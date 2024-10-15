/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** NetworkMessages
*/

#pragma once

#include <cstdint>

enum class NetworkMessages : uint32_t {
  ServerAcceptance,
  ServerDenial,
  ServerPing,
  MessageAll,
  ServerMessage,
  ClientConnection
};

struct PositionComponent {
  float x;
  float y;
};