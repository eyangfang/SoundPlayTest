#pragma once
#include "ISACRenderer.h"
#include "AudioOperation.h"
#include "WAVFileReader.h"

namespace WindowsRuntimeComponent 
{
    public ref class AudioWrapper sealed
    {
    public:
        AudioWrapper();
		void Initialize();
		bool Stop();
		void SetDistance(double dist, bool isCWise);
	private:
		AudioOperation ops;
    };
}
