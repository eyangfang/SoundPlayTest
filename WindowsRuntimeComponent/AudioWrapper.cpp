#include "pch.h"
#include "AudioWrapper.h"
#include "WAVFileReader.h"

using namespace DirectX;
using namespace WindowsRuntimeComponent;
using namespace Platform;

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
	ort = FRONT;
	PeriodicTimer = ThreadPoolTimer::CreatePeriodicTimer(
		ref new TimerElapsedHandler([this](ThreadPoolTimer^ source)
	{
		UpdatePosition();
	}), period);
}

bool AudioWrapper::Stop()
{
	ops.Stop();
	return true;
}

void AudioWrapper::SetDistance(float dist, bool isCWise)
{
	if (isCWise)
	{
		switch (ort)
		{
		case FRONT:
			ops.m_emitter.posX = 0;
			ops.m_emitter.posY = -dist;
			ops.m_emitter.posZ = 0;
			break;
		case BACK:
			ops.m_emitter.posX = 0;
			ops.m_emitter.posY = dist;
			ops.m_emitter.posZ = 0;
			break;
		case RIGHT:
			ops.m_emitter.posX = dist;
			ops.m_emitter.posY = 0;
			ops.m_emitter.posZ = 0;
			break;
		case LEFT:
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
		case FRONT:
			ops.m_emitter.posX = 0;
			ops.m_emitter.posY = -dist;
			ops.m_emitter.posZ = 0;
			break;
		case BACK:
			ops.m_emitter.posX = 0;
			ops.m_emitter.posY = dist;
			ops.m_emitter.posZ = 0;
			break;
		case TOP:
			ops.m_emitter.posX = 0;
			ops.m_emitter.posY = 0;
			ops.m_emitter.posZ = dist;
			break;
		case BOTTOM:
			ops.m_emitter.posX = 0;
			ops.m_emitter.posY = 0;
			ops.m_emitter.posZ = -dist;
			break;
		}
	}
}