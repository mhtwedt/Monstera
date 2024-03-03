#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

static const uint32_t s_MapWidth = 24;
static const char* s_MapTiles =
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWDDDDDWWWWWWWWWWWW"
"WWWWWWWDDDDDDDDDWWWWWWWW"
"WWWWWDDDDDDDDDDDDDWWWWWW"
"WWWDDDDDDDDDDDDDDDDDWWWW"
"WWWDDDWWWDDDDDDDDDDDWWWW"
"WWWDDDWWWDDDDDDDDDDDWWWW"
"WWWDDDDDDDDDDDDDDDDDWWWW"
"WWWDDDDDDDDDDDDDDCDDWWWW"
"WWWWWDDDDDDDDDDDDDWWWWWW"
"WWWWWDDDDDDDDDDDDDWWWWWW"
"WWWWWWWDDDDDDDDDWWWWWWWW"
"WWWWWWWWWWDDDDDDWWWWWWWW"
"WWWWWWWWWWDDDDDDWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW";


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	MD_PROFILE_FUNCTION();

	m_CheckerboardTexture = Monstera::Texture2D::Create("assets/textures/Checkerboard.png");
	m_Spritesheet = Monstera::Texture2D::Create("assets/game/textures/RPGpack_sheet_2X.png");



	m_MapWidth = s_MapWidth;
	m_MapHeight = strlen(s_MapTiles) / s_MapWidth;

	s_TextureMap['D'] = Monstera::SubTexture2D::CreateFromCoords(m_Spritesheet, {6, 11}, {128, 128});
	s_TextureMap['W'] = Monstera::SubTexture2D::CreateFromCoords(m_Spritesheet, { 11, 11 }, { 128, 128 });

	m_TextureBarrel = Monstera::SubTexture2D::CreateFromCoords(m_Spritesheet, { 9,2 }, { 128, 128 });
	m_TextureTree = Monstera::SubTexture2D::CreateFromCoords(m_Spritesheet, { 2,1 }, { 128, 128 }, { 1, 2 });

	// Init here
	m_Particle.ColorBegin = { 114 / 255.0f, 84 / 255.0f, 139 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 50.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };

	m_CameraController.SetZoomLevel(5.0f);
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
	Monstera::Renderer2D::ResetStats();
	{
		MD_PROFILE_SCOPE("Sandbox2D Renderer Prep");

		Monstera::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
		Monstera::RenderCommand::Clear();
	}

#if 0
	{
		static float rotation = 0.0f;
		rotation += ts * (50.0f * glm::pi<float>() / 180.0f);

		MD_PROFILE_SCOPE("Sandbox2D Renderer Draw");
		Monstera::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Monstera::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f, 0.0f }, { 0.8f, 0.8f }, rotation, { 0.8f, 0.2f, 0.3f, 1.0f });
		Monstera::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Monstera::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Monstera::Renderer2D::DrawRotatedQuad({ -0.5f, -0.5f}, { 1.0f, 1.0f }, rotation, m_CheckerboardTexture, 20.0f, {0.2f, 0.8f, 0.3f, 1.0f});
		Monstera::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {20.0f, 20.0f}, m_CheckerboardTexture, 10.0f); // not sure why having a z pos of 0.0 is working

		Monstera::Renderer2D::EndScene();
		
		
		// Stress Test
		Monstera::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f / 10.0f), 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				Monstera::Renderer2D::DrawQuad({ x,y }, { 0.45f, 0.45f }, color);
			}
		}
		Monstera::Renderer2D::EndScene();

	} 
#endif



	if (Monstera::Input::IsMouseButtonPressed(MD_MOUSE_BUTTON_LEFT))
	{
		auto [x, y] = Monstera::Input::GetMousePosition();
		auto width = Monstera::Application::Get().GetWindow().GetWidth();
		auto height = Monstera::Application::Get().GetWindow().GetHeight();

		auto bounds = m_CameraController.GetBounds();
		auto pos = m_CameraController.GetCamera().GetPosition();
		x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		m_Particle.Position = { x + pos.x, y + pos.y };
		for (int i = 0; i < 5; i++)
			m_ParticleSystem.Emit(m_Particle);
	}

	m_ParticleSystem.OnUpdate(ts);
	m_ParticleSystem.OnRender(m_CameraController.GetCamera());

	Monstera::Renderer2D::BeginScene(m_CameraController.GetCamera());


	for (uint32_t y = 0; y < m_MapHeight; y++)
	{
		for (uint32_t x = 0; x < m_MapWidth; x++)
		{
			char tileType = s_MapTiles[x + y * m_MapWidth];

			Monstera::Ref<Monstera::SubTexture2D> texture;
			if (s_TextureMap.find(tileType) != s_TextureMap.end())
				texture = s_TextureMap[tileType];
			else
				texture = m_TextureBarrel;

			Monstera::Renderer2D::DrawQuad({ x - m_MapWidth / 2.0f, m_MapHeight / 2.0f - y, 0.1f }, { 1.0f, 1.0f }, texture);

		}
	}

	// Monstera::Renderer2D::DrawQuad({ 0.0f, 0.0f , 0.1f}, { 1.0f, 1.0f }, m_TextureStairs);
	// Monstera::Renderer2D::DrawQuad({ 1.0f, 0.0f , 0.1f }, { 1.0f, 1.0f }, m_TextureBarrel);
	// Monstera::Renderer2D::DrawQuad({ -1.0f, 0.0f , 0.1f }, { 1.0f, 2.0f }, m_TextureTree);

	Monstera::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	MD_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	auto stats = Monstera::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quad Count: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();

}

void Sandbox2D::OnEvent(Monstera::Event& e)
{
	m_CameraController.OnEvent(e);
}