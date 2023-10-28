#pragma once
#include "..\Render.hpp"
#include "..\MenuConfig.hpp"
#include "..\Cheats.h"

namespace ESP
{
	ImVec4 GetBoxRect(const CEntity& Entity, int BoxType)
	{
		ImVec4 Rect;
		switch (BoxType)
		{
		case 0:
			Rect = Render::Get2DBox(Entity);
			break;
		case 1:
			Rect = Render::Get2DBoneRect(Entity);
			break;
		case 2:
			Rect = Render::Get2DBox(Entity);
			break;
		default:
			break;
		}

		return Rect;
	}

	void RenderPlayerESP(const CEntity& Entity, ImVec4 Rect)
	{
		Render::DrawBone(Entity, MenuConfig::BoneColor, 1.3f);
		Render::ShowPenis(Entity, MenuConfig::PenisLength, MenuConfig::PenisColor, MenuConfig::PenisSize);
		Render::ShowLosLine(Entity, 50.0f, MenuConfig::EyeRayColor, 1.3f);
		Render::DrawHeadCircle(Entity, MenuConfig::HeadBoxColor);

		// box
		if (MenuConfig::ShowBoxESP)
		{
			if (MenuConfig::BoxType == 2)
			{
				Gui.RectangleFilled({ Rect.x,Rect.y }, { Rect.z,Rect.w }, MenuConfig::BoxColor, MenuConfig::BoxRounding);
			}
			else
			{
				Gui.Rectangle({ Rect.x,Rect.y }, { Rect.z,Rect.w }, { 0,0,0,255 }, 3, MenuConfig::BoxRounding);
				Gui.Rectangle({ Rect.x,Rect.y }, { Rect.z,Rect.w }, MenuConfig::BoxColor, 1.3, MenuConfig::BoxRounding);
			}

		}
		Render::LineToEnemy(Rect, MenuConfig::LineToEnemyColor, 1.2);

		if (MenuConfig::ShowWeaponESP)
			Gui.StrokeText(Entity.Pawn.WeaponName, { Rect.x + Rect.z / 2,Rect.y + Rect.w }, ImColor(255, 255, 255, 255), 14, true);

		if (MenuConfig::ShowPlayerName)
		{
			if (MenuConfig::HealthBarType == 0)
				Gui.StrokeText(Entity.Controller.PlayerName, { Rect.x + Rect.z / 2,Rect.y - 14 }, ImColor(255, 255, 255, 255), 14, true);
			else
				Gui.StrokeText(Entity.Controller.PlayerName, { Rect.x + Rect.z / 2,Rect.y - 13 - 14 }, ImColor(255, 255, 255, 255), 14, true);
		}
	}

