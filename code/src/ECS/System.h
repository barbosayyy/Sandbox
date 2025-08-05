#include "../Core/Base.h"

namespace Sb {

class ISystem {
    virtual ~ISystem() = default;

    virtual void Update() {};
};

}
