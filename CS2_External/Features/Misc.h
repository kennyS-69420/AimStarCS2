#pragma once
#include <Windows.h>
#include <time.h>

#include "..\OS-ImGui\imgui\imgui.h"
#include "..\Utils\GlobalVars.h"
#include "..\MenuConfig.hpp"
#include "..\AimBot.hpp"
#include "..\Entity.h"

#pragma comment(lib, "winmm.lib")

namespace Misc
{
	static inline void CheatText(const char* Cheat, bool config)
	{
		if (config)
			ImGui::Text(Cheat);
	}

	static inline void getCurrentTime(struct tm* ptm) {
		time_t now = time(NULL);
		localtime_s(ptm, &now);
	}

	void CheatList() noexcept;
	void Watermark() noexcept;
	void HitSound(const CEntity& aLocalPlayer, int& PreviousTotalHits) noexcept;
	void NoFlash(const CEntity& aLocalPlayer) noexcept;
}