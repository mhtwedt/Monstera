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

		virtual void OnEvent(Event& event) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }
		void SetDarkThemeColors();
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;

	};

}