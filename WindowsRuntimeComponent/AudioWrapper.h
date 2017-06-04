#pragma once

namespace WindowsRuntimeComponent
{
    public ref class AudioWrapper sealed
    {
    public:
        AudioWrapper();
		bool Initialize();
		bool Stop();
    };
}
