#include "mdpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Monstera
{

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		MD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return new OpenGLVertexArray();

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