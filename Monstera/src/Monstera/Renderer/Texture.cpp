#include "mdpch.h"
#include "Texture.h"


#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Monstera {



	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{


		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	MD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLTexture2D>(path);

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