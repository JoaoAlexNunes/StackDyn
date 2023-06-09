#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../pch.h"

#include "Renderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

class GuiDraw
{
public:
	GuiDraw();
	~GuiDraw();
	int Init();

};

