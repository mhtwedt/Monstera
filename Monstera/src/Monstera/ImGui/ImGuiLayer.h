#pragma once

#include "Monstera/Layer.h"

namespace Monstera {

	class MONSTERA_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDettach();
		void OnUpdate();
		void OnEvent(Event& event);
	private:
		float m_Time = 0.0f;

	};

}