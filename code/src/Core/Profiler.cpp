#include "Profiler.h"
#include "Debug.h"
#include <utility>

namespace Sb {

    bool Profiler::enableFrameCapture = false;
    std::unordered_map<std::string, Profiler::clock::time_point> Profiler::recordings;
    std::vector<Profiler::ProfilingData> Profiler::recordTimes;
    float Profiler::totalFrameTime;

    void Profiler::EnableFrameCapture() {
        ClearRecordings();
        enableFrameCapture = true;
        Log::Info("--- Profiler ---: Recording frame");
    }

    void Profiler::DisableFrameCapture() {
        enableFrameCapture = false;
    }
    
    void Profiler::StartRecord(std::string profilingLabel) {
        if(enableFrameCapture) {
            if(recordings.count(profilingLabel) <= 0) {
                recordings.emplace(profilingLabel, clock::now());
            }
        }
    }

    double Profiler::StopRecord(std::string profilingLabel) {
        if(enableFrameCapture) {
            if(recordings.count(profilingLabel) > 0) {
                clock::time_point stopPoint = clock::now();
                std::chrono::duration<double, std::milli> timeElapsed = stopPoint-recordings[profilingLabel];
                recordTimes.push_back(Profiler::ProfilingData{profilingLabel, timeElapsed.count()});
                return timeElapsed.count();
            }
        }
        return 0;
    }

    void Profiler::DumpRecordings() {
        if(recordTimes.size() > 0) {
            for(auto val : recordTimes) {
                Log::Info("--- Profiler ---: ", val.label, " took ", val.time, " ms");
            }
            Log::Info("--- Profiler ---: Total frame time ", 1000.0f / totalFrameTime," ms");
            ClearRecordings();
        }
    }
    
    void Profiler::ClearRecordings() {
        recordings.clear();
        recordTimes.clear();
        Log::Info("--- Profiler ---: Cleared all time recordings");
    }
}