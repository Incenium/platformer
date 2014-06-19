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

void Player::handleInput(SDL_Event e) {
	if (e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
			case SDLK_LEFT:
				m_currentAnimation = PLAYER_RUNNING_LEFT;
				m_x -= 10;
				break;
			case SDLK_RIGHT:
				m_currentAnimation = PLAYER_RUNNING_RIGHT;
				m_x += 10;
				break;
		}
	}
}
void Player::update(float deltaTime) {
	m_animations[m_currentAnimation]->run();
}
void Player::render(SDL_Renderer* renderer) {
	m_animations[m_currentAnimation]->render(m_x, m_y, renderer);
}

bool Player::init(float x, float y) {
    bool success = true;

    Player(x, y);

	return success;
}