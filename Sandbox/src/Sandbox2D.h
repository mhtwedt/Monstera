#pragma once

#include "Monstera.h"

#include "ParticleSystem.h"

class Sandbox2D : public Monstera::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Monstera::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Monstera::Event& e) override;


private:
	Monstera::OrthographicCameraController m_CameraController;

	// Temp
	Monstera::Ref<Monstera::VertexArray> m_SquareVA;
	Monstera::Ref<Monstera::Shader> m_FlatColorShader;

	Monstera::Ref<Monstera::Texture2D> m_CheckerboardTexture;
	Monstera::Ref<Monstera::Texture2D> m_Spritesheet;
	Monstera::Ref<Monstera::SubTexture2D> m_TextureStairs, m_TextureBarrel, m_TextureTree;


	struct ProfileResult
	{
		const char* Name;
		float Time;
	};

	std::vector< ProfileResult> m_ProfileResults;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };


	ParticleSystem m_ParticleSystem;
	ParticleProps m_Particle;

	uint32_t m_MapWidth, m_MapHeight;
	std::unordered_map<char, Monstera::Ref<Monstera::SubTexture2D>> s_TextureMap;
};