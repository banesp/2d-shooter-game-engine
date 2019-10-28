#ifndef TEXT_LABEL_COMPONENT_H
#define TEXT_LABEL_COMPONENT_H

#include "../Game.h"
#include "../EntityManager.h"
#include "../AssetManager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class TextLabelComponent : public Component
{
private:
    SDL_Rect position;
    std::string text;
    std::string fontFamily;
    SDL_Color color;
    SDL_Texture *texture = nullptr;

public:
    TextLabelComponent(int x, int y, std::string text, std::string fontFamily, const SDL_Color &color)
    {
        this->position.x = x;
        this->position.y = y;
        this->text = text;
        this->fontFamily = fontFamily;
        this->color = color;
        SetLabelText(text, fontFamily);
    }

    void SetLabelText(std::string text, std::string fontFamily)
    {
        // TODO: Global stuff
        SDL_Surface *surface = TTF_RenderText_Blended(Game::assetManager->GetFont(fontFamily), text.c_str(), this->color);
        this->texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
        SDL_FreeSurface(surface);
        SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
    }

    void Render() override
    {
        FontManager::Draw(texture, position);
    }
};

#endif