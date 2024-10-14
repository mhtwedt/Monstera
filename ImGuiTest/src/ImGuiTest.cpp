#include <Monstera.h>

#include "imgui/imgui.h"

#include <chrono>

class ExampleLayer : public Monstera::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate()
	{
		if (Monstera::Input::IsKeyPressed(MD_KEY_TAB))
			MD_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(Monstera::Event& event) override
	{
		if (event.GetEventType() == Monstera::EventType::KeyPressed)
		{
			Monstera::KeyPressedEvent& e = (Monstera::KeyPressedEvent&)event;
			if (e.GetKeyCode() == MD_KEY_TAB)
				MD_TRACE("Tab key is pressed (event)!");
			MD_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

};

class Sandbox : public Monstera::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Monstera::Application* Monstera::CreateApplication()
{
	return new Sandbox();
}