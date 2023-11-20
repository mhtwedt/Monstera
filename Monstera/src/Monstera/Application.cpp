#include "mdpch.h"
#include "Application.h"

#include <glad/glad.h>

#include "Input.h"

#include "glm/glm.hpp"

namespace Monstera
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		MD_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		// because this is an explicit constructor, we have to use std::unique_ptr<Window>(Window::Create());
		// meaning we dont have to delete the window ourselves when the application terminates?
		// "Application is a singlton, meaning we only have one application for our application so this is fine?"

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverLay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		// used to log events
		// MD_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
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

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

		//	auto [x, y] = Input::GetMousePosition();
		//	MD_CORE_TRACE("Input Polling example: {0}, {1}", x, y); // This is run with WindowsInput

		//	bool ctrlkey = Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL);
		//	MD_CORE_TRACE("Input Polling example is ctrl pressed: {0}", ctrlkey); // This is run with WindowsInput

			m_Window->OnUpdate();
		}

	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}