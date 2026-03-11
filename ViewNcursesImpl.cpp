#include "View.h"

#include "Controller.h"
#include "Constants.h"

#include <ncurses/ncurses.h>

#include <memory>
#include <cstddef>

namespace termChat
{
enum class colorPairs : short
{
    standard, inverted
}; constexpr short TO_SHORT(colorPairs c) noexcept { return static_cast<short>(c); }


View::View()
{
    initscr();
    start_color();
    if (!has_colors())
    {
        endwin();
        // error handling plz
    }
    noecho();
    raw();
    keypad(stdscr, true);
    refresh();
}

View::~View()
{
    endwin();
}

void View::setController(Controller* c) { controller = c; }

int View::listenForInput()
{
    int c = getch();

    KeyEvent ke = toKeyEvent(c);

    return controller->handleKeyEvent(ke);
}

KeyEvent View::toKeyEvent(int c)
{
    if (c > 31 && c < 256) return KeyEvent{ TC_KEY_CHAR, static_cast<char>(c) };

    KeyEvent ke{TC_KEY_NULL, '\0'};

    switch (c)
    {
        case KEY_UP:
            ke.code = TC_KEY_UP; break;
        case KEY_DOWN:
            ke.code = TC_KEY_DOWN; break;
        case KEY_LEFT:
            ke.code = TC_KEY_LEFT; break;
        case KEY_RIGHT:
            ke.code = TC_KEY_RIGHT; break;

        case KEY_ENTER:
            ke.code = TC_KEY_ENTER; break;
        case 3:
            ke.code = TC_KEY_INT; break;
    }

    return ke;
}


struct ViewImpl
{
    WINDOW* window;
};


MessageHistoryView::MessageHistoryView()
    : p_viewImpl(new ViewImpl{newwin(getmaxy(stdscr) - 2, getmaxx(stdscr), 0, 0)})
{
    wclear(p_viewImpl->window);
    wrefresh(p_viewImpl->window);

    init_pair(TO_SHORT(colorPairs::standard), COLOR_WHITE, COLOR_BLACK);
    init_pair(TO_SHORT(colorPairs::inverted), COLOR_BLACK, COLOR_WHITE);
}

MessageHistoryView::~MessageHistoryView()
{
    delwin(p_viewImpl->window);
}


void MessageHistoryView::renderMessageHistory(
    const std::deque<std::string>& message_history,
    const size_t begin,
    const size_t selected_message
)
{
    wclear(p_viewImpl->window);

    size_t current = begin + 1, 
    lines_in_message = 0;

    int lineNo, 
    max_y = getmaxy(p_viewImpl->window);

    for (
        lineNo = max_y;
        lineNo >= 0 && current;
        //
    ) {
        --current;

        // lines = characters / charactersPerLine, +1 because floor divide
        lines_in_message = getMessageHeight(message_history[current]);

        // Decrement line number after getting current message height
        lineNo -= lines_in_message;

        // Current line is the selected one, highlight it
        if (current == selected_message)
        {
            wattron(p_viewImpl->window, COLOR_PAIR(TO_SHORT(colorPairs::inverted)));
            // Print background for all characters on last line of message, to "pre-fill"...
            mvwhline(p_viewImpl->window, lineNo + lines_in_message - 1, 0, ' ', getmaxx(p_viewImpl->window));
        }

        // ...then print the message
        mvwprintw(p_viewImpl->window, lineNo, 0, "%s", message_history[current].c_str());

        // Reset selection
        wattroff(p_viewImpl->window, COLOR_PAIR(TO_SHORT(colorPairs::inverted)));
    }

    // Line is above screen and clips back onto screen
    if (lineNo < 0 && lines_in_message + lineNo)
    {
        // Fix post-inc of last iter
        // ++current;

        // Set highlight again, turned off after loop iter
        // The ending blanks will always be correct, just the message overwrites it
        if (selected_message == current) wattron(p_viewImpl->window, COLOR_PAIR(TO_SHORT(colorPairs::inverted)));

        mvwprintw(
            p_viewImpl->window,
            0, 0,
            "%s",
            message_history[current].substr(
                // Start at first line (abs(lineNo) * width) that clips screen, until end
                lineNo * -1 * getmaxx(p_viewImpl->window)
            ).c_str()
        );

        wattroff(p_viewImpl->window, COLOR_PAIR(TO_SHORT(colorPairs::inverted)));
    }

    wrefresh(p_viewImpl->window);
}

const size_t MessageHistoryView::getLineCount() const { return getmaxy(p_viewImpl->window); }

const int MessageHistoryView::getMessageHeight(const std::string message) const
{ return (message.length() / getmaxx(p_viewImpl->window)) + 1; }




InputFieldView::InputFieldView()
    : p_viewImpl(new ViewImpl{newwin(2, getmaxx(stdscr), getmaxy(stdscr) - 2, 0)})
{
    render("");
}

InputFieldView::~InputFieldView()
{
    delwin(p_viewImpl->window);
}

void InputFieldView::render(const char* message)
{
    wclear(p_viewImpl->window);
    mvwhline(p_viewImpl->window, 0, 0, '-', getmaxx(p_viewImpl->window));
    mvwprintw(p_viewImpl->window, 1, 0, "%s", message);
    wrefresh(p_viewImpl->window);
}
}