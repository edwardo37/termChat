// Model.cpp

#include "Model.h"

#include <cstddef>
#include <deque>
#include <string>

namespace termChat
{
    const size_t MAX_MESSAGE_HISTORY = 256;

    MessageHistory::MessageHistory() = default;
    MessageHistory::~MessageHistory() = default;

    std::deque<std::string>::iterator MessageHistory::append(const char* message)
    {
        if (messages.size() >= MAX_MESSAGE_HISTORY)
        {
            messages.pop_front();
        }

        messages.push_back(message);

        return messages.end() - 1;
    }

    const std::deque<std::string>& MessageHistory::getMessages() const { return messages; }
    const std::deque<std::string>* const MessageHistory::operator->() const { return &messages; }
}