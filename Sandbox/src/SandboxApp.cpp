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
	}

	void OnEvent(Monstera::Event& event) override
	{
		// MD_TRACE("{0}", event);
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