	void PreviewWindow()
	{
		if (!MenuConfig::ShowPreview)
			return;

		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
		ImGui::SetNextWindowSize(ImVec2(200, 250), ImGuiCond_FirstUseEver);
		const auto& window = ImGui::FindWindowByName("AimStar");
//		ImGui::SetNextWindowPos(ImVec2(window->Pos.x + window->Size.x - 250, window->Pos.y + 100), ImGuiCond_Always);
		ImGui::SetNextWindowPos(ImVec2(window->Pos.x + window->Size.x + ImGui::GetStyle().WindowPadding.x, window->Pos.y));
		ImGui::Begin("ESP Preview", nullptr, windowFlags);

		ImVec2 windowSize = ImGui::GetWindowSize();
		ImVec2 rectSize(100, 150);
		ImVec2 rectPos((windowSize.x - rectSize.x) * 0.45f, (windowSize.y - rectSize.y) * 0.3f);
		ImVec2 centerPos = ImGui::GetCursorScreenPos();
		centerPos.x += rectPos.x;
		centerPos.y += rectPos.y;

		if (MenuConfig::ShowBoxESP) {
			ImU32 boxColor = MenuConfig::BoxColor;
			ImVec2 rectStartPos = centerPos;
			ImVec2 rectEndPos(rectStartPos.x + rectSize.x, rectStartPos.y + rectSize.y);
			ImGui::GetWindowDrawList()->AddRect(rectStartPos, rectEndPos, MenuConfig::BoxColor & IM_COL32_A_MASK, 0.0f, ImDrawCornerFlags_All, 2.0f);
			ImGui::GetWindowDrawList()->AddRect(rectStartPos, rectEndPos, boxColor, 0.0f, ImDrawCornerFlags_All, 1.0f);
		}
		if (MenuConfig::ShowEyeRay) {
			ImU32 EyeC = MenuConfig::EyeRayColor;
			ImVec2 lineStart(centerPos.x + 44, centerPos.y + 15);
			ImVec2 lineEnd(centerPos.x - 10, centerPos.y + 15);
			ImGui::GetWindowDrawList()->AddLine(lineStart, lineEnd, EyeC, 2.0f);
		}
		if (MenuConfig::ShowBoneESP) {
			ImU32 boneColor = MenuConfig::BoneColor;
			ImVec2 NeckStart(centerPos.x + 44, centerPos.y + 15);
			ImVec2 NeckEnd(centerPos.x + 50, centerPos.y + 25);
			ImGui::GetWindowDrawList()->AddLine(NeckStart, NeckEnd, boneColor, 1.8f); // Head to Neck
			ImVec2 SpineStart(centerPos.x + 50, centerPos.y + 25);
			ImVec2 SpineEnd(centerPos.x + 60, centerPos.y + 55);
			ImGui::GetWindowDrawList()->AddLine(SpineStart, SpineEnd, boneColor, 1.8f); // Neck to Spine
			ImVec2 PelvisStart(centerPos.x + 60, centerPos.y + 55);
			ImVec2 PelvisEnd(centerPos.x + 62, centerPos.y + 65);
			ImGui::GetWindowDrawList()->AddLine(PelvisStart, PelvisEnd, boneColor, 1.8f); // Spine to Pelvis
			ImVec2 UL_LegStart(centerPos.x + 62, centerPos.y + 65);
			ImVec2 UL_LegEnd(centerPos.x + 65, centerPos.y + 70);
			ImGui::GetWindowDrawList()->AddLine(UL_LegStart, UL_LegEnd, boneColor, 1.8f); // Left Leg_Up
			ImVec2 ML_LegStart(centerPos.x + 65, centerPos.y + 70);
			ImVec2 ML_LegEnd(centerPos.x + 60, centerPos.y + 100);
			ImGui::GetWindowDrawList()->AddLine(ML_LegStart, ML_LegEnd, boneColor, 1.8f); // Left Leg_Mid
			ImVec2 DL_LegStart(centerPos.x + 60, centerPos.y + 100);
			ImVec2 DL_LegEnd(centerPos.x + 68, centerPos.y + 145);
			ImGui::GetWindowDrawList()->AddLine(DL_LegStart, DL_LegEnd, boneColor, 1.8f); // Left Leg_Down
			ImVec2 UR_LegStart(centerPos.x + 62, centerPos.y + 65);
			ImVec2 UR_LegEnd(centerPos.x + 35, centerPos.y + 100);
			ImGui::GetWindowDrawList()->AddLine(UR_LegStart, UR_LegEnd, boneColor, 1.8f); // Right Leg_Up
			ImVec2 DR_LegStart(centerPos.x + 35, centerPos.y + 100);
			ImVec2 DR_LegEnd(centerPos.x + 47, centerPos.y + 130);
			ImGui::GetWindowDrawList()->AddLine(DR_LegStart, DR_LegEnd, boneColor, 1.8f); // Right Leg_Down
			ImVec2 L_ScapulaStart(centerPos.x + 50, centerPos.y + 25);
			ImVec2 L_ScapulaEnd(centerPos.x + 60, centerPos.y + 30);
			ImGui::GetWindowDrawList()->AddLine(L_ScapulaStart, L_ScapulaEnd, boneColor, 1.8f); // Left Scapula
			ImVec2 UL_ArmStart(centerPos.x + 60, centerPos.y + 30);
			ImVec2 UL_ArmEnd(centerPos.x + 45, centerPos.y + 55);
			ImGui::GetWindowDrawList()->AddLine(UL_ArmStart, UL_ArmEnd, boneColor, 1.8f); // Left Arm_Up
			ImVec2 DL_ArmStart(centerPos.x + 45, centerPos.y + 55);
			ImVec2 DL_ArmEnd(centerPos.x + 25, centerPos.y + 45);
			ImGui::GetWindowDrawList()->AddLine(DL_ArmStart, DL_ArmEnd, boneColor, 1.8f); // Left Arm_Down
			ImVec2 R_ScapulaStart(centerPos.x + 50, centerPos.y + 25);
			ImVec2 R_ScapulaEnd(centerPos.x + 40, centerPos.y + 30);
			ImGui::GetWindowDrawList()->AddLine(R_ScapulaStart, R_ScapulaEnd, boneColor, 1.8f); // Right Scapula
			ImVec2 UR_ArmStart(centerPos.x + 40, centerPos.y + 30);
			ImVec2 UR_ArmEnd(centerPos.x + 27, centerPos.y + 53);
			ImGui::GetWindowDrawList()->AddLine(UR_ArmStart, UR_ArmEnd, boneColor, 1.8f); // Right Arm_Up
			ImVec2 DR_ArmStart(centerPos.x + 27, centerPos.y + 53);
			ImVec2 DR_ArmEnd(centerPos.x + 20, centerPos.y + 45);
			ImGui::GetWindowDrawList()->AddLine(DR_ArmStart, DR_ArmEnd, boneColor, 1.8f); // Right Arm_Down
			
		}
		if (MenuConfig::ShowHeadBox) {
			ImGui::GetWindowDrawList()->AddCircle({ centerPos.x + 44, centerPos.y + 17 }, 10.0f, MenuConfig::HeadBoxColor, 0, 1.8f);
		}
		if (MenuConfig::ShowHealthBar) {
			ImU32 greenColor = IM_COL32(0, 255, 0, 255);
			if (MenuConfig::HealthBarType == 0) {
				ImVec2 HBS(centerPos.x - 8, centerPos.y);
				ImVec2 HBE(centerPos.x - 3, centerPos.y + rectSize.y);
				ImGui::GetWindowDrawList()->AddRectFilled(HBS, HBE, ImColor(96, 246, 113, 220), 0.0f, ImDrawCornerFlags_All);
			}
			if (MenuConfig::HealthBarType == 1) {
				ImVec2 HBS(centerPos.x, centerPos.y - 6);
				ImVec2 HBE(centerPos.x + rectSize.x, centerPos.y - 3);
				ImGui::GetWindowDrawList()->AddRectFilled(HBS, HBE, ImColor(96, 246, 113, 220), 0.0f, ImDrawCornerFlags_All);
			}
			if (MenuConfig::HealthBarType == 2) {
				ImVec2 HBS(centerPos.x, centerPos.y + rectSize.y + 6);
				ImVec2 HBE(centerPos.x + rectSize.x, centerPos.y + rectSize.y + 3);
				ImGui::GetWindowDrawList()->AddRectFilled(HBS, HBE, ImColor(96, 246, 113, 220), 0.0f, ImDrawCornerFlags_All);
			}
		}
		if (MenuConfig::ShowPlayerName) {
			if (MenuConfig::HealthBarType == 0 || MenuConfig::HealthBarType == 2) {
				ImVec2 textPos(centerPos.x + 18, centerPos.y - 18);
				ImGui::GetWindowDrawList()->AddText(textPos, IM_COL32(255, 255, 255, 255), "PlayerName");
			}
			if (MenuConfig::HealthBarType == 1) {
				ImVec2 textPos(centerPos.x + 18, centerPos.y - 22);
				ImGui::GetWindowDrawList()->AddText(textPos, IM_COL32(255, 255, 255, 255), "PlayerName");
			}
		}
		if (MenuConfig::ShowDistance) {
			ImVec2 textPos(centerPos.x + 105, centerPos.y);
			ImGui::GetWindowDrawList()->AddText(textPos, IM_COL32(255, 204, 0, 255), "20m");
		}
		if (MenuConfig::ShowWeaponESP) {
			if (MenuConfig::HealthBarType == 2) {
				ImVec2 textPos(centerPos.x + 29, centerPos.y + 155);
				ImGui::GetWindowDrawList()->AddText(textPos, IM_COL32(255, 255, 255, 255), "Weapon");
			}
			if (MenuConfig::HealthBarType == 0 || MenuConfig::HealthBarType == 1) {
				ImVec2 textPos(centerPos.x + 29, centerPos.y + 150);
				ImGui::GetWindowDrawList()->AddText(textPos, IM_COL32(255, 255, 255, 255), "Weapon");
			}
		}
		ImGui::End();
	}
}