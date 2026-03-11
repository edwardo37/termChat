// Controller.h
//
// Links input, output, and the model together.
//
// Created by Cameron Schultz - 2/28/26

#pragma once

#include "Model.h"
#include "View.h"

#include <string>
#include <cstddef>

namespace termChat
{
    struct KeyEvent;

    struct MessageHistoryViewport
    {
        // first message
        size_t start;
        // Relative to start
        size_t selected;

        bool followLatest;
    };

    
    class Controller
    {
        View& main_view;

        MessageHistory& MH_model;
        MessageHistoryView MH_view{};

        MessageHistoryViewport MH_viewport;

        InputFieldView IF_view{};

        // Error handling pls
        int renderCurrentMessageHistory();

        // Error handling?
        bool tryMoveSelectedDown(); bool tryMoveSelectedUp();

    public:
        Controller(MessageHistory& m, View& v);
        ~Controller();

        // Error handling pls
        int addMessageToHistory(const char* m);

        // Error handling pls
        int handleKeyEvent(const KeyEvent ke);
    };
}