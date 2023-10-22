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
			ImGui::StyleColorsLight();
			break;
		case 2:
			ImGui::StyleColorsClassic();
			break;
		case 3:
			Styles::Style_Classic();
			break;
		default:
			break;
		}
	}
}