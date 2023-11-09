#pragma once

#include "Core.h"
#include "Window.h"

#include "Monstera/LayerStack.h"
#include "Monstera/Events/Event.h"
#include "Monstera/Events/ApplicationEvent.h"




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

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		LayerStack m_LayerStack;
	};

	// To be defined in client
	Application* CreateApplication();

}