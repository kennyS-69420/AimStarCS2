#pragma once
#include <string>
#include <map>

// https://www.unknowncheats.me/forum/counter-strike-2-a/608799-weapon-icon-esp.html
const char* GunIcon(const std::string weapon)
{
	std::map<std::string, const char*> gunIcons = {
		{"nova", "T"},
		{"ak47", "A"},
		{"awp", "C"},
		{"m4a4", "M"},
		{"deagle", "F"},
		{"mp9", "R"},
		{"famas", "H"},
		{"ump45", "b"},
		{"glock", "g"},
		// §¥§à§Ò§Ñ§Ó§î§ä§Ö §à§ã§ä§Ñ§Ý§î§ß§í§Ö §à§â§å§Ø§Ú§ñ §Ú §Ú§ç §ã§à§à§ä§Ó§Ö§ä§ã§ä§Ó§å§ð§ë§Ú§Ö §ã§ä§â§à§Ü§Ú §Ù§Õ§Ö§ã§î
	};

	// §¥§à§Ò§Ñ§Ó§Ý§ñ§Ö§Þ §à§â§å§Ø§Ú§ñ §Ú §Ú§ç §Ù§ß§Ñ§é§Ü§Ú §Ó §ã§à§à§ä§Ó§Ö§ä§ã§ä§Ó§Ú§Ú §ã §Ó§Ñ§ê§Ú§Þ §ã§á§Ú§ã§Ü§à§Þ
	gunIcons[xorstr_("knife_ct")] = "]";
	gunIcons[xorstr_("knife_t")] = "[";
	gunIcons[xorstr_("deagle")] = "A";
	gunIcons[xorstr_("elite")] = "B";
	gunIcons[xorstr_("fiveseven")] = "C";
	gunIcons[xorstr_("glock")] = "D";//
	gunIcons[xorstr_("revolver")] = "J";//
	gunIcons[xorstr_("hkp2000")] = "E";//
	gunIcons[xorstr_("p250")] = "F";//
	gunIcons[xorstr_("usp_silencer")] = "G";//
	gunIcons[xorstr_("tec9")] = "H";//
	gunIcons[xorstr_("cz75a")] = "I";//
	gunIcons[xorstr_("mac10")] = "K";//
	gunIcons[xorstr_("ump45")] = "L";
	gunIcons[xorstr_("bizon")] = "M";//
	gunIcons[xorstr_("mp7")] = "N";//
	gunIcons[xorstr_("mp9")] = "R";
	gunIcons[xorstr_("p90")] = "O";
	gunIcons[xorstr_("galilar")] = "Q";
	gunIcons[xorstr_("famas")] = "R";
	gunIcons[xorstr_("m4a1_silencer")] = "T";//
	gunIcons[xorstr_("m4a1")] = "S";//
	gunIcons[xorstr_("aug")] = "U";
	gunIcons[xorstr_("sg556")] = "V";
	gunIcons[xorstr_("ak47")] = "W";
	gunIcons[xorstr_("g3sg1")] = "X";
	gunIcons[xorstr_("scar20")] = "Y";//
	gunIcons[xorstr_("awp")] = "Z";
	gunIcons[xorstr_("ssg08")] = "a";//
	gunIcons[xorstr_("xm1014")] = "b";
	gunIcons[xorstr_("sawedoff")] = "c";
	gunIcons[xorstr_("mag7")] = "d";
	gunIcons[xorstr_("nova")] = "e";
	gunIcons[xorstr_("negev")] = "f";
	gunIcons[xorstr_("m249")] = "g";
	gunIcons[xorstr_("taser")] = "h";
	gunIcons[xorstr_("flashbang")] = "i";
	gunIcons[xorstr_("hegrenade")] = "j";
	gunIcons[xorstr_("smokegrenade")] = "k";
	gunIcons[xorstr_("molotov")] = "l";//
	gunIcons[xorstr_("decoy")] = "m";
	gunIcons[xorstr_("incgrenade")] = "n";
	gunIcons[xorstr_("c4")] = "o";

	auto it = gunIcons.find(weapon);
	if (it != gunIcons.end()) {
		return it->second;
	}

	return "";
}