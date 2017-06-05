#include "pch.h"
#include "AudioOperation.h"
#include "WAVFileReader.h"

using namespace DirectX;
using namespace WindowsRuntimeComponent;
using namespace Platform;

namespace
{
	const wchar_t* c_WaveFile = L"./assets/ATG_SpatialMotion_monoFunkDrums1Loop.wav";
	const float c_RotateScale = 0.1f;
	const float c_MaxHeight = 100;
	const float c_MoveScale = 3.0f;
}

VOID CALLBACK SpatialWorkCallback(_Inout_ PTP_CALLBACK_INSTANCE Instance, _Inout_opt_ PVOID Context, _Inout_ PTP_WORK Work)
{
	HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	AudioOperation* Sink = (AudioOperation *)Context;
	Work;
	Instance;

	while (Sink->m_threadActive)
	{
		while (Sink->m_PlayingSound && Sink->m_renderer->IsActive())
		{
			// Wait for a signal from the audio-engine to start the next processing pass 
			if (Sink->m_renderer->m_bufferCompletionEvent)
			{
				if (WaitForSingleObject(Sink->m_renderer->m_bufferCompletionEvent, 100) != WAIT_OBJECT_0)
				{
					//make a call to stream to see why we didn't get a signal after 100ms
					hr = Sink->m_renderer->m_SpatialAudioStream->Reset();

					//if we have an error, tell the renderer to reset
					if (hr != S_OK)
					{
						Sink->m_renderer->Reset();
					}
					continue;
				}
			}

			UINT32 frameCount;
			UINT32 availableObjectCount;

			// Begin the process of sending object data and metadata 
			// Get the number of active object that can be used to send object-data 
			// Get the number of frame count that each buffer be filled with?
			hr = Sink->m_renderer->m_SpatialAudioStream->BeginUpdatingAudioObjects(
				&availableObjectCount,
				&frameCount);
			//if we have an error, tell the renderer to reset
			if (hr != S_OK)
			{
				Sink->m_renderer->Reset();
			}

			//Activate the object if not yet done
			if (Sink->m_emitter.object == nullptr)
			{
				// If this method called more than activeObjectCount times 
				// It will fail with this error HRESULT_FROM_WIN32(ERROR_NO_MORE_ITEMS) 
				hr = Sink->m_renderer->m_SpatialAudioStream->ActivateSpatialAudioObject(
					AudioObjectType_Dynamic,
					&Sink->m_emitter.object);
				if (FAILED(hr))
				{
					continue;
				}

			}

			//Get the object buffer
			BYTE* buffer = nullptr;
			UINT32 bytecount;
			hr = Sink->m_emitter.object->GetBuffer(&buffer, &bytecount);
			if (FAILED(hr))
			{
				continue;
			}

			Sink->m_emitter.object->SetPosition(Sink->m_emitter.posX - Sink->m_listener.posX,
				Sink->m_emitter.posZ - Sink->m_listener.posZ,
				Sink->m_listener.posY - Sink->m_emitter.posY); //+x=right,-x=left; +y=above,-y=below; +z=behind,-z=front;
			Sink->m_emitter.object->SetVolume(1.f);

			for (UINT32 i = 0; i < bytecount; i++)
			{
				UINT32 fileLoc = Sink->m_emitter.curBufferLoc;
				buffer[i] = Sink->m_emitter.wavBuffer[fileLoc];
				Sink->m_emitter.curBufferLoc++;
				if (Sink->m_emitter.curBufferLoc == Sink->m_emitter.buffersize)
				{
					Sink->m_emitter.curBufferLoc = 0;
				}
			}

			// Let the audio-engine know that the object data are available for processing now 
			hr = Sink->m_renderer->m_SpatialAudioStream->EndUpdatingAudioObjects();
			if (FAILED(hr))
			{
				//if we have an error, tell the renderer to reset
				Sink->m_renderer->Reset();
				continue;
			}
		}
	}

}

AudioOperation::AudioOperation()
{
	m_fileLoaded = false;
	m_threadActive = false;
	m_PlayingSound = false;
}

void AudioOperation::Initialize()
{
	m_listener.posX = 0;
	m_listener.posY = 0;
	m_listener.posZ = 0;
	m_listener.angle = 0;// X3DAUDIO_PI;

	m_emitter.posX = 0;
	m_emitter.posY = 0;
	m_emitter.posZ = 0;
	m_emitter.angle = 0;

	if (m_renderer == nullptr)
	{
		m_renderer = Microsoft::WRL::Make<ISACRenderer>();

		// Selects the Default Audio Device
		m_renderer->InitializeAudioDeviceAsync();
	}
	

	// Load the emitter file
	m_fileLoaded = LoadFile(c_WaveFile);

	if (m_fileLoaded && m_renderer)
	{
		while (!m_renderer->IsActive())
		{
			//Wait for renderer, then start
			Sleep(5);
		}
		m_threadActive = true;
		m_PlayingSound = true;
		m_workThread = CreateThreadpoolWork(SpatialWorkCallback, this, nullptr);
		SubmitThreadpoolWork(m_workThread);
	}
}

bool AudioOperation::Stop()
{
	m_threadActive = false;
	m_PlayingSound = false;
	WaitForThreadpoolWorkCallbacks(m_workThread, FALSE);
	CloseThreadpoolWork(m_workThread);
	return true;
}

bool AudioOperation::LoadFile(LPCWSTR inFile)
{
	std::unique_ptr<uint8_t[]>              m_waveFile;
	DX::WAVData  WavData;

	if (m_emitter.buffersize)
	{
		delete[] m_emitter.wavBuffer;
	}
	m_emitter.buffersize = 0;
	m_emitter.curBufferLoc = 0;

	if (DX::LoadWAVAudioFromFileEx(inFile, m_waveFile, WavData))
	{
		return false;
	}

	if ((WavData.wfx->wFormatTag == 1) && WavData.wfx->nSamplesPerSec == 48000 && WavData.wfx->nChannels == 1)
	{
		int numSamples = WavData.audioBytes / 2;
		m_emitter.wavBuffer = new char[numSamples * 4];
		m_emitter.buffersize = numSamples * 4;

		float * tempnew;
		short * tempdata = (short *)WavData.startAudio;

		for (int i = 0; i < numSamples; i++)
		{
			tempnew = (float *)m_emitter.wavBuffer;
			tempnew[i] = (float)tempdata[i] / 32768;
		}
	}
	else if ((WavData.wfx->wFormatTag == 3) && WavData.wfx->nSamplesPerSec == 48000 && WavData.wfx->nChannels == 1)
	{
		int numSamples = WavData.audioBytes / 4;
		m_emitter.wavBuffer = new char[numSamples * 4];
		m_emitter.buffersize = numSamples * 4;

		float * tempnew;
		float * tempdata = (float *)WavData.startAudio;

		for (int i = 0; i < numSamples; i++)
		{
			tempnew = (float *)m_emitter.wavBuffer;
			tempnew[i] = (float)tempdata[i];
		}
	}
	else
	{
		return false;
	}

	return true;
}
