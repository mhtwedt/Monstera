#include <Monstera.h>

#include "imgui/imgui.h"

class ExampleLayer : public Monstera::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-5.0f, 5.0f, -5.0f, 5.0f), m_CameraPosition(0.0f, 0.0f, 0.0f)
	{
		// Create Vertex Array
		m_VertexArray.reset(Monstera::VertexArray::Create());

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

		std::shared_ptr<Monstera::VertexBuffer> vertexBuffer;
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

		std::shared_ptr<Monstera::IndexBuffer> indexBuffer;
		indexBuffer.reset(Monstera::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);



		//Create a square
		m_SquareVA.reset(Monstera::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f,  0.0f,
			 0.75f, -0.75f,  0.0f,
			 0.75f,  0.75f,  0.0f,
			-0.75f,  0.75f,  0.0f

		};

		std::shared_ptr<Monstera::VertexBuffer> squareVB;
		squareVB.reset(Monstera::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));


		squareVB->SetLayout({
			{	Monstera::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);


		uint32_t squareIndices[6] = {
			0, 1, 2, 2, 3, 0
		};
		std::shared_ptr<Monstera::IndexBuffer> squareIB;
		squareIB.reset(Monstera::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));


		m_SquareVA->SetIndexBuffer(squareIB);


		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;			
			layout(location = 1) in vec4 a_Color;			

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

		m_Shader.reset(new Monstera::Shader(vertexSrc, fragmentSrc));

		std::string vertexSrcSquare = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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


		m_ShaderSquare.reset(new Monstera::Shader(vertexSrcSquare, fragmentSrcSquare));
	}

	void OnUpdate(Monstera::Timestep ts) override
	{
		MD_TRACE("Delta time: {0}s [{1}ms]", ts.GetSeconds(), ts.GetMilliseconds());

		if (Monstera::Input::IsKeyPressed(MD_KEY_A))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Monstera::Input::IsKeyPressed(MD_KEY_D))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		if (Monstera::Input::IsKeyPressed(MD_KEY_W))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Monstera::Input::IsKeyPressed(MD_KEY_S))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Monstera::Input::IsKeyPressed(MD_KEY_Q))
			m_CameraRotation += m_CameraRotateSpeed * ts;
		else if (Monstera::Input::IsKeyPressed(MD_KEY_E))
			m_CameraRotation -= m_CameraRotateSpeed * ts;

		Monstera::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
		Monstera::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		{
			Monstera::Renderer::BeginScene(m_Camera);

			Monstera::Renderer::Submit(m_ShaderSquare, m_SquareVA);
			Monstera::Renderer::Submit(m_Shader, m_VertexArray);

			Monstera::Renderer::EndScene();


			// Renderer::Flush(); // Usually done on a separate thread when we're multithreaded
		}
	}

	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(Monstera::Event& event) override
	{

	}



private:
	std::shared_ptr<Monstera::Shader> m_Shader;
	std::shared_ptr<Monstera::VertexArray> m_VertexArray;

	std::shared_ptr<Monstera::Shader> m_ShaderSquare;
	std::shared_ptr<Monstera::VertexArray> m_SquareVA;

	Monstera::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0;

	float m_CameraMoveSpeed = 1.0f;
	float m_CameraRotateSpeed = 5.0f;

};

class Sandbox : public Monstera::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};



Monstera::Application* Monstera::CreateApplication()
{
	return new Sandbox();

}