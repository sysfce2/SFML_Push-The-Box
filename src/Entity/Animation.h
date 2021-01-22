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
	bool play_animation(const std::string& name, u8 fps, u8 mode = ANIMATE_ONCE, u32 repeat_from = 0);
	bool new_animation(const std::string& name, u16 x, u16 y, u16 w, u16 h, u32 frames);
	inline std::string get_animation_name() const { return m_CurrentAnimationName; }
	void stop();
	void pause();
	void resume();

	Animation(Entity* animation_owner);
	virtual ~Animation();
private:
	void play_frame(u16 frame);

private:
	bool m_EverPlayed = false;
	bool m_StopAnimation = false;
	bool m_PlayBackward = false;
	float m_FrameTime = 0.f;
	float m_TimeElapsed = 0.f;
	u8 m_PlayMode = ANIMATE_ONCE;
	u32 m_Frames = 0;
	u32 m_CurrentFrame = 0;
	u32 m_RepeatFrom = 0;
	std::string m_CurrentAnimationName;

	AnimationFrames* m_CurrentAnimation = nullptr;
	sf::Texture* m_SpriteSheet = nullptr;
	std::unordered_map<std::string, AnimationFrames> m_Animations;
	Entity* m_AnimationOwner = nullptr;
};