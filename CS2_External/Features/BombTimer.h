#pragma once
#include <chrono>
#include <iostream>
#include <utility>
#include <sstream>
#include <ctime>
#include "..\Entity.h"
#include "..\MenuConfig.hpp"

namespace bmb
{
	bool isPlanted = false;
	std::time_t plantTime;

	uint64_t currentTimeMillis() {
		using namespace std::chrono;
		return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	}

	void RenderWindow()
	{
		if (!MenuConfig::bmbTimer)
			return;

		bool isBombPlanted;
		bool IsBeingDefused;
		float DefuseTime;
		auto plantedAddress = gGame.GetClientDLLAddress() + Offset::GlobalVar.dwPlantedC4 - 0x8;		

		static float windowWidth = 200.0f;
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;
		ImGui::SetNextWindowPos({ (ImGui::GetIO().DisplaySize.x - 200.0f) / 2.0f, 80.0f }, ImGuiCond_Once);
		ImGui::SetNextWindowSize({ windowWidth, 0 }, ImGuiCond_Once);
		if (!MenuConfig::ShowMenu)
			ImGui::SetNextWindowBgAlpha(0.3f);
		ImGui::Begin("Bomb Timer", nullptr, flags);

		ProcessMgr.ReadMemory(plantedAddress, isBombPlanted);
		ProcessMgr.ReadMemory(Offset::GlobalVar.dwPlantedC4 + Offset::PlantedC4.m_bBeingDefused, IsBeingDefused);
		ProcessMgr.ReadMemory(Offset::GlobalVar.dwPlantedC4 + Offset::PlantedC4.m_flDefuseCountDown, DefuseTime);
		std::cout << IsBeingDefused << ", " << DefuseTime << std::endl;

		auto time = currentTimeMillis();

		if (isBombPlanted && !isPlanted && (plantTime == NULL || time - plantTime > 60000))
		{
			isPlanted = true;
			plantTime = time;
		}

		float remaining = (40000 - (int64_t)time + plantTime) / (float)1000;

		if (remaining > 10 || remaining < 0 || !isPlanted)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 196, 0, 255));
		}
		else if (remaining > 5)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 155, 0, 255));
		}
		else {
			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(242, 93, 93, 255));
		}

		
		if (isPlanted && remaining >= 0)
		{
			std::ostringstream ss;
			ss.precision(3);
			ss << std::fixed << remaining << " s";
			Gui.MyText(std::move(ss).str().c_str(), true);
		}
		else {
			Gui.MyText("C4 not planted", true);
		}
		
		ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 180) * 0.5f);
		float barLength = remaining <= 0.0f ? 0.0f : remaining >= 40 ? 1.0f : (remaining / 40.0f);
		Gui.MyProgressBar(barLength, { 180, 15 }, "", MenuConfig::BombTimerCol);

		if (isPlanted && !isBombPlanted)
		{
			isPlanted = false;
		}
		ImGui::PopStyleColor();
		ImGui::End();
	}
}