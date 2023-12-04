#include "mdpch.h"
#include "Buffer.h"


#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

/* can adjust compiled .h files for supported platforms
#if MD_PLATFORM_WINDOWS
	#include "Platform/Direct3D/Direct3DBuffer.h"
#endif
*/

namespace Monstera
{

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:		MD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::OpenGL:	return new OpenGLVertexBuffer(vertices, size);

			/* can adjust cases for supported platforms
			#if MD_PLATFORM_WINDOWS
				case RendererAPI::OpenGL:	return new OpenGLVertexBuffer(vertices, size);
			#endif
			*/
		}
		
		 MD_CORE_ASSERT(false, "Unknown Renderer API!");
		 return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:		MD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGL:	return new OpenGLIndexBuffer(indices, size);

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