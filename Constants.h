// Constants.h
//
// Defines constants shared accross the app, like keycodes.
//
// Created by Cameron Schultz - 3/3/26

#pragma once

#include <cstdint>

namespace termChat
{
    typedef enum
    {
        TC_KEY_NULL,
        
        TC_KEY_UP,
        TC_KEY_DOWN,
        TC_KEY_LEFT,
        TC_KEY_RIGHT,

        TC_KEY_ENTER,
        TC_KEY_INT,

        TC_KEY_CHAR
    } KeyCode;

    struct KeyEvent
    {
        KeyCode code;
        char c; // Only usable if (code == TC_KEY_CHAR)
    };

    typedef enum : uint32_t
    {
        TC_COM_SAY,
        TC_COM_ALIAS,
        TC_COM_EXIT,
        TC_COM_CONNECT,
        TC_COM_DISCONNECT,
        TC_COM_STOP
    } Command;
}