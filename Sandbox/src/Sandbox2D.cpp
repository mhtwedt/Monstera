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
		MD_PROFILE_SCOPE("Sandbox2D Renderer Draw");
		Monstera::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Monstera::Renderer2D::EndScene();

		Monstera::Renderer2D::DrawRotatedQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-30.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
		Monstera::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Monstera::Renderer2D::DrawRotatedQuad({ 0.5f, 0.5f ,-0.1f }, { 10.0f, 10.0f }, glm::radians(30.0f), m_CheckerboardTexture, 10.0f, glm::vec4(0.9f, 0.8f, 1.0f, 1.0f));

		Monstera::Renderer2D::EndScene();
	}
	//glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));


	// TODO Add these functions: Shader::SetMat4, Shader::SetFloat4
	// std::dynamic_pointer_cast<Monstera::OpenGLShader>(m_FlatColorShader)->Bind();
	// std::dynamic_pointer_cast<Monstera::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
	// 
	// Monstera::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

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