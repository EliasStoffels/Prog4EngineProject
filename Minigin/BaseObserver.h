#pragma once
#include <cstdint>

namespace dae
{
	unsigned int sdbm_hash(const char* str);


	struct EventArg {};
	using EventId = unsigned int;
	struct Event {
		const EventId id;
		static const uint8_t MAX_ARGS = 8;
		uint8_t nbArgs;
		EventArg args[MAX_ARGS];
		explicit Event(EventId _id) : id{ _id } {}
	};

	class GameObject;
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(const Event& event, GameObject* object) = 0;
	};
}


