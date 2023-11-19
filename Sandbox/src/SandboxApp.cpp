#include <Monstera.h>

class ExampleLayer : public Monstera::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		//MD_INFO("ExampleLayer::Update");

		if (Monstera::Input::IsKeyPressed(MD_KEY_LEFT_CONTROL))
			MD_TRACE("Left ctrl pressed");
	}

	void OnEvent(Monstera::Event& event) override
	{
		// MD_TRACE("{0}", event);

	// KeyCode Event Polling example
	// 	if (event.GetEventType() == Monstera::EventType::KeyPressed)
	// 	{
	// 		Monstera::KeyPressedEvent& e = (Monstera::KeyPressedEvent&)event;
	// 		MD_TRACE("{0}", (char)e.GetKeyCode());
	// 	}
	}

};

class Sandbox : public Monstera::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Monstera::ImGuiLayer());
	}

	~Sandbox()
	{

	}

};



Monstera::Application* Monstera::CreateApplication()
{
	return new Sandbox();

}