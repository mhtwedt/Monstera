#pragma once

#ifdef MD_PLATFORM_WINDOWS

extern Monstera::Application* Monstera::CreateApplication();

int main(int argc, char** argv)
{
	//Temporary as this should be where the engine is initialized
	// also note this is included in sandbox
	Monstera::Log::Init();
	MD_CORE_WARN("Initialized Log");
	int h = 5;
	MD_INFO("Initialized Log, var h: {0}",h);


	// printf("Monstera EntryPoint\n");
	auto app = Monstera::CreateApplication();
	app->Run();
	delete app;

}

#endif
