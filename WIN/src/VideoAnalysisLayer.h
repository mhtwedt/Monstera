#pragma once

#include "Monstera.h"
#include "Panels/SceneStatisticsPanel.h"

#include "Monstera/Renderer/EditorCamera.h" // Not needed?


namespace Monstera
{
	class VideoAnalysisLayer : public Layer
	{
	public:
		VideoAnalysisLayer();
		virtual ~VideoAnalysisLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;

	private:
		bool OnKeyPressed(KeyPressedEvent& e);

		void NewScene();
		void OpenScene();
		void ImportVideo();
		void SaveSceneAs();

	private:
		OrthographicCameraController m_CameraController;


		Ref<VertexArray> m_SquareVA;
		Ref<Shader> m_FlatColorShader;

		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;

		Entity m_CameraEntity;
		Entity m_SecondCamera;

		bool m_PrimaryCamera = true;

		EditorCamera m_EditorCamera;

		Ref<Framebuffer> m_Framebuffer;

		bool m_ViewportFocused = false, m_ViewportHovered = false;

		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

		int m_ImGuizmoType = -1;

		struct ProfileResult
		{
			const char* Name;
			float Time;
		};

		std::vector< ProfileResult> m_ProfileResults;

		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };


		uint32_t m_MapWidth, m_MapHeight;
		std::unordered_map<char, Ref<SubTexture2D>> s_TextureMap;

		// Panels
		SceneStatisticsPanel m_StatisticsPanel;

	};
}