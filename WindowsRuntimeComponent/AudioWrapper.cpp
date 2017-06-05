﻿#include "pch.h"
#include "AudioWrapper.h"
#include "WAVFileReader.h"

using namespace DirectX;
using namespace WindowsRuntimeComponent;
using namespace Platform;

//VOID CALLBACK SpatialWorkCallback(_Inout_ PTP_CALLBACK_INSTANCE Instance, _Inout_opt_ PVOID Context, _Inout_ PTP_WORK Work)
//{
//	HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
//	AudioOperation* Sink = (AudioOperation *)Context;
//	Work;
//	Instance;
//
//	while (Sink->m_threadActive)
//	{
//		while (Sink->m_renderer->IsActive())
//		{
//			// Wait for a signal from the audio-engine to start the next processing pass 
//			if (Sink->m_renderer->m_bufferCompletionEvent)
//			{
//				if (WaitForSingleObject(Sink->m_renderer->m_bufferCompletionEvent, 100) != WAIT_OBJECT_0)
//				{
//					//make a call to stream to see why we didn't get a signal after 100ms
//					hr = Sink->m_renderer->m_SpatialAudioStream->Reset();
//
//					//if we have an error, tell the renderer to reset
//					if (hr != S_OK)
//					{
//						Sink->m_renderer->Reset();
//					}
//					continue;
//				}
//			}
//
//			UINT32 frameCount;
//			UINT32 availableObjectCount;
//
//			// Begin the process of sending object data and metadata 
//			// Get the number of active object that can be used to send object-data 
//			// Get the number of frame count that each buffer be filled with?
//			hr = Sink->m_renderer->m_SpatialAudioStream->BeginUpdatingAudioObjects(
//				&availableObjectCount,
//				&frameCount);
//			//if we have an error, tell the renderer to reset
//			if (hr != S_OK)
//			{
//				Sink->m_renderer->Reset();
//			}
//
//			//Activate the object if not yet done
//			if (Sink->m_emitter.object == nullptr)
//			{
//				// If this method called more than activeObjectCount times 
//				// It will fail with this error HRESULT_FROM_WIN32(ERROR_NO_MORE_ITEMS) 
//				hr = Sink->m_renderer->m_SpatialAudioStream->ActivateSpatialAudioObject(
//					AudioObjectType_Dynamic,
//					&Sink->m_emitter.object);
//				if (FAILED(hr))
//				{
//					continue;
//				}
//
//			}
//
//			//Get the object buffer
//			BYTE* buffer = nullptr;
//			UINT32 bytecount;
//			hr = Sink->m_emitter.object->GetBuffer(&buffer, &bytecount);
//			if (FAILED(hr))
//			{
//				continue;
//			}
//
//			Sink->m_emitter.object->SetPosition(Sink->m_emitter.posX - Sink->m_listener.posX,
//				Sink->m_emitter.posZ - Sink->m_listener.posZ,
//				Sink->m_listener.posY - Sink->m_emitter.posY);
//			Sink->m_emitter.object->SetVolume(1.f);
//
//			for (UINT32 i = 0; i < bytecount; i++)
//			{
//				UINT32 fileLoc = Sink->m_emitter.curBufferLoc;
//				buffer[i] = Sink->m_emitter.wavBuffer[fileLoc];
//				Sink->m_emitter.curBufferLoc++;
//				if (Sink->m_emitter.curBufferLoc == Sink->m_emitter.buffersize)
//				{
//					Sink->m_emitter.curBufferLoc = 0;
//				}
//			}
//
//			// Let the audio-engine know that the object data are available for processing now 
//			hr = Sink->m_renderer->m_SpatialAudioStream->EndUpdatingAudioObjects();
//			if (FAILED(hr))
//			{
//				//if we have an error, tell the renderer to reset
//				Sink->m_renderer->Reset();
//				continue;
//			}
//		}
//	}
//
//}


AudioWrapper::AudioWrapper()
{
}

