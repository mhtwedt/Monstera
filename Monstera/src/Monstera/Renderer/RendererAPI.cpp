#include "mdpch.h"

#include "RendererAPI.h"

namespace Monstera {

	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;


	void RendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
	}

}