#include "Core/Base.h"

namespace SbEngine{

class ISystem {
    virtual ~ISystem() = default;

    virtual void Update() {};
};

}
