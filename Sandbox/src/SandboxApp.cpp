#include <Monstera.h>


#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}

class ExampleLayer : public Monstera::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

		auto cam = camera(5.0f, { 0.5f, 0.5f });


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
	}

	~Sandbox()
	{

	}

};



Monstera::Application* Monstera::CreateApplication()
{
	return new Sandbox();

}