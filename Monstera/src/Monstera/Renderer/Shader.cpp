#include "mdpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Monstera
{
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	MD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLShader>(filepath);

			/* can adjust cases for supported platforms
			#if MD_PLATFORM_WINDOWS
				case RendererAPI::OpenGL:	return new OpenGLVertexBuffer(vertices, size);
			#endif
			*/
		}

		MD_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	MD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);

			/* can adjust cases for supported platforms
			#if MD_PLATFORM_WINDOWS
				case RendererAPI::OpenGL:	return new OpenGLVertexBuffer(vertices, size);
			#endif
			*/
		}

		MD_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		MD_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;

	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}



	Monstera::Ref<Monstera::Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Monstera::Ref<Monstera::Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Monstera::Ref<Monstera::Shader> ShaderLibrary::Get(const std::string& name)
	{
		MD_CORE_ASSERT(Exists(name), "Shader not found!");

		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}