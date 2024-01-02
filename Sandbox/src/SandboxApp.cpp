#include <Monstera.h>
#include <Monstera/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class ExampleLayer : public Monstera::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f, true)
	{
		// Create Vertex Array
		m_VertexArray = (Monstera::VertexArray::Create());

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

		Monstera::Ref<Monstera::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Monstera::VertexBuffer::Create(vertices, sizeof(vertices)));

		// Set Layout
		Monstera::BufferLayout layout = {
			{	Monstera::ShaderDataType::Float3, "a_Position" },
			{	Monstera::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);


		uint32_t indices[3] = {
			0, 1, 2
		};

		Monstera::Ref<Monstera::IndexBuffer> indexBuffer;
		indexBuffer.reset(Monstera::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);



		//Create a square
		m_SquareVA = Monstera::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f,  0.0f, 0.0f, 1.0f

		};

		Monstera::Ref<Monstera::VertexBuffer> squareVB;
		squareVB.reset(Monstera::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));


		squareVB->SetLayout({
			{	Monstera::ShaderDataType::Float3, "a_Position" },
			{	Monstera::ShaderDataType::Float2, "a_TexCoord" }

			});
		m_SquareVA->AddVertexBuffer(squareVB);


		uint32_t squareIndices[6] = {
			0, 1, 2, 2, 3, 0
		};
		Monstera::Ref<Monstera::IndexBuffer> squareIB;
		squareIB.reset(Monstera::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));


		m_SquareVA->SetIndexBuffer(squareIB);


		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;			
			layout(location = 1) in vec4 a_Color;			

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

		m_Shader = (Monstera::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc));

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;		

			in vec3 v_Position;
				
			uniform vec3 u_Color;			

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";



		m_FlatColorShader = (Monstera::Shader::Create("flatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc));

		auto  textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");


		m_Texture = Monstera::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = Monstera::Texture2D::Create("assets/textures/ChernoLogo.png");


		std::dynamic_pointer_cast<Monstera::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Monstera::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

	}

	void OnUpdate(Monstera::Timestep ts) override
	{
		// Update
		m_CameraController.OnUpdate(ts);

		// Render
		MD_TRACE("Delta time: {0}s [{1}ms]", ts.GetSeconds(), ts.GetMilliseconds());


		Monstera::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
		Monstera::RenderCommand::Clear();


		Monstera::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));


		std::dynamic_pointer_cast<Monstera::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Monstera::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0), pos) * scale;

				Monstera::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Monstera::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_ChernoLogoTexture->Bind();
		Monstera::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle
		//  Monstera::Renderer::Submit(m_Shader, m_VertexArray);

		Monstera::Renderer::EndScene();


		// Renderer::Flush(); // Usually done on a separate thread when we're multithreaded

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Monstera::Event& e) override
	{
		m_CameraController.OnEvent(e);

		if (e.GetEventType() == Monstera::EventType::WindowResize)
		{
			auto& re = (Monstera::WindowResizeEvent&)e;

		//	float zoom = (float)re.GetWidth() / 1280.0f;
		//	m_CameraController.SetZoomLevel(zoom);
		}
	}



private:
	Monstera::ShaderLibrary m_ShaderLibrary;
	Monstera::Ref<Monstera::Shader> m_Shader;
	Monstera::Ref<Monstera::VertexArray> m_VertexArray;

	Monstera::Ref<Monstera::Shader> m_FlatColorShader;
	Monstera::Ref<Monstera::VertexArray> m_SquareVA;

	Monstera::Ref<Monstera::Texture2D> m_Texture, m_ChernoLogoTexture;

	Monstera::OrthographicCameraController m_CameraController;
	glm::vec3 m_CameraPosition;

	glm::vec3 m_SquareColor = { 0.2f, 0.4f, 0.8f };
};

class Sandbox : public Monstera::Application
{
public:
	Sandbox()
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}

};



Monstera::Application* Monstera::CreateApplication()
{
	return new Sandbox();

}