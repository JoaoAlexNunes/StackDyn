#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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

//added by PM
#include <vector>
#include <map>
#include <variant>

//using namespace std;
//using vec_types = std::variant<vector<int>, glm::vec3, Texture, int, int>;

class GuiDraw
{
private:
	int Draw();
	//std::variant<vec_types> DrawContainers();

public:
	GuiDraw();
	~GuiDraw();

};

