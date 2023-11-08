#include <Monstera.h>



class Sandbox : public Monstera::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}

};



Monstera::Application* Monstera::CreateApplication()
{
	return new Sandbox();

}