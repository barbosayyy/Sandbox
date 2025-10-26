#pragma once

#include "Core/Types.h"

namespace Sb {

	/*  Static class -> all default mesh with static vectors
        Getting each of the meshes returns vertex data only
        Each mesh in the ECS holds instance of the appropriate material (shader + data)
    */

	DefaultMesh GetPrimitiveMeshByID(u32 ID); 

	class Primitive {
	public:
		static DefaultMesh GetCube();
		static DefaultMesh GetPlane();
		static DefaultMesh GetSphere(float radius, u32 stacks, u32 sectors);
		static DefaultMesh GetQuad();

	private:
		static DefaultMesh cube;
		static DefaultMesh plane;
		static DefaultMesh sphere;
		static DefaultMesh quad;
	};
}
