#pragma once
#include <string>

namespace SbEngine{

    // Debug define changes where the resource data file will be fetched

    #ifdef SANDBOX_DEBUG
        const std::string SB_RESOURCE_DATA_PATH = "../resources/resource_manifests.yaml";
    #else
        const std::string SB_RESOURCE_DATA_PATH = "resources/resource_manifest.yaml";
    #endif
}