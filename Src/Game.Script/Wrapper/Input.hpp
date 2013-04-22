#pragma once
#pragma managed
#include <Engine/Data.hpp>

namespace Game
{
	public enum class EventType
	{
		kMouse,
		kKeyboard,
		kPosition
	};

	public ref class Event
	{
	public:

		Event(EventType type) : Type(type){}

		EventType Type;
	};

	public ref class KeyboardEvent : Event
	{
	public :
		KeyboardEvent(unsigned char key, bool pressed) : Event(EventType::kKeyboard), Key(key), Pressed(pressed){}

		unsigned char Key;
		bool	      Pressed;
	};

	public ref class MouseEvent : Event
	{
	public :
		MouseEvent(unsigned char key, bool pressed) : Event(EventType::kMouse), Key(key), Pressed(pressed){}

		unsigned char Key;
		bool	      Pressed;
	};

	public ref class MousePositionEvent : Event
	{
	public :
		MousePositionEvent(unsigned int x, unsigned int y, unsigned int z) : Event(EventType::kPosition), X(x), Y(y), Z(z){}

		unsigned int X;
		unsigned int Y;
		unsigned int Z;
	};

	public ref class Input
	{
	public:

		static Event^ Poll();
		static void Push(Event^ ev);

	private:

		static System::Collections::Generic::LinkedList<Event^>^ _events = gcnew System::Collections::Generic::LinkedList<Event^>();
	};
}