#include "mdpch.h"
#include "Application.h"


#include "GLFW/glfw3.h"

namespace Monstera
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		// because this is an explicit constructor, we have to use std::unique_ptr<Window>(Window::Create());
		// meaning we dont have to delete the window ourselves when the application terminates?
		// "Application is a singlton, meaning we only have one application for our application so this is fine?"

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		// used to log events
		MD_CORE_TRACE("{0}", e);
	}

	void Application::Run()
	{
		// Event testing
		// WindowResizeEvent e(1280, 720);
		// MD_TRACE(e);

		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}

	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}