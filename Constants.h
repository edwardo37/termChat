// Constants.h
//
// Defines constants shared accross the app, like keycodes.
//
// Created by Cameron Schultz - 3/3/26

#pragma once

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
}