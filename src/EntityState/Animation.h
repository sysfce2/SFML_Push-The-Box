#pragma once
#include "EntityState/Entity.h"
#include <unordered_map>
#include <vector>

#define AN_ONCE       0x01
#define AN_REPEAT     0x02
#define AN_BACKNFORTH 0x03

using AnimationFrames = std::vector<sf::Sprite*>;

class Animation
{
public:
	void update(const float& dt);
	bool load_sprite_sheet(const std::string& texture_name);
	bool play_animation(const std::string& name, uint8_t fps,
		               uint8_t mode = AN_ONCE, uint8_t repeat_from = 0);
	bool new_animation(const std::string& name, uint16_t x, uint16_t y,
					   uint16_t w, uint16_t h, uint8_t frames);
	void start_stop();

	Animation(Entity* animation_owner);
	virtual ~Animation();
private:
	void play_frame(uint16_t frame);

private:
	bool m_EverPlayed = false;
	bool m_StopAnimation = false;
	float m_FrameTime = 0.f;
	float m_TimeElapsed = 0.f;
	uint8_t m_PlayMode = AN_ONCE;
	uint8_t m_FrameSwitchDirection = 1;
	uint8_t m_Frames = 0;
	uint8_t m_CurrentFrame = 0;
	uint8_t m_RepeatFrom = 0;

	AnimationFrames* m_CurrentAnimation = nullptr;
	sf::Texture* m_SpriteSheet = nullptr;
	std::unordered_map<std::string, AnimationFrames> m_Animations;
	Entity* m_AnimationOwner = nullptr;
};