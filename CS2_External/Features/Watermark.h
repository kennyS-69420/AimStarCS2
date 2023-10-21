#pragma once
#include "..\OS-ImGui\imgui\imgui.h"
#include "..\Utils\GlobalVars.h"
#include "..\MenuConfig.hpp"

namespace Watermark
{

	inline void Render() noexcept
	{
		if (!MenuConfig::WaterMark)
			return;

		globalvars GV;
		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize;
		ImGui::SetNextWindowBgAlpha(0.3f);
		ImGui::Begin("Watermark", nullptr, windowFlags);

		static auto FrameRate = 1.0f;
		FrameRate = 0.9f * FrameRate + 0.1f * GV.GetFrameCount();

		ImGui::Text("AimStar | %d fps", FrameRate != 0.0f ? static_cast<int>(1 / FrameRate) : 0);
		ImGui::End();
	}
}