#pragma once

#include "Monstera/Core/Layer.h"

#include "Monstera/Events/KeyEvent.h"
#include "Monstera/Events/MouseEvent.h"
#include "Monstera/Events/ApplicationEvent.h"

namespace Monstera {

	class MONSTERA_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;

	};

}