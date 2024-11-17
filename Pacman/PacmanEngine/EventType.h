#pragma once

#include <cstdint>
#include <string_view>


namespace pac
{
	enum class EventType : uint8_t
	{
		KeyPressed,
		PowerUp,
		SceneOver,
		_Count
	};

	std::string_view GetEventTypeName(EventType type);
}
