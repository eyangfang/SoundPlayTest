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

AudioOperation::AudioOperation()
{
	m_fileLoaded = false;
	m_threadActive = false;
}

void AudioOperation::Initialize()
{
	m_renderer = Microsoft::WRL::Make<ISACRenderer>();

	// Selects the Default Audio Device
	m_renderer->InitializeAudioDeviceAsync();

	// Load the emitter file
	m_fileLoaded = LoadFile(c_WaveFile);
}

bool AudioOperation::Stop()
{
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
