#pragma once
#include "ISACRenderer.h"
#include "AudioOperation.h"
#include "WAVFileReader.h"

using namespace Windows::System::Threading;
using namespace Windows::Foundation;
using namespace Windows::System;

namespace WindowsRuntimeComponent 
{
	enum Orientation
	{
		LEFT,
		RIGHT,
		FRONT,
		BACK,
		TOP,
		BOTTOM
	};

    public ref class AudioWrapper sealed
    {
    public:
        AudioWrapper();
		void Initialize();
		bool Stop();
		void SetDistance(double dist, bool isCWise);
		void SetMode(bool isCWise) { m_bCWise = isCWise; };

	private:
		void UpdatePosition();
		AudioOperation ops;
		TimeSpan period;
		ThreadPoolTimer ^ PeriodicTimer;
		bool m_bCWise;
		Orientation ort;
    };
}
