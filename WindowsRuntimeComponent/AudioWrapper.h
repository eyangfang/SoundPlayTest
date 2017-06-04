#pragma once
#include "ISACRenderer.h"
#include "AudioOperations.h"
#include "WAVFileReader.h"

namespace WindowsRuntimeComponent 
{
    public ref class AudioWrapper sealed
    {
    public:
        AudioWrapper();
		void Initialize();
		bool Stop();
	private:
		AudioOperations ops;
    };
}
