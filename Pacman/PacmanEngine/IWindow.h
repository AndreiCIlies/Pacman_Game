#pragma once

#include "Textures.h"
#include "Position.h"
#include "IEvent.h"

#include <string>
#include <vector>
#include <memory>


namespace pac
{
	class IWindow
	{
	public:
		virtual ~IWindow() = default;
		virtual void DrawScore(ScoreType score) = 0;
		virtual void DrawTexture(Position position, Textures texture) = 0;
		virtual bool IsOpen() const = 0;
		virtual bool ShouldClose() const = 0;
		virtual void Clear() const = 0;
		virtual void Display() = 0;
		virtual void Close() = 0;
		virtual std::vector<std::unique_ptr<IEvent>> GetEvents() = 0;
	};
}
