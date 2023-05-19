#include <stdafx.h>

// #pragma comment (lib, "glew32s.lib")
// #define GLEW_STATIC
// #include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <array>
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

#include "Engine/Graphics/Renderer.h"

 GLFWwindow* CreateWindow(int windowWidth, int windowHeight, const char* title)
 {
     GLFWwindow* window;
 
     // Initialize the library
     glfwSetErrorCallback(GLFWErrorCallback);
     if (!glfwInit())
         return nullptr;
 
     const char* GLSLVersion = "#version 330 core";
     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 
     // Create a windowed mode window and its OpenGL context
     window = glfwCreateWindow(windowWidth, windowHeight, title, NULL, NULL);
     if (window == NULL)
     {
         std::cout << "Failed while running function: glfwCreateWindow" << std::endl;
         glfwTerminate();
         return nullptr;
     }
 
     // Make the window's context current
     glfwMakeContextCurrent(window);
     glfwSwapInterval(1);
 
     //Setup Dear ImGui context
     IMGUI_CHECKVERSION();
     ImGui::CreateContext();
     ImGuiIO& io = ImGui::GetIO(); (void)io;
     io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
     io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
     io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
 
     // Setup Dear ImGui style
     ImGui::ApplyDefaultStyle();
 
     // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
     ImGuiStyle& style = ImGui::GetStyle();
     if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
     {
         style.WindowRounding = 0.0f;
         style.Colors[ImGuiCol_WindowBg].w = 1.0f;
     }
 
     // Setup Platform/Renderer backends
     ImGui_ImplGlfw_InitForOpenGL(window, true);
     ImGui_ImplOpenGL3_Init(GLSLVersion);
 
 
     // Init modern OpenGl
     if (glewInit() != GLEW_OK)
     {
         std::cout << "Failed while running function: gleInit" << std::endl;
         return nullptr;
     }
 
     std::cout << "Using GL Version: " << glGetString(GL_VERSION) << std::endl;
 
     glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
 
     return window;
 }
 
 int main()
 {
     int windowWidth = 960;
     int windowHeight = 540;
 
     GLFWwindow* window = CreateWindow(windowWidth, windowHeight, "Hello World");
 
     glm::vec4 clearColor(0.1, 0.32, 0.56, 1); // default clearColor
 
     do
     {
         // Start the Dear ImGui frame
         ImGui_ImplOpenGL3_NewFrame();
         ImGui_ImplGlfw_NewFrame();
         ImGui::NewFrame();
 
         {
             // Debug Window
             ImGui::Begin("Debug");
             ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
 
             ImGui::End();
         }
 
         ImGui::Render();
         int displayWidth, displayHeight;
         glfwGetFramebufferSize(window, &displayWidth, &displayHeight);
         glViewport(0, 0, displayWidth, displayHeight);
         glClearColor(clearColor.x * clearColor.w, clearColor.y * clearColor.w, clearColor.z * clearColor.w, clearColor.w);
         ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
 
         if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
         {
             GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
             ImGui::UpdatePlatformWindows();
             ImGui::RenderPlatformWindowsDefault();
             glfwMakeContextCurrent(backupCurrentContext);
         }
 
         // Swap buffers
         glfwSwapBuffers(window);
         glfwPollEvents();
     }
     while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
 
     ImGui_ImplOpenGL3_Shutdown();
     ImGui_ImplGlfw_Shutdown();
     ImGui::DestroyContext();
 
     glfwDestroyWindow(window);
     glfwTerminate();
 
     return EXIT_SUCCESS;
 }