#include "Player.hpp"

Player::Player() {
    m_x = 0.0f;
    m_y = 0.0f;

    m_velocity = 0.0f;

    for (int i = 0; i < 2; i++)
        m_animations[i] = nullptr;
}

Player::Player(float x, float y) {
    m_x = x;
    m_y = y;

    m_velocity = 0.0f;

    for (int i = 0; i < 2; i++)
        m_animations[i] = nullptr;
}

Player::~Player() {
    for (int i = 0; i < 2; i++)
        m_animations[i] = nullptr;
}

bool Player::init(float x, float y)
{
    bool success = true;

    Player(x, y);
    
    return success;
}
