// Model.h
//
// Everything to do with the messages in termChat
//
// Cameron Schultz - Created 2/28/26

#pragma once

#include <deque>
#include <string>

namespace termChat
{
    class IObserver;

    extern const size_t MAX_MESSAGE_HISTORY;

    // Singleton Message log
    class MessageHistory
    {
        std::deque<std::string> messages;

    public:
        MessageHistory();
        ~MessageHistory();

        std::deque<std::string>::iterator append(const char* m);

        const std::deque<std::string>& getMessages() const;
        const std::deque<std::string>* const operator->() const;
    };
}