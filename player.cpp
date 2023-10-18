#include "player.h"
#include <cmath>

void Player::CollisionWithScreenBorder (int screenWidth, int screenHeight) 
{
  if (position.x <= 0 || position.x+size.x >= screenWidth) {
    velocity.x = 0;
    position.x <= 0 ? position.x = 0 : position.x = (screenWidth-size.x);
  } 
  if (position.y < 0 || position.y+size.y > screenHeight) {
    velocity.y = 0;
    *jumping = false;
    if (position.y < 0) {
      position.y = 0;
    } else {
      position.y = (screenHeight-size.y);
    }
  } 
};

void Player::EventListeners() {
  if (IsKeyDown(KEY_RIGHT) && abs(velocity.x) < maxVelocity.x) velocity.x += 1.5f;
  if (IsKeyDown(KEY_LEFT) && abs(velocity.x) < maxVelocity.x) velocity.x -= 1.5f;
  if (IsKeyPressed(KEY_X) && *jumpingEnabled == true) {
    *jumping = true;
    xPressedCount += 1;
    velocity.y = 0;
    jumpVelocity = initialJumpVelocity;
    jumpAcceleration = initialJumpAcceleration;
    jumpInitialHeight = position.y;
  }

  if (IsKeyReleased(KEY_X)) {
    *jumping = false;
  }
  if (IsKeyDown(KEY_ESCAPE)) WindowShouldClose();
  
  if (jumping) {
    if (jumpInitialHeight - position.y  >= jumpMaxHeight) {
      *jumping = false;
      jumpAcceleration = initialJumpAcceleration;         
      jumpVelocity = initialJumpVelocity;
    } else {
      if (abs(velocity.y) < maxJumpVelocity && position.y > 0) velocity.y -= jumpVelocity;
    }
  }
}


void Player::Move() {
   position.x += velocity.x;
   position.y += velocity.y;
 
   if (velocity.x > 0) velocity.x -= 0.5f;
   if (velocity.x < 0) velocity.x += 0.5f;
 
   if (velocity.y < maxVelocity.y) velocity.y++;
}

void Player::Show() {
  Draw(position, size, MAROON);
};
