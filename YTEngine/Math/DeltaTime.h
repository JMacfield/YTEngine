#include <windows.h>

class DeltaTime {
private:
    LARGE_INTEGER frequency;
    LARGE_INTEGER lastTime;

public:
    DeltaTime() {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&lastTime);
    }

    float GetDeltaTime() {
        LARGE_INTEGER currentTime;
        QueryPerformanceCounter(&currentTime);

        float deltaTime = static_cast<float>(currentTime.QuadPart - lastTime.QuadPart) / frequency.QuadPart;
        lastTime = currentTime;
        return deltaTime;
    }
};