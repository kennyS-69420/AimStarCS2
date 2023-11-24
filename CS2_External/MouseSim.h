#pragma once

#ifndef MOUSESIM_H
#define MOUSESIM_H

#include <Windows.h>

// Mouse Function Prototypes
namespace MouseSim
{
    inline void MoveMouse(int targetX, int targetY) {
        INPUT input = { 0 };
        input.type = INPUT_MOUSE;
        input.mi.dx = targetX;
        input.mi.dy = targetY;
        input.mi.dwFlags = MOUSEEVENTF_MOVE;
        SendInput(1, &input, sizeof(INPUT));

    }

    inline void SimulateLeftButtonUp() {
        INPUT input = { 0 };

        // Set up the input event for the left mouse button up
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTUP;

        // Send the input event
        SendInput(1, &input, sizeof(INPUT));
    }

    inline void SimulateLeftButtonDown() {
        INPUT input = { 0 };

        // Set up the input event for the left mouse button down
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

        // Send the input event
        SendInput(1, &input, sizeof(INPUT));
    }
}



#endif // MOUSESIM_H
