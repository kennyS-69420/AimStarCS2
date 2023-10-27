#pragma once
#include "..\Entity.h"
#include "..\MenuConfig.hpp"

namespace NoFlash
{

	inline void Run(const CEntity& aLocalPlayer) noexcept
	{
		if (!MenuConfig::NoFlash)
			return;

		float duration = 0.0f;
		ProcessMgr.WriteMemory(aLocalPlayer.Pawn.Address + Offset::Pawn.flFlashDuration, duration);
	}
}
