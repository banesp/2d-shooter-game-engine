#include "../Components/TileComponent.h"
#include <iostream>

TileComponent::TileComponent(int sourceRectX, int sourceRectY, int x, int y, int tileSize, int tileScale, SDL_Texture *texture)
{
    this->texture = texture;

    sourceRectangle.x = sourceRectX;
    sourceRectangle.y = sourceRectY;
    sourceRectangle.w = tileSize;
    sourceRectangle.h = tileSize;

    destinationRectangle.x = x;
    destinationRectangle.y = y;
    destinationRectangle.w = tileSize * tileScale;
    destinationRectangle.h = tileSize * tileScale;

    position.x = x;
    position.y = y;
}

TileComponent::~TileComponent()
{
    this->texture = nullptr;
}

void TileComponent::Update(float deltaTime)
{
    destinationRectangle.x = position.x - Game::camera.x;
    destinationRectangle.y = position.y - Game::camera.y;
}

void TileComponent::Render()
{
    TextureAPI::Draw(texture, sourceRectangle, destinationRectangle, SDL_FLIP_NONE);
}
