#include "Pacman.h"
#include "Logger/Logger.h"
#include "KeyPressedEvent.h"


pac::Pacman::Pacman(Position initialPosition, TicksType ticksPerMove, TicksType powerUpDuration)
	: mPosition(initialPosition)
	, mDirection()
	, mNextDirection()
	, mTick(static_cast<TicksType>(-1))
	, mTicksPerMove(ticksPerMove)
	, mPowerUpDuration(powerUpDuration)
	, mLastPowerUpStart(0)
{
	// empty
}

pac::ScoreType pac::Pacman::TryMove(Maze& maze)
{
	++mTick;
	if (mTick % mTicksPerMove == 0)
	{
		return 0;
	}

	if (!mPosition.IsValid())
	{
		throw std::runtime_error(std::format("Pacman current position ( {}, {} ) is invalid", mPosition.row, mPosition.col));
	}

	if (mNextDirection.IsValid())
	{
		Position newPosition = Add(mPosition, mNextDirection);
		if (newPosition.IsValid() && maze.GetCellType(newPosition) == CellType::Empty)
		{
			mDirection = mNextDirection;
			mNextDirection = Direction::GetInvalid();
		}
	}

	if (mDirection.IsValid())
	{
		Position newPosition = Add(mPosition, mDirection);
		if (maze.GetCellType(newPosition) == CellType::Coin
			|| maze.GetCellType(newPosition) == CellType::PowerUp)
		{
			mPosition = newPosition;
			return maze.EatCell(mPosition);
		}
		if (newPosition.IsValid())
		{
			if (maze.IsWalkable(newPosition))
			{
				mPosition = newPosition;
			}
			else
			{
				mDirection = Direction::GetInvalid();
				mNextDirection = Direction::GetInvalid();
			}
		}
	}

	return 0;
}

pac::Position pac::Pacman::GetCurrentPosition() const
{
	return mPosition;
}

void pac::Pacman::SetPowerUp()
{
	mLastPowerUpStart = static_cast<TicksType>(mTick);
}

bool pac::Pacman::IsPoweredUp() const
{
	return mLastPowerUpStart > 0 
		&& mTick - mLastPowerUpStart < mPowerUpDuration;
}

void pac::Pacman::Draw(IWindow* window) const
{
	window->DrawTexture(mPosition, Textures::Pacman);
}

void pac::Pacman::OnEvent(IEvent* event)
{
	if (event->GetType() == EventType::KeyPressed)
	{
		auto keyEvent = dynamic_cast<KeyPressedEvent*>(event);
		if (keyEvent == nullptr)
		{
			throw std::runtime_error("Failed to cast event to KeyPressedEvent");
		}

		Direction& pos = mDirection.IsValid() ? mNextDirection : mDirection;

		switch (keyEvent->GetKeyCode())
		{
		case KeyCode::Up:
		case KeyCode::W:
			pos = Direction::Up();
			break;
		case KeyCode::Down:
		case KeyCode::S:
			pos = Direction::Down();
			break;
		case KeyCode::Left:
		case KeyCode::A:
			pos = Direction::Left();
			break;
		case KeyCode::Right:
		case KeyCode::D:
			pos = Direction::Right();
			break;
		case KeyCode::Unknown:
			Logger::cout.Warning("Unknown key pressed");
			break;
		default:
			Logger::cout.Warning("Unhandled key pressed");
			break;
		}
	}
}