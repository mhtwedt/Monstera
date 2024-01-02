#pragma once

#include "Monstera/Core/Core.h"

#ifdef MD_PLATFORM_WINDOWS

extern Monstera::Application* Monstera::CreateApplication();

int main(int argc, char** argv)
{
	//Temporary as this should be where the engine is initialized
	// also note this is included in sandbox
	Monstera::Log::Init();
	//MD_CORE_WARN("Initialized Log");
	//int h = 5;
	//MD_INFO("Initialized Log, var h: {0}",h);
	// printf("Monstera EntryPoint\n");

	MD_INFO("To utilize the JSON profiling, go to chrome::/tracing");
	MD_PROFILE_BEGIN_SESSION("Startup", "MonsteraProfile-Startup.json");
	auto app = Monstera::CreateApplication();
	MD_PROFILE_END_SESSION();
	
	MD_PROFILE_BEGIN_SESSION("Runtime", "MonsteraProfile-Runtime.json");
	app->Run();
	MD_PROFILE_END_SESSION();
	
	MD_PROFILE_BEGIN_SESSION("Shutdown", "MonsteraProfile-Shutdown.json");
	delete app;
	MD_PROFILE_END_SESSION();
}

#endif
