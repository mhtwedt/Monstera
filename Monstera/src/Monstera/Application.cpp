#include "mdpch.h"
#include "Application.h"

#include <glad/glad.h>

#include "Input.h"

#include "glm/glm.hpp"

namespace Monstera
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Monstera::ShaderDataType::Float:		return GL_FLOAT;
			case Monstera::ShaderDataType::Float2:		return GL_FLOAT;
			case Monstera::ShaderDataType::Float3:		return GL_FLOAT;
			case Monstera::ShaderDataType::Float4:		return GL_FLOAT;
			case Monstera::ShaderDataType::Mat3:		return GL_FLOAT;
			case Monstera::ShaderDataType::Mat4:		return GL_FLOAT;
			case Monstera::ShaderDataType::Int:			return GL_INT;
			case Monstera::ShaderDataType::Int2:		return GL_INT;
			case Monstera::ShaderDataType::Int3:		return GL_INT;
			case Monstera::ShaderDataType::Int4:		return GL_INT;
			case Monstera::ShaderDataType::Bool:		return GL_BOOL;
		}

		MD_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;

	}



	Application::Application()
	{
		MD_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		// because this is an explicit constructor, we have to use std::unique_ptr<Window>(Window::Create());
		// meaning we dont have to delete the window ourselves when the application terminates?
		// "Application is a singlton, meaning we only have one application for our application so this is fine?"

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		// Create Vertex Array
		m_VertexArray.reset(VertexArray::Create());

		// Things necessary for a renderer
		// Vertex Array
		// Vertex Buffer
		// Index Buffer
		// Shader


		// 
		float vertices[3 * 7] = {
			 0.0f,  0.5f,  0.0f,  0.0f,  0.8f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.0f,  0.8f,  0.0f,  0.8f,  1.0f, 
			 0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  0.8f,  1.0f
		}; 

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		// Set Layout
		BufferLayout layout = {
			{	ShaderDataType::Float3, "a_Position" },
			{	ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);


		uint32_t indices[3] = {
			0, 1, 2
		};

		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);



		//Create a square
		m_SquareVA.reset(VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f,  0.0f,
			 0.75f, -0.75f,  0.0f,
			 0.75f,  0.75f,  0.0f,
			-0.75f,  0.75f,  0.0f

		};

		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));


		squareVB->SetLayout({
			{	ShaderDataType::Float3, "a_Position" }
		});
		m_SquareVA->AddVertexBuffer(squareVB);


		uint32_t squareIndices[6] = {
			0, 1, 2, 2, 3, 0
		};
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));


		m_SquareVA->SetIndexBuffer(squareIB);


		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;			
			layout(location = 1) in vec4 a_Color;			

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position =  vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;		

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

		std::string vertexSrcSquare = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;			

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position =  vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrcSquare = R"(
			#version 330 core

			layout(location = 0) out vec4 color;		

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";


		m_ShaderSquare.reset(new Shader(vertexSrcSquare, fragmentSrcSquare));

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
			glClearColor(0.2f, 0.2f, 0.2f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_ShaderSquare->Bind();
			m_SquareVA->Bind();
			glDrawElements(GL_TRIANGLES, m_SquareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);


			m_Shader->Bind();
			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();


			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();


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