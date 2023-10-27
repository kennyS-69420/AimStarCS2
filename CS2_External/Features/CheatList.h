#pragma once
#include "..\OS-ImGui\imgui\imgui.h"
#include "..\MenuConfig.hpp"

namespace CheatList
{
	static inline void CheatText(const char* Cheat, bool config)
	{
		if (config)
			ImGui::Text(Cheat);
	}

	inline void Render() noexcept
	{
		if (!MenuConfig::CheatList)
			return;

		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse;
		ImGui::SetNextWindowBgAlpha(0.3f);
		ImGui::SetNextWindowSize(ImVec2(200, 0));
		ImGui::Begin("Cheats List", nullptr, windowFlags);

		CheatText("ESP", MenuConfig::ESPenbled);
		if (MenuConfig::AimBot && (MenuConfig::AimAlways || GetAsyncKeyState(AimControl::HotKey)))
			ImGui::Text("Aimbot [Toggle]");
		CheatText("RCS", MenuConfig::RCS);
		CheatText("Radar", MenuConfig::ShowRadar);
		if (MenuConfig::TriggerBot && (MenuConfig::TriggerAlways || GetAsyncKeyState(MenuConfig::TriggerHotKey)))
			ImGui::Text("TriggerBot [Toggle]");

		CheatText("Crosshair", CrosshairConfig::ShowCrossHair);
		CheatText("Headshot Line", MenuConfig::ShowHeadShootLine);
		CheatText("No Flash", MenuConfig::NoFlash);
		CheatText("Bhop", MenuConfig::BunnyHop);
		CheatText("HitSound", MenuConfig::HitSound);


		ImGui::End();
	}
}