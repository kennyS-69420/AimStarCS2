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

	void RenderPlayerESP(const CEntity &Entity, ImVec4 Rect)
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
}