#include <string>
#include "Cheats.h"
#include "Render.hpp"
#include "MenuConfig.hpp"
#include "Utils/ConfigMenu.hpp"
#include "Utils/ConfigSaver.hpp"
#include "Font/IconsFontAwesome5.h"
#include "Features/StyleChanger.h"

void Cheats::Menu()
{
	ImGui::Begin("AimStar",nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);

	
	{
		ImGui::BeginTabBar("AimStar", ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_FittingPolicyScroll | ImGuiTabBarFlags_NoTooltip);
		// esp menu
		if (ImGui::BeginTabItem(ICON_FA_EYE " ESP"))
		{
			/*
			if (ImGui::IsItemHovered())
			{
				ImGui::SetTooltip("Extra Sensory Perception");
			}*/

			Gui.MyCheckBox("Enabled", &MenuConfig::ESPenbled);
			ImGui::Checkbox("Box", &MenuConfig::ShowBoxESP);
			ImGui::SameLine();
			ImGui::ColorEdit4("##BoxColor", reinterpret_cast<float*>(&MenuConfig::BoxColor), ImGuiColorEditFlags_NoInputs);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(MenuConfig::ComboWidth);
			ImGui::Combo("##BoxStyle", &MenuConfig::BoxType, "Normal\0Edge\0Flat");
			if (MenuConfig::ShowBoxESP)
				ImGui::SliderFloat("Box Rounding", &MenuConfig::BoxRounding, 0.0f, 15.0f, "%.1f", ImGuiSliderFlags_NoInput);

			ImGui::Checkbox("Skeleton", &MenuConfig::ShowBoneESP);
			ImGui::SameLine();
			ImGui::ColorEdit4("##BoneColor", reinterpret_cast<float*>(&MenuConfig::BoneColor), ImGuiColorEditFlags_NoInputs);

			ImGui::Checkbox("Head Box", &MenuConfig::ShowHeadBox);
			ImGui::SameLine();
			ImGui::ColorEdit4("##HeadBoxColor", reinterpret_cast<float*>(&MenuConfig::HeadBoxColor), ImGuiColorEditFlags_NoInputs);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(MenuConfig::ComboWidth);
			ImGui::Combo("##HeadBoxStyle", &MenuConfig::HeadBoxStyle, "Normal\0Flat");

			ImGui::Checkbox("EyeRay", &MenuConfig::ShowEyeRay);
			ImGui::SameLine();
			ImGui::ColorEdit4("##EyeRay", reinterpret_cast<float*>(&MenuConfig::EyeRayColor), ImGuiColorEditFlags_NoInputs);

			ImGui::Checkbox("HealthBar", &MenuConfig::ShowHealthBar);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(MenuConfig::ComboWidth); 
			ImGui::Combo("##BarStyle", &MenuConfig::HealthBarType, "Vetical\0Horizontal");
			
			ImGui::Checkbox("Weapon", &MenuConfig::ShowWeaponESP);
			ImGui::Checkbox("Distance", &MenuConfig::ShowDistance);
			ImGui::Checkbox("Name", &MenuConfig::ShowPlayerName);
		
			ImGui::Checkbox("SnapLine", &MenuConfig::ShowLineToEnemy);
			ImGui::SameLine();
			ImGui::ColorEdit4("##LineToEnemyColor", reinterpret_cast<float*>(&MenuConfig::LineToEnemyColor), ImGuiColorEditFlags_NoInputs);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(MenuConfig::ComboWidth);
			ImGui::Combo("Line Pos", &MenuConfig::LinePos, "Top\0Center\0Bottom");

//			ImGui::NextColumn();
			ImGui::NewLine();
			if (ImGui::CollapsingHeader("SexyESP"))
			{
				ImGui::Checkbox("Penis", &MenuConfig::ShowPenis);
				ImGui::SameLine();
				ImGui::ColorEdit4("##PenisColor", reinterpret_cast<float*>(&MenuConfig::PenisColor), ImGuiColorEditFlags_NoInputs);
				ImGui::SliderFloat("Length", &MenuConfig::PenisLength, 1.0f, 50.0f, "%.1f");
				ImGui::SliderFloat("Size", &MenuConfig::PenisSize, 1.3f, 5.0f, "%.3f");
			}

//			ImGui::Columns(1);
			ImGui::EndTabItem();
		}

		// aimbot menu
		
		if (ImGui::BeginTabItem(ICON_FA_USER " AimBot"))
		{

			Gui.MyCheckBox("Enabled", &MenuConfig::AimBot);
			
			ImGui::SetNextItemWidth(75.f);
			if (ImGui::Combo("Key", &MenuConfig::AimBotHotKey, "LALT\0LBUTTON\0RBUTTON\0XBUTTON1\0XBUTTON2\0CAPITAL\0SHIFT\0CONTROL"))
			{
				AimControl::SetHotKey(MenuConfig::AimBotHotKey);
			}
			ImGui::SameLine();
			ImGui::Checkbox("Toggle Mode", &MenuConfig::AimToggleMode);

			ImGui::Checkbox("Draw Fov", &MenuConfig::DrawFov);
			ImGui::SameLine();
			ImGui::ColorEdit4("##FovCircleColor", reinterpret_cast<float*>(&MenuConfig::FovCircleColor), ImGuiColorEditFlags_NoInputs);
			ImGui::Checkbox("Visible Only", &MenuConfig::VisibleCheck);

			float FovMin = 0.1f, FovMax = 89.f;
			float SmoothMin = 0.1f, SmoothMax = 1.f;
			ImGui::SliderFloat("Fov", &AimControl::AimFov, 0.0f, 25.0f, "%.1f", ImGuiSliderFlags_Logarithmic);
			ImGui::SliderFloat("Speed", &AimControl::Smooth, 0.0f, 1.0f, "%.1f");
			if (ImGui::Combo("Bone", &MenuConfig::AimPosition, "Head\0Neck\0Chest\0Penis"))
			{
				switch (MenuConfig::AimPosition)
				{
				case 0:
					MenuConfig::AimPositionIndex = BONEINDEX::head;
					break;
				case 1:
					MenuConfig::AimPositionIndex = BONEINDEX::neck_0;
					break;
				case 2:
					MenuConfig::AimPositionIndex = BONEINDEX::spine_1;
					break;
				case 3:
					MenuConfig::AimPositionIndex = BONEINDEX::pelvis;
					break;
				default:
					break;
				}
			}
			/*
			ImGui::NewLine();
			if (ImGui::CollapsingHeader("RCS"))
			{
				Gui.MyCheckBox("Enabled", &MenuConfig::RCS);
				ImGui::SliderInt("Start Bullet", &AimControl::RCSBullet, 1, 6, "%d");
				ImGui::SliderFloat("Yaw", &AimControl::RCSScale.x, 0.f, 2.f, "%.1f");
				ImGui::SliderFloat("Pitch", &AimControl::RCSScale.y, 0.f, 2.f, "%.1f");
			}*/
			ImGui::EndTabItem();
		}

		// Radar menu
		if (ImGui::BeginTabItem("Radar"))
		{
			/*
			if (ImGui::IsItemHovered())
			{
				ImGui::SetTooltip("External rendering radar hack.");
			}*/

			Gui.MyCheckBox("Enabled", &MenuConfig::ShowRadar);
			ImGui::SetNextItemWidth(MenuConfig::ComboWidth + 20);
			ImGui::Combo("Style", &MenuConfig::RadarType, "Circle\0Arrow\0Circle & Arrow");
			ImGui::Checkbox("Custom", &MenuConfig::customRadar);
			
			if (MenuConfig::customRadar)
			{
				ImGui::NewLine();
				ImGui::Checkbox("Cross Line", &MenuConfig::ShowRadarCrossLine);
				ImGui::SameLine();
				ImGui::ColorEdit4("##CrossLineColor", reinterpret_cast<float*>(&MenuConfig::RadarCrossLineColor), ImGuiColorEditFlags_NoInputs);
				float RadarPointSizeProportionMin = 0.8f, RadarPointSizeProportionMax = 2.f;
				float ProportionMin = 500.f, ProportionMax = 3300.f;
				float RadarRangeMin = 100.f, RadarRangeMax = 300.f;
				ImGui::SliderFloat("PointSize", &MenuConfig::RadarPointSizeProportion, RadarPointSizeProportionMin, RadarPointSizeProportionMax, "%.1f");
				ImGui::SliderFloat("Proportion", &MenuConfig::Proportion, ProportionMin, ProportionMax, "%.1f");
				ImGui::SliderFloat("Range", &MenuConfig::RadarRange, RadarRangeMin, RadarRangeMax, "%.1f");
				ImGui::SliderFloat("Backgroud Alpha", &MenuConfig::RadarBgAlpha, 0.0f, 1.0f, "%.2f");
			}
			


//			ImGui::Checkbox("Fov Line", &MenuConfig::ShowFovLine);
//			ImGui::SameLine();
//			ImGui::ColorEdit4("##FovLineColor", reinterpret_cast<float*>(&MenuConfig::FovLineColor), ImGuiColorEditFlags_NoInputs);
//			float FovLineSizeMin = 20.f, FovLineSizeMax = 120.f;
//			Gui.SliderScalarEx1("Length", ImGuiDataType_Float, &MenuConfig::FovLineSize, &FovLineSizeMin, &FovLineSizeMax, "%.1f", ImGuiSliderFlags_None);

			ImGui::EndTabItem();
		}

		// TriggerBot
		if (ImGui::BeginTabItem(ICON_FA_HAND_POINTER " TriggerBot"))
		{
			/*
			if (ImGui::IsItemHovered())
			{
				ImGui::SetTooltip("Automatically fires a weapon as soon as an enemy comes into the crosshair.");
			}*/

			Gui.MyCheckBox("Enabled", &MenuConfig::TriggerBot);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(MenuConfig::ComboWidth);

			if (ImGui::Combo("Hotkey", &MenuConfig::TriggerHotKey, "LALT\0RBUTTON\0XBUTTON1\0XBUTTON2\0CAPITAL\0SHIFT\0CONTROL"))
			{
				TriggerBot::SetHotKey(MenuConfig::TriggerHotKey);
			}

			ImGui::Checkbox("Always Activate", &MenuConfig::TriggerAlways);
			DWORD TriggerDelayMin = 10, TriggerDelayMax = 300;
			ImGui::SliderInt("Delay", &TriggerBot::TriggerDelay, TriggerDelayMin, TriggerDelayMax, "%d ms", ImGuiSliderFlags_None);

			ImGui::EndTabItem();
		}

		//Crosshair
		if (ImGui::BeginTabItem("+ Crosshair"))
		{
			/*
			if (ImGui::IsItemHovered())
			{
				ImGui::SetTooltip("Highly customizable external crosshair.");
			}*/

			Gui.MyCheckBox("Enabled", &CrosshairConfig::ShowCrossHair);

			ImGui::SetNextItemWidth(MenuConfig::ComboWidth + 50);
			if (ImGui::Combo("Presets", &CrosshairConfig::crosshairPreset, "Custom\0Dot\0Circle Dot 1\0Circle Dot 2\0Crosshair Small\0Crosshair Medium\0Crosshair Dot"))
				Render::UpdateCrosshairPreset(CrosshairConfig::crosshairPreset);

			ImGui::Text("Crosshair Color");
			ImGui::SameLine();
			ImGui::ColorEdit4("##CrossHairColor", reinterpret_cast<float*>(&CrosshairConfig::CrossHairColor), ImGuiColorEditFlags_NoInputs);

			ImGui::Checkbox("Center Dot", &CrosshairConfig::drawDot);
			if (CrosshairConfig::drawDot)
			{
				ImGui::SliderFloat("Dot Size", &CrosshairConfig::DotSize, 1.f, 50.f, "%.f");
			}

			ImGui::Checkbox("Outline", &CrosshairConfig::drawOutLine);
			ImGui::Checkbox("Crossline", &CrosshairConfig::drawCrossline);
			if (CrosshairConfig::drawCrossline)
			{
				ImGui::SliderInt("Horizontal Length", &CrosshairConfig::HorizontalLength, 1, 100, "%d");
				ImGui::SliderInt("Vertical Length", &CrosshairConfig::VerticalLength, 1, 100, "%d");
				ImGui::SliderInt("Gap", &CrosshairConfig::Gap, 1, 50, "%d");
//				ImGui::Checkbox("Dynamic Gap", &CrosshairConfig::DynamicGap);
				ImGui::Checkbox("T Style", &CrosshairConfig::tStyle);
			}

			ImGui::Separator();
			ImGui::Checkbox("Circle", &CrosshairConfig::drawCircle);
			if(CrosshairConfig::drawCircle)
				ImGui::SliderFloat("Circle Radius", &CrosshairConfig::CircleRadius, 0.0f, 50.0f, "%.1f");

			ImGui::Separator();
			ImGui::Checkbox("Target Crosshair", &CrosshairConfig::showTargeting);
			ImGui::SameLine();
			ImGui::ColorEdit4("##CrosshairColor", reinterpret_cast<float*>(&CrosshairConfig::TargetedColor), ImGuiColorEditFlags_NoInputs);

			ImGui::EndTabItem();
		}

		// Misc
		if (ImGui::BeginTabItem(ICON_FA_SUN " Misc"))
		{
			/*
			if (ImGui::IsItemHovered())
			{
				ImGui::SetTooltip("Other features.");
			}*/

			ImGui::Columns(2, nullptr, false);
			ImGui::SetColumnOffset(1, 250.0f);

			if (ImGui::Combo("Style", &MenuConfig::MenuStyle, "Default\0Light\0Classic\0Red"))
				StyleChanger::UpdateStyle(MenuConfig::MenuStyle);

			ImGui::Checkbox("Headshot Line", &MenuConfig::ShowHeadShootLine);
			ImGui::SameLine();
			ImGui::ColorEdit4("##HeadShootLineColor", reinterpret_cast<float*>(&MenuConfig::HeadShootLineColor), ImGuiColorEditFlags_NoInputs);
			ImGui::Checkbox("Cheat In Spec", &MenuConfig::WorkInSpec);
			ImGui::Checkbox("No Flash", &MenuConfig::NoFlash);
			ImGui::Checkbox("Watermark", &MenuConfig::WaterMark);
			ImGui::Checkbox("Cheat List", &MenuConfig::CheatList);

			ImGui::NextColumn();
			ImGui::Checkbox("Bunny Hop", &MenuConfig::BunnyHop);
			ImGui::Checkbox("Team Check", &MenuConfig::TeamCheck);
			ImGui::Checkbox("Bypass OBS", &MenuConfig::BypassOBS);

			ImGui::Columns(1);
			ImGui::EndTabItem();
		}

		// Config
		ConfigMenu::RenderConfigMenu();

		// About
		if (ImGui::BeginTabItem(ICON_FA_FILE_CODE " README"))
		{
			/*
			if (ImGui::IsItemHovered())
			{
				ImGui::SetTooltip("About.");
			}*/

			// Since it's already the MIT license, there's no need to do that.
			// ImGui::TextColored(ImColor(255, 0, 0, 255), "Reselling prohibited");

			Gui.OpenWebpageButton("Source Code", "https://github.com/CowNowK/AimStarCS2");
			ImGui::SameLine();
			Gui.OpenWebpageButton("Join Discord", "https://discord.gg/MzbmSRaU3p");
			ImGui::TextColored(ImColor(0, 200, 255, 255), "Last update: 2023-10-22");
			ImGui::NewLine();

			ImGui::Text("Offsets:");
			ImGui::Text("EntityList:");
			ImGui::SameLine();
			ImGui::Text(std::to_string(Offset::EntityList).c_str());
			ImGui::Text("Matrix:");
			ImGui::SameLine();
			ImGui::Text(std::to_string(Offset::Matrix).c_str());
			ImGui::Text("LocalPlayerController:");
			ImGui::SameLine();
			ImGui::Text(std::to_string(Offset::LocalPlayerController).c_str());
			ImGui::Text("ViewAngle:");
			ImGui::SameLine();
			ImGui::Text(std::to_string(Offset::ViewAngle).c_str());
			ImGui::Text("LocalPlayerPawn:");
			ImGui::SameLine();
			ImGui::Text(std::to_string(Offset::LocalPlayerPawn).c_str());
			ImGui::Text("ForceJump:");
			ImGui::SameLine();
			ImGui::Text(std::to_string(Offset::ForceJump).c_str());

			ImGui::EndTabItem();
		}

	}ImGui::End();
}

