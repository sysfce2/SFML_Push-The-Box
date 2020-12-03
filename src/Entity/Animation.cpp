#include "Entity/Animation.h"
#include "Core/AssetsManager.h"
#include "Core/Window.h"
#include "Core/Logger.h"

void Animation::update(const float& dt)
{
    if (!m_StopAnimation) {
        m_TimeElapsed += dt;
        switch (m_PlayMode) {
        case AN_ONCE:
            if (m_CurrentFrame < m_Frames) {
                if (m_TimeElapsed >= m_FrameTime) {
                    play_frame(m_CurrentFrame);
                    m_TimeElapsed -= m_FrameTime;
                    m_CurrentFrame++;
                }
            }
            else m_StopAnimation = true;
            break;
        case AN_REPEAT:
            if (m_TimeElapsed >= m_FrameTime) {
                play_frame(m_CurrentFrame);
                m_TimeElapsed -= m_FrameTime;
                m_CurrentFrame++;
                if (m_CurrentFrame == m_Frames)
                    m_CurrentFrame = m_RepeatFrom;
            }
            break;
        case AN_BACKNFORTH:
            if (m_TimeElapsed >= m_FrameTime) {
                play_frame(m_CurrentFrame);
                m_TimeElapsed -= m_FrameTime;
                if (!m_PlayBackward && m_CurrentFrame == m_Frames - 1)
                    m_PlayBackward = true;
                else if (m_PlayBackward && m_CurrentFrame == m_RepeatFrom)
                    m_PlayBackward = false;
                m_CurrentFrame = m_PlayBackward ? -1 : 1;
            }
            break;
        default:
            break;
        }
    }
}

bool Animation::set_sprite_sheet(const std::string& texture_name)
{
    m_SpriteSheet = AssetsManager::get().get_texture(texture_name);
    return m_SpriteSheet != nullptr;
}

void Animation::stop()
{
    if (m_CurrentAnimation != nullptr) {
        play_frame(0);
        m_StopAnimation = true;
    }
}

void Animation::pause()
{
    if (m_CurrentAnimation != nullptr) 
        m_StopAnimation = true;
}

void Animation::resume()
{
    if (m_CurrentAnimation != nullptr)
        m_StopAnimation = false;
}

bool Animation::play_animation(const std::string& name, uint8_t fps, uint8_t mode, uint32_t repeat_from)
{
    if (m_Animations.find(name) != m_Animations.end()) {
        AnimationFrames* frames = &m_Animations.at(name);
        if (mode <= AN_BACKNFORTH) {
            if (m_Frames == 1u) m_PlayMode = AN_ONCE;
            else m_PlayMode = mode;
            m_Frames = static_cast<uint32_t>(frames->size());
            m_CurrentAnimation = frames;
            m_RepeatFrom = repeat_from;
            m_FrameTime = 1.f / fps;
            m_TimeElapsed = 0.f;
            m_CurrentFrame = 1u;
            m_PlayBackward = false;
            m_StopAnimation = false;
            m_EverPlayed = true;
            play_frame(0);
            return true;
        }
        else return false;
    }
    else return false;
}

void Animation::play_frame(uint16_t frame)
{
    if (frame >= 0 && frame < m_Frames)
        m_AnimationOwner->set_sprite(m_CurrentAnimation->at(frame), false);
}

bool Animation::new_animation(const std::string& name, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t frames)
{
    if (m_SpriteSheet != nullptr) {
        m_Animations[name] = std::vector<sf::Sprite*>();
        for (uint16_t i = x; i < x + w * frames; i += w) {
            vec2f scale = { m_AnimationOwner->m_Scale.x * Window::res_scale().x,
                            m_AnimationOwner->m_Scale.y * Window::res_scale().y };
            sf::Sprite* spr = new sf::Sprite();
            spr->setTexture(*m_SpriteSheet);
            spr->setTextureRect(sf::IntRect(i, y, w, h));
            spr->setScale(scale);
            m_Animations[name].emplace_back(spr);
        }
        return true;
    }
    return false;
}

Animation::Animation(Entity* animation_owner)
    : m_AnimationOwner(animation_owner)
{
}

Animation::~Animation()
{
    if (m_EverPlayed) 
        m_AnimationOwner->m_Sprite = nullptr;
    for (auto& anim : m_Animations)
        for (auto& spr : anim.second)
            delete spr;
}
