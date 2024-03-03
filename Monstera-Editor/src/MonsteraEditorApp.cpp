#include <Monstera.h>
#include <Monstera/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "EditorLayer.h"

namespace Monstera {

	class MonsteraEditor : public Application
	{
	public:
		MonsteraEditor()
			: Application("Monstera Editor")
		{
			PushLayer(new EditorLayer());
		}

		~MonsteraEditor()
		{

		}

	};



	Application* CreateApplication()
	{
		return new MonsteraEditor();

	}
}