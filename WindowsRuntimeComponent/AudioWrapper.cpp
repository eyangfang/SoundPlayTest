#include "pch.h"
#include "AudioWrapper.h"
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

AudioWrapper::AudioWrapper()
{
}

bool AudioWrapper::Initialize()
{
	std::unique_ptr<uint8_t[]>              m_waveFile;
	DX::WAVData  WavData;
	if (DX::LoadWAVAudioFromFileEx(c_WaveFile, m_waveFile, WavData))
	{
		return false;
	}
	return true;
}

bool AudioWrapper::Stop()
{
	return true;
}