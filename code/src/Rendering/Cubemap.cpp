#include "Cubemap.h"
#include "Resources/ResourceManagement.h"
#include "Core/Debug.h"

namespace Sb {
    
    void Cubemap::Draw() {
        Renderer& renderer = Renderer::GetInstance();

        glDepthMask(GL_FALSE);
		glDepthFunc(GL_LEQUAL);
		this->_cubemapShader->Use();
		this->_cubemapShader->SetMat4("view", mat4(mat3(renderer.GetRenderCamera()->GetView())));
		this->_cubemapShader->SetMat4("projection", renderer.GetRenderCamera()->GetProjection());
		glBindVertexArray(this->vertexData);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, this->data);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LESS);
    }
}