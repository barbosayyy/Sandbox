
#include "bo_utils.h"

GLuint BOUtils::createBO(GLsizeiptr size, const GLvoid* data, GLenum usage)
{
	GLuint boID;
	glGenBuffers(1, &boID);
	glBindBuffer(GL_ARRAY_BUFFER, boID);
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return boID;
}