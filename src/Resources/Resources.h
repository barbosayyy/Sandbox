#pragma once
#include <string>

namespace Sandbox{

    // Debug define changes where the resource data file will be fetched

    #ifdef SANDBOX_DEBUG
        const std::string SB_RESOURCE_DATA_PATH = "../resources/resource-data.yaml";
    #else
        const std::string SB_RESOURCE_DATA_PATH = "resources/resource-data.yaml";
    #endif
}