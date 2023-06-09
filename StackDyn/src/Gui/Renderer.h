#pragma once

#include <GL/glew.h>

#include "../pch.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if(!(x)) __debugbreak();

#ifdef NDEBUG
#define GLCall(x) x
#else
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#endif

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
private:
public:
	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};



