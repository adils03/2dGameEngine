#ifndef TEXTURE_H
#define TEXTURE_H

#include<glad/glad.h>
#include<stb/stb_image.h>

#include "Shader.h"
#include "Component.h"

class Texture : public virtual Component
{
public:
	GLuint ID;
	GLenum type;
	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
	void update()  override;
	void cleanup() const override;
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind() const;
	void Unbind() const;
	void Delete() const;

};

#endif // TEXTURE_H
