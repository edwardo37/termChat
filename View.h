// View.h
//
// Created by Cameron Schultz - 2/28/26

#pragma once

#include <deque>
#include <vector>
#include <string>
#include <memory>

namespace termChat
{
    // Forward declaration for circular-dependency
    class Controller;

    struct KeyEvent;

    class View
    {
        // Pointer because circular dependency
        Controller* controller;

    public:
        View();
        ~View();
        
        void setController(Controller* c);

        int listenForInput();

        KeyEvent toKeyEvent(int c);
    };


    struct ViewImpl;


    class MessageHistoryView
    {
        std::unique_ptr<ViewImpl> p_viewImpl;
    public:
        MessageHistoryView();
        ~MessageHistoryView();

        void renderMessageHistory(
            const std::deque<std::string>& mh, 
            const size_t start,
            const size_t selected_message_offset
        );

        const size_t getLineCount() const;

        const int getMessageHeight(const std::string m) const;
    };


    class InputFieldView
    {
        std::unique_ptr<ViewImpl> p_viewImpl;
    public:
        InputFieldView();
        ~InputFieldView();

        void render(const char* message);
    };
}