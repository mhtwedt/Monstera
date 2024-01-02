#include "mdpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Monstera {
	
	
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_windowHandle(windowHandle)
	{
		MD_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		MD_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		MD_CORE_ASSERT(status, "Failed to initialize Glad");

		MD_CORE_INFO("OpenGL Info");
		MD_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		MD_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		MD_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));

		#ifdef MD_ENABLE_ASSERTS
			int versionMajor;
			int versionMinor;
			glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
			glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

			MD_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Monstera requires at least OpenGL Version 4.5");
		#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		MD_PROFILE_FUNCTION();

		glfwSwapBuffers(m_windowHandle);
	}
}
