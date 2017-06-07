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
		void SetDistance(float dist, bool isCWise);
		void SetMode(bool isCWise) { m_bCWise = isCWise; };
		void UpdatePosition();
		bool GetClockWise() { return m_bCWise; }
		void SetClockWise(bool inClockWise) { m_bCWise = inClockWise; }
		int GetCurrentOrientation() { return ort; }
		void SetCurrentOrientation(int orientation) { ort = (Orientation)orientation; }
	private:
		AudioOperation ops;
		TimeSpan period;
		ThreadPoolTimer ^ PeriodicTimer;
		bool m_bCWise;
		Orientation ort;
    };
}
