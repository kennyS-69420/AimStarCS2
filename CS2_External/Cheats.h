#pragma once
#include "Game.h"
#include "Entity.h"
#include "AimBot.hpp"
#include "Radar/Radar.h"
#include "TriggerBot.h"
#include "Bunnyhop.hpp"

#include "Features/NoFlash.h"
#include "Features/Watermark.h"
#include "Features/CheatList.h"
#include "Features/HitSound.h"

namespace Cheats
{
	void KeyCheckThread();

	void RenderCrossHair(ImDrawList* drawList) noexcept;

	void Menu();
	void RadarSetting(Base_Radar& Radar);
	void Run();
}

struct {
	ImFont* normal15px = nullptr;
} fonts;