#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	MD_PROFILE_FUNCTION();

	m_CheckerboardTexture = Monstera::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	MD_PROFILE_FUNCTION();

}


void Sandbox2D::OnUpdate(Monstera::Timestep ts)
{
	MD_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	{
		MD_PROFILE_SCOPE("Sandbox2D Renderer Prep");
		Monstera::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
		Monstera::RenderCommand::Clear();
	}


	{
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		MD_PROFILE_SCOPE("Sandbox2D Renderer Draw");
		Monstera::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Monstera::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -1*rotation, { 0.8f, 0.2f, 0.3f, 1.0f });
		Monstera::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Monstera::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Monstera::Renderer2D::DrawRotatedQuad({ -0.5f, -0.5f}, { 1.0f, 1.0f }, rotation, m_CheckerboardTexture, 20.0f);
		Monstera::Renderer2D::DrawQuad({0.0f, 0.0f, 0.0f}, {10.0f, 10.0f}, m_CheckerboardTexture, 10.0f); // not sure why having a z pos of 0.0 is working

		Monstera::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Monstera::Event& e)
{
	m_CameraController.OnEvent(e);
}