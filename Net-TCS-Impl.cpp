// Net-TCS-Impl.cpp

#include "Constants.h"
#include "Controller.h"
#include "Net.h"

#include <cstddef>
#include <cstdint>

#define TINYCSOCKET_IMPLEMENTATION
#include "include/tinycsocket/tinycsocket.h"

namespace termChat 
{
// Move to config
const uint16_t TC_PORT = 6131;

struct NetManager::Impl
{
    TcsSocket socket;

    TcsSocket remoteSocket;
    TcsAddress remoteAddress;
};

NetManager::NetManager(const Controller& c)
    :   controller(c),
        p_netImpl(new Impl{
            .socket=TCS_SOCKET_INVALID,
            .remoteSocket=TCS_SOCKET_INVALID,
            .remoteAddress=TCS_ADDRESS_NONE
        })
{
    TcsResult result = tcs_lib_init();
    
    if (result != TCS_SUCCESS)
    {
        // Error handling
        exit(result);
    }

    result = tcs_tcp_server_str(
        &p_netImpl->socket, 
        "0.0.0.0", 
        termChat::TC_PORT
    );

    if (result != TCS_SUCCESS)
    {
        // Error handling
        tcs_close(&p_netImpl->socket);
        tcs_lib_free();
        exit(result);
    }
}

NetManager::~NetManager()
{
    tcs_close(&p_netImpl->socket);
    tcs_lib_free();
}

int NetManager::acceptConnections()
{
    tcs_accept(
        p_netImpl->socket,
        &p_netImpl->remoteSocket,
        &p_netImpl->remoteAddress);

    while (true)
    {
        NetMessageHeader header{};
        size_t bytes_recieved = 0;

        tcs_receive(
            p_netImpl->socket,
            (uint8_t*)&header,
            sizeof(header),
            0,
            &bytes_recieved);

        // Hack to circumvent blocking accept call
        // Sent from self to stop recieving connections, and connect to a remote
        // TODO: add a process-specific hash to the check to avoid another instance sending a malicious packet
        if (header.command == TC_COM_STOP && p_netImpl->remoteAddress.data.ip4.address == TCS_ADDRESS_LOOPBACK_IP4)
        {
            return 0;
        }
    }
}
} // namespace termChat