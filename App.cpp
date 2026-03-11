// App.cpp

#include "App.h"

#include "Controller.h"

namespace termChat
{

    App::App()
        :   running(false),
            controller(model, view)
    {
        view.setController(&controller);
    }

    App::~App() = default;

    App& App::getInstance()
    {
        static App a;
        return a;
    }

    int App::run()
    {
        if (running) return 1;
        running = true;

        controller.addMessageToHistory("Lorem ipsum dolor sit amet consectetur adipiscing elit. Quisque faucibus ex sapien vitae pellentesque sem placerat.");
        controller.addMessageToHistory("In id cursus mi pretium tellus duis convallis. Tempus leo eu aenean sed diam urna tempor. Pulvinar vivamus fringilla lacus nec metus bibendum egestas.");
        controller.addMessageToHistory("Iaculis massa nisl malesuada lacinia integer nunc posuere. Ut hendrerit semper vel class aptent taciti sociosqu.");
        controller.addMessageToHistory("Ad litora torquent per conubia nostra inceptos himenaeos.");

        controller.addMessageToHistory("Lorem ipsum dolor sit amet consectetur adipiscing elit. Quisque faucibus ex sapien vitae pellentesque sem placerat. In id cursus mi pretium tellus duis convallis. Tempus leo eu aenean sed diam urna tempor. Pulvinar vivamus fringilla lacus nec metus bibendum egestas. Iaculis massa nisl malesuada lacinia integer nunc posuere. Ut hendrerit semper vel class aptent taciti sociosqu. Ad litora torquent per conubia nostra inceptos himenaeos.");

        controller.addMessageToHistory("Lorem ipsum dolor sit amet consectetur adipiscing elit. Quisque faucibus ex sapien vitae pellentesque sem placerat.");
        controller.addMessageToHistory("In id cursus mi pretium tellus duis convallis. Tempus leo eu aenean sed diam urna tempor. Pulvinar vivamus fringilla lacus nec metus bibendum egestas.");
        controller.addMessageToHistory("Iaculis massa nisl malesuada lacinia integer nunc posuere. Ut hendrerit semper vel class aptent taciti sociosqu.");
        controller.addMessageToHistory("Ad litora torquent per conubia nostra inceptos himenaeos.");

        controller.addMessageToHistory("Lorem ipsum dolor sit amet consectetur adipiscing elit. Quisque faucibus ex sapien vitae pellentesque sem placerat. In id cursus mi pretium tellus duis convallis. Tempus leo eu aenean sed diam urna tempor. Pulvinar vivamus fringilla lacus nec metus bibendum egestas. Iaculis massa nisl malesuada lacinia integer nunc posuere. Ut hendrerit semper vel class aptent taciti sociosqu. Ad litora torquent per conubia nostra inceptos himenaeos.");


        controller.addMessageToHistory("Lorem ipsum dolor sit amet consectetur adipiscing elit. Quisque faucibus ex sapien vitae pellentesque sem placerat.");
        controller.addMessageToHistory("In id cursus mi pretium tellus duis convallis. Tempus leo eu aenean sed diam urna tempor. Pulvinar vivamus fringilla lacus nec metus bibendum egestas.");
        controller.addMessageToHistory("Iaculis massa nisl malesuada lacinia integer nunc posuere. Ut hendrerit semper vel class aptent taciti sociosqu.");
        controller.addMessageToHistory("Ad litora torquent per conubia nostra inceptos himenaeos.");

        controller.addMessageToHistory("Lorem ipsum dolor sit amet consectetur adipiscing elit. Quisque faucibus ex sapien vitae pellentesque sem placerat. In id cursus mi pretium tellus duis convallis. Tempus leo eu aenean sed diam urna tempor. Pulvinar vivamus fringilla lacus nec metus bibendum egestas. Iaculis massa nisl malesuada lacinia integer nunc posuere. Ut hendrerit semper vel class aptent taciti sociosqu. Ad litora torquent per conubia nostra inceptos himenaeos.");


        // TODO: listen for input in view, view sends input to controller to react
        while (true)
        {
            if (view.listenForInput() == 3) break;
        }

        return 0;
    }
}