#include "Core/Debug.h"
#include "GLBuffer.h"

namespace Sb {
    static void GLBufferVertexData(u32 &vao, std::vector<Vertex> vertices, std::vector<u32> indices) {
        glGenVertexArrays(1, &vao);
		
		u32 vbo;
		u32 ebo;
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		if(vertices.size() > 0) {
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
		}
		else {
            Log::Warn("Mesh: Creating mesh with no vertices!");
		}
        if(indices.size() > 0) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
		}
        if (vertices.size() > 0) {
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
            glEnableVertexAttribArray(2);
		}
		glBindVertexArray(0);
    }

    static void GLBufferPrimitiveData(u32 &vao, const float* primitive, size_t vertexSize, size_t numAttributes) {
        u32 vbo;
        
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(vertexSize*numAttributes), primitive, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    }
}