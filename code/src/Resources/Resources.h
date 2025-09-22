#pragma once
#include <string>

namespace Sb {

	// Debug define changes where the resource data file will be fetched

#ifdef SANDBOX_DEBUG
	const std::string SB_RESOURCE_FOLDER_PATH = "..\\resources";
	const std::string SB_RESOURCE_MANIFEST_PATH = "..\\resources\\resource_manifest.yaml";
	#else
	const std::string SB_RESOURCE_FOLDER_PATH = "resources";
	const std::string SB_RESOURCE_MANIFEST_PATH = "resources\\resource_manifest.yaml";
#endif
}