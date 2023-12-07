#include "mdpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Monstera {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}