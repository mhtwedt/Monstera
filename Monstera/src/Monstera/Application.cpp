#include "mdpch.h"
#include "Application.h"

#include "Monstera/Events/ApplicationEvent.h"
#include "Monstera/Log.h"

namespace Monstera
{
	Application::Application()
	{
		// because this is an explicit constructor, we have to use std::unique_ptr<Window();
		// meaning we dont have to delete the window ourselves when the application terminates?
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		// Event testing
		// WindowResizeEvent e(1280, 720);
		// MD_TRACE(e);

		while (m_Running)
		{
			m_Window->OnUpdate();
		}

	}
}