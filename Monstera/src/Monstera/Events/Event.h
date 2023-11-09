#pragma once

#include "mdpch.h"
#include "Monstera/Core.h"


namespace Monstera
{
	// Events in Hazel are currently blocking, meaning when an event occurs it 
	// immediately gets dispatched and must be dealt with right then and there.
	// For the future, a better strategy migth be to buffer events in an event
	// bus and process them during the "event" part of the update stage.
	// ie it would be better to have a buffered queue, and not pause other functions

	/// <summary>
	/// EventType integer Enum
	/// </summary>
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	/// <summary>
	/// Event Category enum uses bit shift
	/// so EventCategoryKeyboard = 00100
	/// </summary>
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput		 = BIT(1),
		EventCategoryKeyboard	 = BIT(2),
		EventCategoryMouse		 = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

	
	// Notes on Macros
	// these are used so we can avoid declaring each function in every class
	// saved code may have looked like:
	// static EventType GetStaticType() {return EventType::KeyPressed; } 
	// virtual  EventType GetEventType() const override {return GetStaticType(); }
	// virtual const char* GetName() const override {return "KeyPressed"; }
	// Instead we can just use a macro, like this:
	// EVENT_CLASS_TYPE(KeyPressed)
	// 
	// We are using static types as these dont need to be member functions
	// ie we dont need to have an instance of the keypressed event
	// the reason we need a virtual one, 
	

	// Macros

	//	Current event types:
	// 
	//	None,
	//	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
	//	AppTick, AppUpdate, AppRender,
	//	KeyPressed, KeyReleased,
	//	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::##type; }\
								virtual EventType GetEventType() const override {return GetStaticType(); }\
								virtual const char* GetName() const override {return #type; }

	//  Current Event Categories:
	//
	// 	None
	//	EventCategoryApplication
	//	EventCategoryInput		
	//	EventCategoryKeyboard	
	//	EventCategoryMouse		
	//	EventCategoryMouseButton
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category; }

	class MONSTERA_API Event
	{
		friend class EventDispatcher;
	public:

		bool Handled = false;

		virtual EventType GetEventType() const = 0; // pure virtual meaning every event has to implement them
		virtual const char* GetName() const = 0; // possibly debug only, as const char* is more expensive
		virtual int GetCategoryFlags() const = 0; // possibly debug only, as const char* is more expensive
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

	};

	class EventDispatcher
	{
		template <typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{

		}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}