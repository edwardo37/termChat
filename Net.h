// Net.h
//
// Networking model
//
// Created by Cameron Schultz - 3/11/26

#include "Constants.h"
#include "Controller.h"

#include <cstddef>
#include <cstdint>
#include <memory>

namespace termChat 
{
    struct NetMessageHeader
    {
        const uint32_t contents_length;
        const Command command;
    };

    struct NetMessage
    {
        const NetMessageHeader header;
        const char* payload;
    };


    class NetManager
    {
        struct Impl;

        std::unique_ptr<Impl> p_netImpl;

        const Controller& controller;
    public:
        NetManager(const Controller& c);
        ~NetManager();

        // Error handling pls
        int acceptConnections();
        int stop_acceptConnections();

        // Error handling pls
        int connectToRemote(const char* host);
    };
}