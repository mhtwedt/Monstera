#include "mdpch.h"

#include "RendererAPI.h"

namespace Monstera {

	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;


	void RendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
	}

}