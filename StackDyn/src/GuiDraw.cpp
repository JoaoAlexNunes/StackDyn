#include "GuiDraw.h"

//using string_int = std::variant<std::string, int>;

//std::vector<string_int> vec;

GuiDraw::GuiDraw() 
{
    Draw();
}


int GuiDraw::Draw()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    //GLFWmonitor* monitor = glfwGetPrimaryMonitor();

    /*glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);*/
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    //Maximized Window
    int left, top, right, bottom;
    glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), &left, &top, &right, &bottom);
    float width = (float)right - left;
    float height = (float)bottom - top;

    // Create a window
    window = glfwCreateWindow(width, height, "hello", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMaximizeWindow(window);
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Context was created start glew
    if (glewInit() != GLEW_OK)
        std::cout << "ERROR !" << std::endl;
    
    {
        float positions[] = {
             -150.0f, -35.0f, 0.0f, 0.0f, // Vertice 0
              150.0f, -35.0f, 1.0f, 0.0f, // Vertice 1
              150.0f,  35.0f, 1.0f, 1.0f, // Vertice 2
             -150.0f,  35.0f, 0.0f, 1.0f  // Vertice 3
        };

        unsigned int indices[] = {
            0,1,2,
            2,3,0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        glm::mat4 proj = glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();

        Texture texture("res/textures/container001-blue-small.png"); 
        shader.SetUniform1i("u_Texture", 0);

        Texture texture2("res/textures/container001-red-small.png");
        shader.SetUniform1i("u_Texture", 0);

        Renderer renderer;

        // Setup ImGui binding
        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();

        glm::vec3 translationA(175, 35, 0);
        glm::vec3 translationB(700, 35, 0);
        glm::vec3 translationC(950, 35, 0);
        glm::vec3 translationD(1250, 35, 0);
        glm::vec3 translationE(1750, 35, 0);
        glm::vec3 translationF(175, 105, 0);
        glm::vec3 translationG(175, 105, 0);

        //criar as translations para o ground


        int pos_x, pos_y = 0;

        //criar o vetor das posi��es (translations) 
        // [0] -> posi��es i ch�o
        // [1] -> posi��es dos containers 
        //std::vector<vec_types> vec_master{//vetor principal 
            //{ //chao

                //{ //vetor dos peda�os do ch�o
                    //{pos_x, pos_y}, //pos(x,y) para o draw
                    //translationA,   //translation
                    //texture,        //textura
                    //0,              //id
                    //500             //segundos para countdown
                //} 
            //}                 

        //};

        float r = 0.0f;
        float increment = 0.05f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            ImGui_ImplGlfwGL3_NewFrame();

            //left ground
            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
                glm::mat4 mvp = proj * view * model;
                shader.SetUniformMat4f("u_MVP", mvp);
                texture.Bind();
                renderer.Draw(va, ib, shader);
            }


            //middle ground
            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
                glm::mat4 mvp = proj * view * model;
                shader.SetUniformMat4f("u_MVP", mvp);
                texture.Bind();
                renderer.Draw(va, ib, shader);
            }

            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationC);
                glm::mat4 mvp = proj * view * model;
                shader.SetUniformMat4f("u_MVP", mvp);
                texture.Bind();
                renderer.Draw(va, ib, shader);
            }

            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationD);
                glm::mat4 mvp = proj * view * model;
                shader.SetUniformMat4f("u_MVP", mvp);
                texture.Bind();
                renderer.Draw(va, ib, shader);
            }



            //right ground
            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationE);
                glm::mat4 mvp = proj * view * model;
                shader.SetUniformMat4f("u_MVP", mvp);
                texture.Bind();
                renderer.Draw(va, ib, shader);
            }

            

            
            std::variant<int, std::string> f(21);

            std::visit([](auto v) {std::cout << v; }, f);

            //std::vector<vec_types> vec_returned;

            //vec_returned = DrawContainers();


            //for (int i[1] : vec_returned) {
            //    glm::vec3 translationG(175, i*10, 0);
            //    {
            //        glm::mat4 model = glm::translate(glm::mat4(1.0f), translationG);
            //        glm::mat4 mvp = proj * view * model;
            //        shader.SetUniformMat4f("u_MVP", mvp);
            //        texture2.Bind();
            //        renderer.Draw(va, ib, shader);
            //    } 
            //}
            
                //container 
                // 
            //{
            //    glm::mat4 model = glm::translate(glm::mat4(1.0f), translationF);
            //    glm::mat4 mvp = proj * view * model;
            //    shader.SetUniformMat4f("u_MVP", mvp);
            //    texture2.Bind();
            //    renderer.Draw(va, ib, shader);
            //} 

            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;
            r += increment;

            #ifdef _DEBUG
            {
               
                ImGui::SliderFloat2("Translation A", &translationA.x, 0.0f, 960.0f);
                ImGui::SliderFloat2("Translation B", &translationB.x, 0.0f, 1060.0f);
                ImGui::SliderFloat2("Translation C", &translationC.x, 0.0f, 1160.0f);
                ImGui::SliderFloat2("Translation D", &translationD.x, 0.0f, 1260.0f);
                ImGui::SliderFloat2("Translation E", &translationE.x, 0.0f, 1360.0f);
                ImGui::SliderFloat2("Translation F", &translationF.x, 0.0f, 1460.0f);
                ImGui::SliderFloat2("Translation G", &translationG.x, 0.0f, 1560.0f);
                //Draw a second square
                //ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, 960.0f);
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                
            }

                ImGui::Render();
                ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
            #endif // NDEBUG

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    // Cleanup
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
}
//using namespace std;
//std::variant<vec_types> GuiDraw::DrawContainers() {
    
    
//    glm::vec3 translationZ(175, 35, 0);
//    std::variant<vec_types> vector_geral{
//        translationZ,

//    };

//    return vector_geral;
//}

GuiDraw::~GuiDraw()
{
}