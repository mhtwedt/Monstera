#pragma once

#include "Monstera/Core/Core.h"

namespace Monstera {

	class MONSTERA_API Input
	{
	protected:
		Input() = default;

	public:
		Input(const Input&) = delete; // Made input a true singleton ????
		Input& operator=(const Input&) = delete;

		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }

		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }

		inline static bool GetMouseX(int button) { return s_Instance->GetMouseXImpl(); }
		inline static bool GetMouseY(int button) { return s_Instance->GetMouseYImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0; // This is what we implement per platform

		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		static Scope<Input> s_Instance;

	};


}