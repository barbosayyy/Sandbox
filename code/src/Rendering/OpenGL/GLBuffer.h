#pragma once

#include "Core/Base.h"
#include "Core/Types.h"

namespace Sb {
    void GLBufferVertexData(u32& vao, std::vector<Vertex> vertices, std::vector<u32> indices);
    void GLBufferPrimitiveData(u32& vao, const float* primitive, size_t vertexSize, size_t numAttributes);
}