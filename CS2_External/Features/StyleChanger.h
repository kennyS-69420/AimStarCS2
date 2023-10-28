#pragma once
#include "..\Utils\Style.h"

namespace StyleChanger
{
	inline void UpdateStyle(int Style) noexcept
	{
		switch (Style) {
		case 0:
			Styles::Style_EnemyMouse();
			break;
		case 1:
			Styles::Style_Hacker();
			break;
		case 2:
			ImGui::StyleColorsLight();
			break;
		case 3:
			ImGui::StyleColorsClassic();
			break;
		case 4:
			Styles::Style_Classic();
			break;
		default:
			break;
		}
	}

	inline void InitStyle() noexcept
	{
		Styles::Style_EnemyMouse();
	}
}