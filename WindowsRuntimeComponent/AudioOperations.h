#pragma once
#include "ISACRenderer.h"
#include "WAVFileReader.h"

namespace WindowsRuntimeComponent 
{
    class AudioOperations
    {
    public:
		AudioOperations();
		void Initialize();
		bool Stop();
		bool LoadFile(LPCWSTR inFile);

		struct AudioEmitter
		{
			char*   wavBuffer;
			UINT32  buffersize;
			UINT32  curBufferLoc;
			float   posX;
			float   posY;
			float   posZ;
			float   angle;
			Microsoft::WRL::ComPtr<ISpatialAudioObject> object;
		};
		// Worker thread for spatial system
		PTP_WORK                                        m_workThread;
	public:
		Microsoft::WRL::ComPtr<ISACRenderer>            m_renderer;
		AudioEmitter                                    m_emitter;
		AudioEmitter                                    m_listener;
		bool	                                        m_threadActive;
		bool                                            m_fileLoaded;
    };
}
