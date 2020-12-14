#pragma once
#include "Entity/Entity.h"
#include <unordered_map>
#include <vector>

#define ANIMATE_ONCE       0x01
#define ANIMATE_REPEAT     0x02
#define ANIMATE_BACKNFORTH 0x03

struct AnimationFrames {
	std::vector<sf::Sprite*> sprites;
	vec2f animation_scale;
};

class Animation
{
public:
	void update(const float& dt);
	bool set_sprite_sheet(const std::string& texture_name);
	bool play_animation(const std::string& name, uint8_t fps, uint8_t mode = ANIMATE_ONCE, uint32_t repeat_from = 0u);
	bool new_animation(const std::string& name, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t frames);
	void stop();
	void pause();
	void resume();

	Animation(Entity* animation_owner);
	virtual ~Animation();
private:
	void play_frame(uint16_t frame);

private:
	bool m_EverPlayed = false;
	bool m_StopAnimation = false;
	bool m_PlayBackward = false;
	float m_FrameTime = 0.f;
	float m_TimeElapsed = 0.f;
	uint8_t m_PlayMode = ANIMATE_ONCE;
	uint32_t m_Frames = 0u;
	uint32_t m_CurrentFrame = 0u;
	uint32_t m_RepeatFrom = 0u;

	AnimationFrames* m_CurrentAnimation = nullptr;
	sf::Texture* m_SpriteSheet = nullptr;
	std::unordered_map<std::string, AnimationFrames> m_Animations;
	Entity* m_AnimationOwner = nullptr;
};