#pragma once

#include "Engine/IEngine.h"

namespace SbEditor {
    class Editor {
    public:
		void Run();

		void Update();

		void Render();

		// Query application to stop on next processing cycle
		void QueryStop() { _flag = true; };

		// Returns Application-side flag for stopping the application
		bool ShouldStop() { return _flag; };

		void SetSbEnginePtr(Sb::IEngine* sbEngine) { _sbEngine = sbEngine; };

	private:
		bool _flag = false;
		Sb::IEngine* _sbEngine;
    };
}