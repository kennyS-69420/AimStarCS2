#pragma once
#include "..\Render.hpp"
#include "..\MenuConfig.hpp"
#include "..\Cheats.h"
#define ICON_FA_EYE "\xef\x81\xae"

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
		case 3:
			Rect = Render::Get2DBox(Entity);
		default:
			break;
		}

		return Rect;
	}

	void RenderPlayerESP(const CEntity& LocalEntity, const CEntity& Entity, ImVec4 Rect, int LocalPlayerControllerIndex, int Index)
	{
		Render::DrawBone(Entity, ESPConfig::BoneColor, 1.3f);
		Render::ShowPenis(Entity, ESPConfig::PenisLength, ESPConfig::PenisColor, ESPConfig::PenisSize);
		Render::ShowLosLine(Entity, 50.0f, ESPConfig::EyeRayColor, 1.3f);
		Render::DrawHeadCircle(Entity, ESPConfig::HeadBoxColor);

		// box
		if (ESPConfig::ShowBoxESP)
		{
			ImColor FlatBoxCol = { ESPConfig::BoxColor.Value.x, ESPConfig::BoxColor.Value.y, ESPConfig::BoxColor.Value.z, ESPConfig::BoxAlpha };
			ImColor FlatBoxVisCol = { ESPConfig::VisibleColor.Value.x, ESPConfig::VisibleColor.Value.y, ESPConfig::VisibleColor.Value.z, ESPConfig::BoxAlpha };
			switch (MenuConfig::BoxType)
			{
			case 0:
				if (((Entity.Pawn.bSpottedByMask & (DWORD64(1) << LocalPlayerControllerIndex)) || (LocalEntity.Pawn.bSpottedByMask & (DWORD64(1) << Index))) && ESPConfig::VisibleCheck)
				{
					Gui.Rectangle({ Rect.x,Rect.y }, { Rect.z,Rect.w }, ESPConfig::VisibleColor & IM_COL32_A_MASK, 3, ESPConfig::BoxRounding);
					Gui.Rectangle({ Rect.x,Rect.y }, { Rect.z,Rect.w }, ESPConfig::VisibleColor, 1.3, ESPConfig::BoxRounding);
				}
				else {
					Gui.Rectangle({ Rect.x,Rect.y }, { Rect.z,Rect.w }, ESPConfig::BoxColor & IM_COL32_A_MASK, 3, ESPConfig::BoxRounding);
					Gui.Rectangle({ Rect.x,Rect.y }, { Rect.z,Rect.w }, ESPConfig::BoxColor, 1.3, ESPConfig::BoxRounding);
				}
				break;
			case 1:
				if (((Entity.Pawn.bSpottedByMask & (DWORD64(1) << LocalPlayerControllerIndex)) || (LocalEntity.Pawn.bSpottedByMask & (DWORD64(1) << Index))) && ESPConfig::VisibleCheck)
				{
					Gui.Rectangle({ Rect.x,Rect.y }, { Rect.z,Rect.w }, ESPConfig::VisibleColor & IM_COL32_A_MASK, 3, ESPConfig::BoxRounding);
					Gui.Rectangle({ Rect.x,Rect.y }, { Rect.z,Rect.w }, ESPConfig::VisibleColor, 1.3, ESPConfig::BoxRounding);
				}
				else {
					Gui.Rectangle({ Rect.x,Rect.y }, { Rect.z,Rect.w }, ESPConfig::BoxColor & IM_COL32_A_MASK, 3, ESPConfig::BoxRounding);
					Gui.Rectangle({ Rect.x,Rect.y }, { Rect.z,Rect.w }, ESPConfig::BoxColor, 1.3, ESPConfig::BoxRounding);
				}
				break;
			case 2:
				if (((Entity.Pawn.bSpottedByMask & (DWORD64(1) << LocalPlayerControllerIndex)) || (LocalEntity.Pawn.bSpottedByMask & (DWORD64(1) << Index))) && ESPConfig::VisibleCheck)
				{
					Gui.RectangleFilled({ Rect.x,Rect.y }, { Rect.z,Rect.w }, FlatBoxVisCol, ESPConfig::BoxRounding);
				}
				else {
					Gui.RectangleFilled({ Rect.x,Rect.y }, { Rect.z,Rect.w }, FlatBoxCol, ESPConfig::BoxRounding);
				}
				break;
			case 3:
				//Outline
				Gui.Line({ Rect.x, Rect.y }, { Rect.x + Rect.z * 0.25f, Rect.y }, ESPConfig::BoxColor & IM_COL32_A_MASK, 3);
				Gui.Line({ Rect.x, Rect.y }, { Rect.x, Rect.y + Rect.w * 0.25f }, ESPConfig::BoxColor & IM_COL32_A_MASK, 3);
				Gui.Line({ Rect.x + Rect.z, Rect.y + Rect.w }, { Rect.x + Rect.z - Rect.z * 0.25f, Rect.y + Rect.w }, ESPConfig::BoxColor & IM_COL32_A_MASK, 3);
				Gui.Line({ Rect.x + Rect.z, Rect.y + Rect.w }, { Rect.x + Rect.z, Rect.y + Rect.w - Rect.w * 0.25f }, ESPConfig::BoxColor & IM_COL32_A_MASK, 3);
				Gui.Line({ Rect.x, Rect.y + Rect.w }, { Rect.x + Rect.z * 0.25f, Rect.y + Rect.w }, ESPConfig::BoxColor & IM_COL32_A_MASK, 3);
				Gui.Line({ Rect.x, Rect.y + Rect.w }, { Rect.x, Rect.y + Rect.w - Rect.w * 0.25f }, ESPConfig::BoxColor & IM_COL32_A_MASK, 3);
				Gui.Line({ Rect.x + Rect.z, Rect.y }, { Rect.x + Rect.z - Rect.z * 0.25f, Rect.y }, ESPConfig::BoxColor & IM_COL32_A_MASK, 3);
				Gui.Line({ Rect.x + Rect.z, Rect.y }, { Rect.x + Rect.z, Rect.y + Rect.w * 0.25f }, ESPConfig::BoxColor & IM_COL32_A_MASK, 3);

				// Main Box Lines
				Gui.Line({ Rect.x, Rect.y }, { Rect.x + Rect.z * 0.25f, Rect.y }, ESPConfig::BoxColor, 1.3f);
				Gui.Line({ Rect.x, Rect.y }, { Rect.x, Rect.y + Rect.w * 0.25f }, ESPConfig::BoxColor, 1.3f);
				Gui.Line({ Rect.x + Rect.z, Rect.y }, { Rect.x + Rect.z - Rect.z * 0.25f, Rect.y }, ESPConfig::BoxColor, 1.3f);
				Gui.Line({ Rect.x + Rect.z, Rect.y }, { Rect.x + Rect.z, Rect.y + Rect.w * 0.25f }, ESPConfig::BoxColor, 1.3f);
				Gui.Line({ Rect.x, Rect.y + Rect.w }, { Rect.x + Rect.z * 0.25f, Rect.y + Rect.w }, ESPConfig::BoxColor, 1.3f);
				Gui.Line({ Rect.x, Rect.y + Rect.w }, { Rect.x, Rect.y + Rect.w - Rect.w * 0.25f }, ESPConfig::BoxColor, 1.3f);
				Gui.Line({ Rect.x + Rect.z, Rect.y + Rect.w }, { Rect.x + Rect.z - Rect.z * 0.25f, Rect.y + Rect.w }, ESPConfig::BoxColor, 1.3f);
				Gui.Line({ Rect.x + Rect.z, Rect.y + Rect.w }, { Rect.x + Rect.z, Rect.y + Rect.w - Rect.w * 0.25f }, ESPConfig::BoxColor, 1.3f);
				break;
			}

		}


		Render::LineToEnemy(Rect, MenuConfig::LineToEnemyColor, 1.2);

		if (ESPConfig::ShowWeaponESP)
			Gui.StrokeText(Entity.Pawn.WeaponName, { Rect.x + Rect.z / 2,Rect.y + Rect.w }, ImColor(255, 255, 255, 255), 14, true);

		if (ESPConfig::ShowPlayerName)
		{
			if (MenuConfig::HealthBarType == 0)
				Gui.StrokeText(Entity.Controller.PlayerName, { Rect.x + Rect.z / 2,Rect.y - 14 }, ImColor(255, 255, 255, 255), 14, true);
			else
				Gui.StrokeText(Entity.Controller.PlayerName, { Rect.x + Rect.z / 2,Rect.y - 13 - 14 }, ImColor(255, 255, 255, 255), 14, true);
		}
	}

	void DrawPreviewBox(const ImVec2& startPos, const ImVec2& endPos, ImColor boxColor, float rounding, float thickness, bool filled) {
		if (filled) {
			ImGui::GetWindowDrawList()->AddRectFilled(startPos, endPos, boxColor, rounding, ImDrawCornerFlags_All);
		}
		else {
			ImGui::GetWindowDrawList()->AddRect(startPos, endPos, boxColor, rounding, ImDrawCornerFlags_All, thickness);
		}
	}

	void PreviewWindow()
	{
		if (!ESPConfig::ShowPreview)
			return;

		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
		ImGui::SetNextWindowSize(ImVec2(200, 250), ImGuiCond_FirstUseEver);
		const auto& window = ImGui::FindWindowByName("AimStar");
		ImGui::SetNextWindowPos(ImVec2(window->Pos.x + window->Size.x + ImGui::GetStyle().WindowPadding.x, window->Pos.y));
		
//		ImGui::SetNextWindowPos(ImVec2(window->Pos.x + window->Size.x - 250, window->Pos.y + 100), ImGuiCond_Always);
		
		ImGui::Begin("ESP Preview", nullptr, windowFlags);
		ImVec2 windowSize = ImGui::GetWindowSize();
		ImVec2 rectSize(100, 150);
		ImVec2 rectPos((windowSize.x - rectSize.x) * 0.45f, (windowSize.y - rectSize.y) * 0.3f);
		ImVec2 centerPos = ImGui::GetCursorScreenPos();
		centerPos.x += rectPos.x;
		centerPos.y += rectPos.y;

		if (ESPConfig::ShowEyeRay) {
			ImU32 EyeC = ESPConfig::EyeRayColor;
			ImVec2 lineStart(centerPos.x + 44, centerPos.y + 15);
			ImVec2 lineEnd(centerPos.x - 10, centerPos.y + 20);
			ImGui::GetWindowDrawList()->AddLine(lineStart, lineEnd, EyeC, 2.0f);
		}
		if (ESPConfig::ShowBoneESP) {
			ImU32 boneColor = ESPConfig::BoneColor;
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
		if (ESPConfig::ShowHeadBox) {
			switch (ESPConfig::HeadBoxStyle)
			{
			case 0:
				ImGui::GetWindowDrawList()->AddCircle({ centerPos.x + 44, centerPos.y + 17 }, 10.0f, ESPConfig::HeadBoxColor, 0, 1.8f);
				break;
			case 1:
				ImGui::GetWindowDrawList()->AddCircleFilled({ centerPos.x + 44, centerPos.y + 17 }, 10.0f, ESPConfig::HeadBoxColor, 0);
			default:
				break;
			}
			
		}
		if (ESPConfig::ShowBoxESP) {
			ImVec2 rectStartPos;
			ImVec2 rectEndPos;
			ImColor boxColor = ESPConfig::BoxColor;

			rectStartPos = centerPos;
			rectEndPos = { rectStartPos.x + rectSize.x, rectStartPos.y + rectSize.y };
			ImColor filledBoxColor = { boxColor.Value.x, boxColor.Value.y, boxColor.Value.z, ESPConfig::BoxAlpha };
			switch (MenuConfig::BoxType)
			{
				case 0:
					DrawPreviewBox(rectStartPos, rectEndPos, boxColor, ESPConfig::BoxRounding, 1.0f, false);
					break;
				case 1:
					DrawPreviewBox(rectStartPos, rectEndPos, boxColor, ESPConfig::BoxRounding, 1.0f, false);
//					rectStartPos = { centerPos.x + 20, centerPos.y + 15 };
//					rectEndPos = { rectStartPos.x + 50, rectStartPos.y + 132 };
//					DrawPreviewBox(rectStartPos, rectEndPos, boxColor, ESPConfig::BoxRounding, 1.0f, false);
					break;
				case 2:
					DrawPreviewBox(rectStartPos, rectEndPos, filledBoxColor, ESPConfig::BoxRounding, 0.0f, true);
					break;
				case 3:
					ImGui::GetWindowDrawList()->AddLine(rectStartPos, { rectStartPos.x + rectSize.x * 0.25f, rectStartPos.y }, boxColor, 1.0f);
					ImGui::GetWindowDrawList()->AddLine(rectStartPos, { rectStartPos.x, rectStartPos.y + rectSize.y * 0.25f }, boxColor, 1.0f);
					ImGui::GetWindowDrawList()->AddLine({ rectStartPos.x + rectSize.x, rectStartPos.y + rectSize.y }, { rectStartPos.x + rectSize.x * 0.75f, rectStartPos.y + rectSize.y }, boxColor, 1.0f);
					ImGui::GetWindowDrawList()->AddLine({ rectStartPos.x + rectSize.x, rectStartPos.y + rectSize.y }, { rectStartPos.x + rectSize.x, rectStartPos.y + rectSize.y * 0.75f }, boxColor, 1.0f);
					ImGui::GetWindowDrawList()->AddLine({ rectStartPos.x, rectStartPos.y + rectSize.y }, { rectStartPos.x + rectSize.x * 0.25f, rectStartPos.y + rectSize.y }, boxColor, 1.0f);
					ImGui::GetWindowDrawList()->AddLine({ rectStartPos.x, rectStartPos.y + rectSize.y }, { rectStartPos.x, rectStartPos.y + rectSize.y * 0.75f }, boxColor, 1.0f);
					ImGui::GetWindowDrawList()->AddLine({ rectStartPos.x + rectSize.x, rectStartPos.y }, { rectStartPos.x + rectSize.x * 0.75f, rectStartPos.y}, boxColor, 1.0f);
					ImGui::GetWindowDrawList()->AddLine({ rectStartPos.x + rectSize.x, rectStartPos.y }, { rectStartPos.x + rectSize.x, rectStartPos.y + rectSize.y * 0.25f }, boxColor, 1.0f);
					break;

			}
		}
		if (ESPConfig::ShowHealthBar) {
			ImU32 greenColor = IM_COL32(0, 255, 0, 255);
			if (MenuConfig::HealthBarType == 0) {
				ImVec2 HBS(centerPos.x - 8, centerPos.y);
				ImVec2 HBE(centerPos.x - 3, centerPos.y + rectSize.y);
				ImGui::GetWindowDrawList()->AddRectFilled(HBS, HBE, ImColor(96, 246, 113, 220), 30.f, ImDrawCornerFlags_All);
			}
			if (MenuConfig::HealthBarType == 1) {
				ImVec2 HBS(centerPos.x, centerPos.y - 6);
				ImVec2 HBE(centerPos.x + rectSize.x, centerPos.y - 3);
				ImGui::GetWindowDrawList()->AddRectFilled(HBS, HBE, ImColor(96, 246, 113, 220), 30.f, ImDrawCornerFlags_All);
			}
			if (MenuConfig::HealthBarType == 2) {
				ImVec2 HBS(centerPos.x, centerPos.y + rectSize.y + 6);
				ImVec2 HBE(centerPos.x + rectSize.x, centerPos.y + rectSize.y + 3);
				ImGui::GetWindowDrawList()->AddRectFilled(HBS, HBE, ImColor(96, 246, 113, 220), 30.f, ImDrawCornerFlags_All);
			}
		}
		if (MenuConfig::ShowLineToEnemy) {
			ImVec2 LineStart, LineEnd;
			LineStart = { centerPos.x + rectSize.x / 2 , centerPos.y };
			switch (MenuConfig::LinePos)
			{
			case 0:
				LineEnd = { LineStart.x, LineStart.y - 50 };
				break;
			case 1:
				LineEnd = { Gui.Window.Size.x, Gui.Window.Size.y };
				break;
			case 2:
				LineEnd = { LineStart.x, LineStart.y - 200 };
				break;
			}
			ImGui::GetWindowDrawList()->AddLine(LineStart, LineEnd, MenuConfig::LineToEnemyColor, 1.8f);
		}
		if (ESPConfig::ShowPlayerName) {
			if (MenuConfig::HealthBarType == 0 || MenuConfig::HealthBarType == 2) {
				ImVec2 textPos(centerPos.x + 30, centerPos.y - 18);
				ImGui::GetWindowDrawList()->AddText(textPos, IM_COL32(255, 255, 255, 255), "Player");
			}
			if (MenuConfig::HealthBarType == 1) {
				ImVec2 textPos(centerPos.x + 30, centerPos.y - 22);
				ImGui::GetWindowDrawList()->AddText(textPos, IM_COL32(255, 255, 255, 255), "Player");
			}
		}
		if (ESPConfig::ShowDistance) {
			ImVec2 textPos(centerPos.x + 105, centerPos.y);
			ImGui::GetWindowDrawList()->AddText(textPos, IM_COL32(255, 204, 0, 255), "20m");
		}
		if (ESPConfig::ShowWeaponESP) {
			if (MenuConfig::HealthBarType == 2) {
				ImVec2 textPos(centerPos.x + 27, centerPos.y + 155);
				ImGui::GetWindowDrawList()->AddText(textPos, IM_COL32(255, 255, 255, 255), "Weapon");
			}
			if (MenuConfig::HealthBarType == 0 || MenuConfig::HealthBarType == 1) {
				ImVec2 textPos(centerPos.x + 27, centerPos.y + 150);
				ImGui::GetWindowDrawList()->AddText(textPos, IM_COL32(255, 255, 255, 255), "Weapon");
			}
		}
		ImGui::End();
	}
}