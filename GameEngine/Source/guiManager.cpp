#include "guiManager.h"

guiManager::guiManager(GLFWwindow* window)
{
	init(window);
}

guiManager::~guiManager()
{
	destroy();
}

void guiManager::init(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void guiManager::create()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void guiManager::render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void guiManager::destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

bool guiManager::wantCaptureMouse()
{
	return ImGui::GetIO().WantCaptureMouse;
}

bool guiManager::wantCaptureKeyboard()
{
	return ImGui::GetIO().WantCaptureMouse;
}

void guiManager::debugWindow()
{
	this->create();
	ImGui::Begin("Welcome to the simulation, adventurer!");
	ImGui::Text("This is just some fancy text man.", b2Color(1.0f, 0.0f, 0.0f, 1.0f));
	ImGui::Spacing();
	ImGui::End();
	this->render();
}