void Cheats::RadarSetting(Base_Radar& Radar)
{
	// Radar window
	ImGui::SetNextWindowBgAlpha(MenuConfig::RadarBgAlpha);
	ImGui::Begin("Radar", 0, ImGuiWindowFlags_NoResize);
	ImGui::SetWindowSize({ MenuConfig::RadarRange * 2,MenuConfig::RadarRange * 2 });
	
	if (!MenuConfig::customRadar)
	{
		ImGui::SetWindowPos(ImVec2(0, 0));
		MenuConfig::ShowRadarCrossLine = false;
		MenuConfig::Proportion = 3300.f;
		MenuConfig::RadarPointSizeProportion = 1.f;
		MenuConfig::RadarRange = 150.f;
		MenuConfig::RadarBgAlpha = 0.1f;
	}
		

	// Radar.SetPos({ Gui.Window.Size.x / 2,Gui.Window.Size.y / 2 });
	Radar.SetDrawList(ImGui::GetWindowDrawList());
	Radar.SetPos({ ImGui::GetWindowPos().x + MenuConfig::RadarRange, ImGui::GetWindowPos().y + MenuConfig::RadarRange });
	Radar.SetProportion(MenuConfig::Proportion);
	Radar.SetRange(MenuConfig::RadarRange);
	Radar.SetSize(MenuConfig::RadarRange * 2);
	Radar.SetCrossColor(MenuConfig::RadarCrossLineColor);

	Radar.ArcArrowSize *= MenuConfig::RadarPointSizeProportion;
	Radar.ArrowSize *= MenuConfig::RadarPointSizeProportion;
	Radar.CircleSize *= MenuConfig::RadarPointSizeProportion;

	Radar.ShowCrossLine = MenuConfig::ShowRadarCrossLine;
	Radar.Opened = true;
}

