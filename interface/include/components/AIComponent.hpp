/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AIComponent
*/

#pragma once

#include <r-type/AComponent.hpp>

namespace component
{

  enum class AIType
  {
    LINEAR,
    SINUSOIDAL,
    CIRCULAR,
  };
  class AIComponent : public AComponent
  {
  public:
    AIComponent(uint32_t entityID, AIType type);
    ~AIComponent();

    AIType getType();
    void setType(AIType type);

    float getElapsedTime();
    void setElapsedTime(float elapsedTime);

    void update(AIType type, float elapsedTime);

  private:
    AIType _type;
    float _elapsedTime;
  };
}