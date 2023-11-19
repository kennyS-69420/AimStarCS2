#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Game.h"
#include "Entity.h"
#include "MenuConfig.hpp"
#include <iostream>
#include "View.hpp"
#include "Features/RCS.h"

extern "C" {
#include "Features\Mouse.h"
#include "Entity.h"
}


namespace AimControl
{
    inline int HotKey = VK_LMENU;
    inline float AimFov = 5;
    inline float Smooth = 2.0f;
    inline Vec2 RCSScale = { 1.f,1.f };
    inline std::vector<int> HotKeyList{ VK_LMENU, VK_LBUTTON, VK_RBUTTON, VK_XBUTTON1, VK_XBUTTON2, VK_CAPITAL, VK_LSHIFT, VK_LCONTROL };

    inline void SetHotKey(int Index)
    {
        HotKey = HotKeyList.at(Index);
    }

    inline void switchToggle()
    {
        MenuConfig::AimAlways = !MenuConfig::AimAlways;
    }

    inline void AimBot(const CEntity& Local, Vec3 LocalPos, Vec3 AimPos)
    {
        if (MenuConfig::ShowMenu)
            return;

        float Yaw, Pitch;
        float Distance, Norm;
        Vec3 OppPos;
        int ScreenCenterX = Gui.Window.Size.x / 2;
        int ScreenCenterY = Gui.Window.Size.y / 2;
        float TargetX = 0.f;
        float TargetY = 0.f;

        OppPos = AimPos - LocalPos;

        Distance = sqrt(pow(OppPos.x, 2) + pow(OppPos.y, 2));

        Yaw = atan2f(OppPos.y, OppPos.x) * 57.295779513 - Local.Pawn.ViewAngle.y;
        Pitch = -atan(OppPos.z / Distance) * 57.295779513 - Local.Pawn.ViewAngle.x;
        Norm = sqrt(pow(Yaw, 2) + pow(Pitch, 2));

        Vec2 ScreenPos;
        gGame.View.WorldToScreen(Vec3(AimPos), ScreenPos);

        if (Norm < AimFov)
        {
            if (ScreenPos.x > ScreenCenterX)
            {
                TargetX = -(ScreenCenterX - ScreenPos.x);
                if (Smooth != 0.0f) {
                    TargetX /= Smooth;
                }
                if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
            }
            if (ScreenPos.x < ScreenCenterX)
            {
                TargetX = ScreenPos.x - ScreenCenterX;
                if (Smooth != 0.0f) {
                    TargetX /= Smooth;
                }
                if (TargetX + ScreenCenterX < 0) TargetX = 0;
            }

            if (ScreenPos.y != 0)
            {
                if (ScreenPos.y > ScreenCenterY)
                {
                    TargetY = -(ScreenCenterY - ScreenPos.y);
                    if (Smooth != 0.0f) {
                        TargetY /= Smooth;
                    }
                    if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
                }

                if (ScreenPos.y < ScreenCenterY)
                {
                    TargetY = ScreenPos.y - ScreenCenterY;
                    if (Smooth != 0.0f) {
                        TargetY /= Smooth;
                    }
                    if (TargetY + ScreenCenterY < 0) TargetY = 0;
                }
            }

            if (!Smooth)
            {
                mouse_event(MOUSEEVENTF_MOVE, (DWORD)(TargetX), (DWORD)(TargetY), NULL, NULL);
                return;
            }

            // Dynamic AimSmooth based on distance
            float DistanceRatio = Norm / AimFov; // Calculate the distance ratio
            float SpeedFactor = 1.0f + (1.0f - DistanceRatio); // Determine the speed factor based on the distance ratio
            TargetX /= (Smooth * SpeedFactor);
            TargetY /= (Smooth * SpeedFactor);
            // by Skarbor
            
            if (fabs(TargetX) < 1)
            {
                if (TargetX > 0)
                {
                    TargetX = 1;
                }
                if (TargetX < 0)
                {
                    TargetX = -1;
                }
            }
            if (fabs(TargetY) < 1)
            {
                if (TargetY > 0)
                {
                    TargetY = 1;
                }
                if (TargetY < 0)
                {
                    TargetY = -1;
                }
            }
            mouse_event(MOUSEEVENTF_MOVE, TargetX, TargetY, NULL, NULL);
        }
    }
}