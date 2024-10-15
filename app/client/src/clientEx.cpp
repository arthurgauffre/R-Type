/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** clientEx
*/

#include <Client.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

void simpleClient()
{
  rtype::network::Client c;
  c.Connect("127.0.0.1", 60000);
  std::cout << "Socket: " << c.GetConnection()->GetSocket() << std::endl;
  std::cout << "Endpoint: " << c.GetConnection()->GetEndpoint() << std::endl;
  sf::RenderWindow window(sf::VideoMode(800, 600), "Preferences");
  sf::Event event;
  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Space: {
          std::cout << "space" << std::endl;
          c.PingServer();
        } break;
        case sf::Keyboard::C: {
          std::cout << "C" << std::endl;
          c.CreateEntity();
        } break;
        case sf::Keyboard::Q: {
          std::cout << "Q" << std::endl;
          window.close();
        } break;
        case sf::Keyboard::V: {
          std::cout << "V" << std::endl;
          c.SendMessageToAllClients();
        } break;
        default:
          break;
        }
      }
    }
    if (c.IsConnected()) {
      if (!c.GetIncomingMessages().empty()) {
        std::cout << "Incoming" << std::endl;
        auto msg = c.GetIncomingMessages().popFront().message;
        switch (msg.header.id) {
        case NetworkMessages::ServerAcceptance: {
          std::cout << "Server Accepted Connection" << std::endl;
        } break;

        case NetworkMessages::ServerPing: {
          std::chrono::system_clock::time_point timeNow =
              std::chrono::system_clock::now();
          std::chrono::system_clock::time_point timeThen;
          msg >> timeThen;
          std::cout << "Ping: "
                    << std::chrono::duration<double>(timeNow - timeThen).count()
                    << std::endl;
        } break;

        case NetworkMessages::ServerMessage: {
          uint32_t clientID;
          msg >> clientID;
          std::cout << "Hello from [" << clientID << "]" << std::endl;
        } break;
        case NetworkMessages::ServerDenial: {

        } break;
        case NetworkMessages::MessageAll: {

        } break;
        case NetworkMessages::ClientConnection: {
        } break;
        case NetworkMessages::createEntity: {
          std::cout << "Entity created" << std::endl;
        } break;
        }
      }
    } else {
      std::cout << "Server Down" << std::endl;
      window.close();
      break;
    }

    window.clear();
    window.display();
  }
}