void AudioWrapper::UpdatePosition()
{
	if (m_bCWise) //front -> right-> back-> left
	{
		switch (ort) 
		{
			case LEFT:
				ort = FRONT;
				ops.m_emitter.posX = 0;
				ops.m_emitter.posY = -100;
				ops.m_emitter.posZ = 0;
				break;
			case RIGHT:
				ort = BACK;
				ops.m_emitter.posX = 0;
				ops.m_emitter.posY = 100;
				ops.m_emitter.posZ = 0;
				break;
			case FRONT:
				ort = RIGHT;
				ops.m_emitter.posX = 100;
				ops.m_emitter.posY = 0;
				ops.m_emitter.posZ = 0;
				break;
			case BACK:
				ort = LEFT;
				ops.m_emitter.posX = -100;
				ops.m_emitter.posY = 0;
				ops.m_emitter.posZ = 0;
				break;
		}
	}
	else         //front->above->back->below
	{
		switch (ort)
		{
		case BOTTOM:
			ort = FRONT;
			ops.m_emitter.posX = 0;
			ops.m_emitter.posY = -100;
			ops.m_emitter.posZ = 0;
			break;
		case TOP:
			ort = BACK;
			ops.m_emitter.posX = 0;
			ops.m_emitter.posY = 100;
			ops.m_emitter.posZ = 0;
			break;
		case FRONT:
			ort = TOP;
			ops.m_emitter.posX = 0;
			ops.m_emitter.posY = 0;
			ops.m_emitter.posZ = 100;
			break;
		case BACK:
			ort = BOTTOM;
			ops.m_emitter.posX = 0;
			ops.m_emitter.posY = 0;
			ops.m_emitter.posZ = -100;
			break;
		}
	}
}

void AudioWrapper::Initialize()
{
	ops.Initialize();
	period.Duration = 10 * 10000000;
	times = 0;
	ort = FRONT;
	PeriodicTimer = ThreadPoolTimer::CreatePeriodicTimer(
		ref new TimerElapsedHandler([this](ThreadPoolTimer^ source)
	{
		UpdatePosition();
	}), period);

	//if (ops.m_fileLoaded && ops.m_renderer)
	//{
	//	while (!ops.m_renderer->IsActive())
	//	{
	//		//Wait for renderer, then start
	//		Sleep(5);
	//	}
	//	ops.m_threadActive = true;
	//	ops.m_workThread = CreateThreadpoolWork(SpatialWorkCallback, &ops, nullptr);
	//	SubmitThreadpoolWork(ops.m_workThread);
	//}
}

bool AudioWrapper::Stop()
{
	/*ops.m_threadActive = false;
	WaitForThreadpoolWorkCallbacks(ops.m_workThread, FALSE);
	CloseThreadpoolWork(ops.m_workThread);*/
	ops.Stop();
	return true;
}

void AudioWrapper::SetDistance(double dist, bool isCWise)
{
	if (isCWise)
	{
		switch (ort)
		{
		case LEFT:
			ort = FRONT;
			ops.m_emitter.posX = 0;
			ops.m_emitter.posY = -dist;
			ops.m_emitter.posZ = 0;
			break;
		case RIGHT:
			ort = BACK;
			ops.m_emitter.posX = 0;
			ops.m_emitter.posY = dist;
			ops.m_emitter.posZ = 0;
			break;
		case FRONT:
			ort = RIGHT;
			ops.m_emitter.posX = dist;
			ops.m_emitter.posY = 0;
			ops.m_emitter.posZ = 0;
			break;
		case BACK:
			ort = LEFT;
			ops.m_emitter.posX = -dist;
			ops.m_emitter.posY = 0;
			ops.m_emitter.posZ = 0;
			break;
		}
	}
	else         //front->above->back->below
	{
		switch (ort)
		{
		case BOTTOM:
			ort = FRONT;
			ops.m_emitter.posX = 0;
			ops.m_emitter.posY = -dist;
			ops.m_emitter.posZ = 0;
			break;
		case TOP:
			ort = BACK;
			ops.m_emitter.posX = 0;
			ops.m_emitter.posY = dist;
			ops.m_emitter.posZ = 0;
			break;
		case FRONT:
			ort = TOP;
			ops.m_emitter.posX = 0;
			ops.m_emitter.posY = 0;
			ops.m_emitter.posZ = dist;
			break;
		case BACK:
			ort = BOTTOM;
			ops.m_emitter.posX = 0;
			ops.m_emitter.posY = 0;
			ops.m_emitter.posZ = -dist;
			break;
		}
	}
}