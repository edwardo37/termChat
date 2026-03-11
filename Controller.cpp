// Controller.cpp

#include "Controller.h"

#include "Model.h"
#include "View.h"
#include "Constants.h"

namespace termChat
{
Controller::Controller(MessageHistory& model, View& view)
    :   main_view(view),
        MH_model(model),
        MH_view{},
        MH_viewport{0, 0, true},
        IF_view{}
{
}

Controller::~Controller() = default;

// Controller private:
int Controller::renderCurrentMessageHistory()
{
    MH_view.renderMessageHistory(
        MH_model.getMessages(), 
        MH_viewport.start, 
        MH_viewport.selected
    );

    return 0;
}

bool Controller::tryMoveSelectedDown()
{
    // If max size, abort since cannot traverse farther
    if (MH_viewport.selected == MH_model->size() - 1) return false;
    // Else, increase and succeed

    // If at the bottom of the screen, also increase the viewport start
    if (MH_viewport.selected == MH_viewport.start) ++MH_viewport.start;

    ++MH_viewport.selected;

    // Check if selected at max after update to tag followLatest
    if (MH_viewport.selected == MH_model->size() - 1) MH_viewport.followLatest = true;

    return true;
}

bool Controller::tryMoveSelectedUp()
{
    // The fun one, since we print from the bottom up

    // Detach it from the latest
    MH_viewport.followLatest = false;

    // If selected == 0, can't move up
    if (!MH_viewport.selected) return false;


    // Determine whether viewport start needs to move up
    int usedLines = 0, currentMessageHeight = 0;
    size_t current;
    // Count messages bottom up until min(selected->next doesn't fit on screen, or until current == selected->next)
    for (
        current = MH_viewport.start+1;
        current != MH_viewport.selected-1;
        //
    ) {
        --current;

        currentMessageHeight = MH_view.getMessageHeight(MH_model->at(current));

        if (usedLines + currentMessageHeight >= MH_view.getLineCount()) {
            --MH_viewport.start;
            break;
        }

        usedLines += currentMessageHeight;
    }

    --MH_viewport.selected;

    return true;
}

// Controller public:

int Controller::addMessageToHistory(const char* message)
{   
    MH_model.append(message);

    // Follow the latest message
    if (MH_viewport.followLatest) tryMoveSelectedDown();

    // Else follow the current message
    // Only needs to move up if size is full and history begins to pop_front -- it is index-based
    else if (MH_model->size() == MAX_MESSAGE_HISTORY) tryMoveSelectedUp();

    renderCurrentMessageHistory();

    return 0;
}

int Controller::handleKeyEvent(const KeyEvent ke)
{
    switch (ke.code)
    {
        case TC_KEY_CHAR:
            addMessageToHistory((char[]){ke.c, '\0'}); break;
        case TC_KEY_UP:
            tryMoveSelectedUp();
            break;
        case TC_KEY_DOWN:
            tryMoveSelectedDown();
            break;
        case TC_KEY_INT:
            return 3;
        default:
            break;
    }

    renderCurrentMessageHistory();

    return 0;
}
} // namespace termChat