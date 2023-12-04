#pragma once

#include "Core.h"
#include "Window.h"

#include "Monstera/LayerStack.h"
#include "Monstera/Events/Event.h"
#include "Monstera/Events/ApplicationEvent.h"

#include "Monstera/ImGui/ImGuiLayer.h"

#include "Monstera/Renderer/Shader.h"
#include "Monstera/Renderer/Buffer.h"
#include "Monstera/Renderer/VertexArray.h"

namespace Monstera {


	class MONSTERA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;

		LayerStack m_LayerStack;


		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_ShaderSquare;
		std::shared_ptr<VertexArray> m_SquareVA;

	private:
		static Application* s_Instance;
	};

	// To be defined in client
	Application* CreateApplication();

}