void Cheats::RenderCrossHair(ImDrawList* drawList) noexcept
{
	if (!CrosshairConfig::ShowCrossHair)
		return;

	if(CrosshairConfig::isAim && CrosshairConfig::showTargeting)
		Render::DrawCrossHair(drawList, ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), ImGui::ColorConvertFloat4ToU32(CrosshairConfig::TargetedColor));
	else
		Render::DrawCrossHair(drawList, ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), ImGui::ColorConvertFloat4ToU32(CrosshairConfig::CrossHairColor));
}

void Cheats::Run()
{	
	// Show menu
	static DWORD lastTick = 0; 
	DWORD currentTick = GetTickCount(); 
	if ((GetAsyncKeyState(VK_INSERT) & 0x8000) && currentTick - lastTick >= 150){
		// Check key state per 150ms once to avoid loop
		MenuConfig::ShowMenu = !MenuConfig::ShowMenu;
		lastTick = currentTick; 
	}
	if(MenuConfig::ShowMenu)
		Menu();

	// Update matrix
	if(!ProcessMgr.ReadMemory(gGame.GetMatrixAddress(), gGame.View.Matrix,64))
		return;

	// Update EntityList Entry
	gGame.UpdateEntityListEntry();

	DWORD64 LocalControllerAddress = 0;
	DWORD64 LocalPawnAddress = 0;

	if (!ProcessMgr.ReadMemory(gGame.GetLocalControllerAddress(), LocalControllerAddress))
		return;
	if (!ProcessMgr.ReadMemory(gGame.GetLocalPawnAddress(), LocalPawnAddress))
		return;

	// LocalEntity
	CEntity LocalEntity;
	static int LocalPlayerControllerIndex = 1;
	if (!LocalEntity.UpdateController(LocalControllerAddress))
		return;
	if (!LocalEntity.UpdatePawn(LocalPawnAddress) && !MenuConfig::WorkInSpec)
		return;

	// HealthBar Map
	static std::map<DWORD64, Render::HealthBar> HealthBarMap;

	// AimBot data
	float DistanceToSight = 0;
	float MaxAimDistance = 100000;
	Vec3  HeadPos{ 0,0,0 };
	Vec3  AimPos{ 0,0,0 };

	// Radar Data
	Base_Radar Radar;
	if (MenuConfig::ShowRadar)
		RadarSetting(Radar);

	for (int i = 0; i < 64; i++)
	{
		CEntity Entity;
		DWORD64 EntityAddress = 0;
		if (!ProcessMgr.ReadMemory<DWORD64>(gGame.GetEntityListEntry() + (i + 1) * 0x78, EntityAddress))
			continue;
		if (EntityAddress == LocalEntity.Controller.Address)
		{
			LocalPlayerControllerIndex = i;
			continue;
		}
		if (!Entity.UpdateController(EntityAddress))
			continue;
		if (!Entity.UpdatePawn(Entity.Pawn.Address))
			continue;

		if (MenuConfig::TeamCheck && Entity.Controller.TeamID == LocalEntity.Controller.TeamID)
			continue;
		if (!Entity.IsAlive())
			continue;
//		if (MenuConfig::VisibleCheck && (!Entity.Pawn.bSpottedByMask > 0))
//			continue;


		// Add entity to radar
		if (MenuConfig::ShowRadar)
			Radar.AddPoint(LocalEntity.Pawn.Pos, LocalEntity.Pawn.ViewAngle.y, Entity.Pawn.Pos, ImColor(237, 85, 106, 200), MenuConfig::RadarType, Entity.Pawn.ViewAngle.y);

		if (!Entity.IsInScreen())
			continue;

		// Bone Debug
	/*	for (int BoneIndex = 0; BoneIndex < Entity.BoneData.BonePosList.size(); BoneIndex++)
		{
			Vec2 ScreenPos{};
			if (gGame.View.WorldToScreen(Entity.BoneData.BonePosList[BoneIndex].Pos, ScreenPos))
			{
				Gui.Text(std::to_string(BoneIndex), ScreenPos, ImColor(255, 255, 255, 255));
			}
		}*/

		DistanceToSight = Entity.GetBone().BonePosList[BONEINDEX::head].ScreenPos.DistanceTo({ Gui.Window.Size.x / 2,Gui.Window.Size.y / 2 });


		if (DistanceToSight < MaxAimDistance)
		{
			MaxAimDistance = DistanceToSight;

			if (!MenuConfig::VisibleCheck ||
				Entity.Pawn.bSpottedByMask & (DWORD64(1) << (LocalPlayerControllerIndex)) ||
				LocalEntity.Pawn.bSpottedByMask & (DWORD64(1) << (i)))
			{
				AimPos = Entity.GetBone().BonePosList[MenuConfig::AimPositionIndex].Pos;
				if (MenuConfig::AimPositionIndex == BONEINDEX::head)
					AimPos.z -= 1.f;
			}
		}
		

		if (MenuConfig::ESPenbled)
		{

			// Draw Bone
			Render::DrawBone(Entity, MenuConfig::BoneColor, 1.3f);

			// Draw Penis
			Render::ShowPenis(Entity, MenuConfig::PenisLength, MenuConfig::PenisColor, MenuConfig::PenisSize);

			// Draw eyeRay
			Render::ShowLosLine(Entity, 50.0f, MenuConfig::EyeRayColor, 1.3f);

			// Draw Head Box
			Render::DrawHeadCircle(Entity, MenuConfig::HeadBoxColor);

			// Box
			ImVec4 Rect;
			switch (MenuConfig::BoxType)
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

			// Snap Line
			if (MenuConfig::ShowLineToEnemy)
			{
				Render::LineToEnemy(Rect, MenuConfig::LineToEnemyColor, 1.2);
			}
				
			// Draw Box
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
				
			

			// Draw HealthBar
			if (MenuConfig::ShowHealthBar)
			{
				ImVec2 HealthBarPos, HealthBarSize;
				if (MenuConfig::HealthBarType == 0)
				{
					// Vertical
					HealthBarPos = { Rect.x - 10.f,Rect.y };
					HealthBarSize = { 7 ,Rect.w };
				}
				else
				{
					// Horizontal
					HealthBarPos = { Rect.x + Rect.z / 2 - 70 / 2,Rect.y - 13 };
					HealthBarSize = { 70,8 };
				}
				Render::DrawHealthBar(EntityAddress, 100, Entity.Pawn.Health, HealthBarPos, HealthBarSize, MenuConfig::HealthBarType);
			}

			// Draw weaponName
			if (MenuConfig::ShowWeaponESP)
				Gui.StrokeText(Entity.Pawn.WeaponName, { Rect.x + Rect.z / 2,Rect.y + Rect.w }, ImColor(255, 255, 255, 255), 14, true);

			// Draw Distance
			Render::DrawDistance(LocalEntity, Entity, Rect);

			// Draw player name
			if (MenuConfig::ShowPlayerName)
			{
				if (MenuConfig::HealthBarType == 0)
					Gui.StrokeText(Entity.Controller.PlayerName, { Rect.x + Rect.z / 2,Rect.y - 14 }, ImColor(255, 255, 255, 255), 14, true);
				else
					Gui.StrokeText(Entity.Controller.PlayerName, { Rect.x + Rect.z / 2,Rect.y - 13 - 14 }, ImColor(255, 255, 255, 255), 14, true);
			}
		}
	}
	// Radar render
	if(MenuConfig::ShowRadar)
	{
		Radar.Render();
		ImGui::End();
	}

	// TriggerBot
	if (MenuConfig::TriggerBot && (GetAsyncKeyState(TriggerBot::HotKey) || MenuConfig::TriggerAlways))
		TriggerBot::Run(LocalEntity);	

	// WaterMark
	Watermark::Render();

	// Cheat List
	CheatList::Render();

	// Fov line
	Render::DrawFov(LocalEntity, MenuConfig::FovLineSize, MenuConfig::FovLineColor, 1);

	// HeadShoot Line
	Render::HeadShootLine(LocalEntity, MenuConfig::HeadShootLineColor);
	
	// CrossHair
	TriggerBot::TargetCheck(LocalEntity);
	Bunnyhop::AirCheck(LocalEntity);
	RenderCrossHair(ImGui::GetBackgroundDrawList());

	// Bhop
	Bunnyhop::Run(LocalEntity);

	// No Flash
	NoFlash::Run(LocalEntity);

	// Aimbot
	if (MenuConfig::AimBot)
	{
		Render::DrawFovCircle(LocalEntity);

		if (MenuConfig::AimAlways)
		{
			if (AimPos != Vec3(0, 0, 0))
			{
				AimControl::AimBot(LocalEntity, LocalEntity.Pawn.CameraPos, AimPos);
			}
		}
		else
		{
			if (GetAsyncKeyState(AimControl::HotKey))
			{
				if (AimPos != Vec3(0, 0, 0))
				{
					AimControl::AimBot(LocalEntity, LocalEntity.Pawn.CameraPos, AimPos);
				}
			}
		}

		if (MenuConfig::AimToggleMode && (GetAsyncKeyState(AimControl::HotKey) & 0x8000) && currentTick - lastTick >= 200)
		{
			AimControl::switchToggle();
			lastTick = currentTick;
		}
			
			
	}
		
}
