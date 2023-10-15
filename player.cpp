#include "player.h"

void Player::CollisionWithScreenBorder
(
  Vector2* position, 
  Vector2* velocity, 
  int screenWidth, 
  int screenHeight, 
  Vector2 size,
  bool * jumping,
  bool * jumpingEnabled
) 
{
  if (position->x <= 0 || position->x+size.x >= screenWidth) {
    velocity->x = 0;
    position->x <= 0 ? position->x = 0 : position->x = (screenWidth-size.x);
  } 
  if (position->y < 0 || position->y+size.y > screenHeight) {
    velocity->y = 0;
    *jumping = false;
    if (position->y < 0) {
      position->y = 0;
    } else {
      position->y = (screenHeight-size.y);
    }
  } 
};
