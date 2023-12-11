#include "mdpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Monstera
{

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	MD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return new OpenGLShader(vertexSrc, fragmentSrc);

			/* can adjust cases for supported platforms
			#if MD_PLATFORM_WINDOWS
				case RendererAPI::OpenGL:	return new OpenGLVertexBuffer(vertices, size);
			#endif
			*/
		}

		MD_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

}