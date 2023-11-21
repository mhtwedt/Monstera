#pragma once

#include "Core.h"
#include "Window.h"

#include "Monstera/LayerStack.h"
#include "Monstera/Events/Event.h"
#include "Monstera/Events/ApplicationEvent.h"

#include "Monstera/ImGui/ImGuiLayer.h"

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
		std::unique_ptr<ImGuiLayer> m_ImGuiLayer;

		bool m_Running = true;

		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};

	// To be defined in client
	Application* CreateApplication();

}