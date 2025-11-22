#pragma once

namespace SbEditor {
    class EditorApplication {
        bool _flag = false;
    public:
        void Run();
        
        void QueryStop() { _flag = true; };

		bool ShouldStop() { return _flag; };
    };
}