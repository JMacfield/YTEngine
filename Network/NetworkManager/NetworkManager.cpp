#include "NetworkManager.h"
#include "IPEndpoint.h"
#include "Packet.h"
#include <iostream>
#include <cstring>

namespace YTEngine
{
    NetworkManager::NetworkManager() : connection(nullptr), isRunning(false) {}

    NetworkManager::~NetworkManager()
    {
        Shutdown();
    }

    bool NetworkManager::Initialize()
    {
        if (!YNet::Network::Initialize())
        {
            std::cerr << "Failed to initialize network system." << std::endl;
            return false;
        }
        return true;
    }

    void NetworkManager::Shutdown()
    {
        isRunning = false;

        if (receiveThread.joinable())
        {
            receiveThread.join();
        }

        if (connection)
        {
            connection->Close();
            delete connection;
            connection = nullptr;
        }

        YNet::Network::Shutdown();
    }

    bool NetworkManager::Connect(const std::string& ip, uint16_t port)
    {
        const char* cstr = ip.c_str();

        YNet::IPEndpoint endpoint(cstr, port);

        YNet::Socket socket;
        if (!socket.Create())
        {
            std::cerr << "Failed to create socket." << std::endl;
            return false;
        }

        if (!socket.Connect(endpoint))
        {
            std::cerr << "Failed to connect to server: " << endpoint.ToString() << std::endl;
            return false;
        }

        connection = new YNet::TCPConnection(std::move(socket), endpoint);
        isRunning = true;
        receiveThread = std::thread(&NetworkManager::ReceiveLoop, this);

        return true;
    }

    void NetworkManager::Send(const std::vector<char>& data)
    {
        if (connection)
        {
            connection->socket.SendAll(data.data(), static_cast<int>(data.size()));
        }
    }

    void NetworkManager::SetReceiveCallback(DataCallback callback)
    {
        std::lock_guard<std::mutex> lock(receiveMutex);
        dataCallback = callback;
    }

    void NetworkManager::Update()
    {
        std::lock_guard<std::mutex> lock(receiveMutex);
        while (!receiveQueue.empty())
        {
            auto data = std::move(receiveQueue.front());
            receiveQueue.pop();

            if (dataCallback)
            {
                dataCallback(data);
            }
        }
    }

    void NetworkManager::ReceiveLoop()
    {
        while (isRunning)
        {
            char buffer[1024];
            int bytesReceived = connection->socket.RecvAll(buffer, sizeof(buffer));

            if (bytesReceived > 0)
            {
                std::lock_guard<std::mutex> lock(receiveMutex);
                receiveQueue.push(std::vector<char>(buffer, buffer + bytesReceived));
            }
            else if (bytesReceived == 0)
            {
                std::cerr << "Server closed the connection." << std::endl;
                isRunning = false;
            }
            else
            {
                std::cerr << "Error while receiving data." << std::endl;
                isRunning = false;
            }
        }
    }
}
