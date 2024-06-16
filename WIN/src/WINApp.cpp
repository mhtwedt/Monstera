#include <Monstera.h>
#include <Monstera/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VideoAnalysisLayer.h"

namespace Monstera {

	class WINApp : public Application
	{
	public:
		WINApp()
			: Application("Monstera Editor")
		{
			PushLayer(new VideoAnalysisLayer());
		}

		~WINApp()
		{

		}

	};



	Application* CreateApplication()
	{
		return new WINApp();

	}
}