#pragma once

#include "Core/Types.h"
#include <chrono>
#include <unordered_map>

namespace Sb {
    class Profiler {
        using clock = std::chrono::high_resolution_clock;
        struct ProfilingData {
            std::string label;
            double time;
        };

    public:
        static void EnableFrameCapture();
        static void DisableFrameCapture();
        static void StartRecord(std::string profilingLabel);
        static double StopRecord(std::string profilingLabel);
        static void DumpRecordings();
        static void ClearRecordings();
        static void SetTotalFrametime(float ioFrameTime) { totalFrameTime = ioFrameTime; };
    private:
        static bool enableFrameCapture;
        static std::unordered_map<std::string, clock::time_point> recordings;
        static std::vector<ProfilingData> recordTimes;
        static float totalFrameTime;
    };
}