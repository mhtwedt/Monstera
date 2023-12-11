#pragma once

#include "Core.h"
#include "Window.h"

#include "Monstera/LayerStack.h"
#include "Monstera/Events/Event.h"
#include "Monstera/Events/ApplicationEvent.h"

#include "Monstera/ImGui/ImGuiLayer.h"

#include "Monstera/Core/Timestep.h"

namespace Monstera {


	class Application
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

	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;

		LayerStack m_LayerStack;
		float m_LastFrameTime;
	private:
		static Application* s_Instance;
	};

	// To be defined in client
	Application* CreateApplication();

}