// App.h
//
// Application lifetime class, attempt to use PIMPL
//
// Created by Cameron Schultz - 3/3/26

#pragma once

#include "Model.h"
#include "View.h"
#include "Controller.h"

namespace termChat
{
    class App
    {
        App();
        ~App();

        MessageHistory model;
        View view;
        Controller controller;

        bool running;

    public:
        App(const App&) = delete;
        App& operator=(const App&) = delete;

        App(const App&&) = delete;
        App& operator=(const App&&) = delete;

        static App& getInstance();

        int run();
    };
}