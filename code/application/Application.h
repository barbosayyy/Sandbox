#pragma once

namespace SbApplication{

    class Application {
    public:

        void Run();

        // Query application to stop on next processing cycle
        void QueryStop(){_flag = true;};

        // Returns Application-side flag for stopping the application
        bool ShouldStop(){return _flag;};
    private:
        bool _flag = false;
    };

}
