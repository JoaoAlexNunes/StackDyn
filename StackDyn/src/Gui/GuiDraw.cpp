#include "GuiDraw.h"


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
        float positionsGround[] = {
             -width / 2, -50.0f, 0.0f, 0.0f, // Vertice 0
              width / 2, -50.0f, 1.0f, 0.0f, // Vertice 1
              width / 2,  50.0f, 1.0f, 1.0f, // Vertice 2
             -width / 2,  50.0f, 0.0f, 1.0f  // Vertice 3
        };

        unsigned int indicesGround[] = {
            0,1,2,
            2,3,0,
        };


        float positionsContainer[] = {
             -70.0f, -35.0f, 0.0f, 0.0f, // Vertice 0
              70.0f, -35.0f, 1.0f, 0.0f, // Vertice 1
              70.0f,  25.0f, 1.0f, 1.0f, // Vertice 2
             -70.0f,  25.0f, 0.0f, 1.0f  // Vertice 3
        };

        unsigned int indicesContainer[] = {
            0,1,2,
            2,3,0,
        };



        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


        /*------------------- Projection and View ----------------------*/
        glm::mat4 proj = glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        

        Texture texture("res/textures/container001-red-small.png");
        Texture texture2("res/textures/ground.png");

        Renderer renderer;

        // Setup ImGui binding
        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();

        glm::vec3 translationA(100, 40, 0);
        glm::vec3 translationB(960, 50, 0);

        float r = 0.0f;
        float increment = 0.05f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            ImGui_ImplGlfwGL3_NewFrame();
            
            /*----------------- Ground Start ------------------------*/
            VertexArray vaGround;
            VertexBuffer vbGround(positionsGround, sizeof(positionsGround));

            VertexBufferLayout layoutGround;
            layoutGround.Push<float>(2);
            layoutGround.Push<float>(2);
            vaGround.AddBuffer(vbGround, layoutGround);

            IndexBuffer ibGround(indicesGround, 6);

            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
                glm::mat4 mvp = proj * view * model;
                shader.SetUniformMat4f("u_MVP", mvp);
                texture2.Bind();
                renderer.Draw(vaGround, ibGround, shader);
            }
            /*----------------- Ground End ------------------------*/
            

            /*---------------- Container Start ------------------------*/
            VertexArray vaContainer;
            VertexBuffer vbContainer(positionsContainer, sizeof(positionsContainer));

            VertexBufferLayout layoutContainer;
            layoutContainer.Push<float>(2);
            layoutContainer.Push<float>(2);
            vaContainer.AddBuffer(vbContainer, layoutContainer);

            IndexBuffer ibContainer(indicesContainer, 6);

            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
                glm::mat4 mvp = proj * view * model;
                shader.SetUniformMat4f("u_MVP", mvp);
                texture.Bind();
                renderer.Draw(vaContainer, ibContainer, shader);
            }
            /*---------------- Container End ------------------------*/


            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;
            r += increment;

            #ifdef _DEBUG
            {
               
                ImGui::SliderFloat2("Translation A", &translationA.x, 0.0f, width);
                //Draw a second square
                ImGui::SliderFloat2("Translation B", &translationB.x, 0.0f, width);
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

GuiDraw::~GuiDraw()
{
}