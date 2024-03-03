#pragma once

#include "Monstera/Core/Core.h"
#include "Monstera/Core/Timestep.h"
#include "Monstera/Events/Event.h"

namespace Monstera
{

	class MONSTERA_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		const std::string& getName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}