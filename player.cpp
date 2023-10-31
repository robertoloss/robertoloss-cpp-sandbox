#include "player.h"
#include <ios>
#include <iostream>
#include "raylib.h"
#include <cmath>
#include <cstdio>


void Player::CollisionWithScreenBorder (int screenWidth, int screenHeight) 
{
  if (position.x <= 0 || position.x+size.x >= screenWidth) {
    velocity.x = 0;
    position.x <= 0 ? position.x = 0 : position.x = (screenWidth-size.x);
  } 
  if (position.y + velocity.y < 0 || position.y + size.y + velocity.y > screenHeight) {
    velocity.y = 0;
    *jumping = false;
    if (position.y + velocity.y < 0) {
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
  
  if (*jumping) {
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
	oldPosition.x = position.x;
	oldPosition.y = position.y;
	pLeft = position.x;
	pRight = position.x + size.x;
	pTop = position.y;
	pBottom = position.y + size.y;

  float num = (float)1000 / (float)16;

	if (velocity.x > 0) velocity.x -= 0.5f;
	if (velocity.x < 0) velocity.x += 0.5f;
  
	if (velocity.y < maxVelocity.y) velocity.y += gravity;

	position.x += velocity.x * GetFrameTime() * num;
	position.y += velocity.y * GetFrameTime() * num;

}

void Player::Show() {
  DrawRectangleV(position, size, MAROON);
};

void Player::CheckIfCollision(Tile* tile) {
	if (
		velocity.y < 0 &&
		pTop + velocity.y < tile->bottom &&
		pBottom + velocity.y > tile->bottom &&
		pRight > tile->left &&
		pLeft < tile->right	
	) {
		//std::cout << "top collision" << std::endl;
		velocity.y = 0;
		position.y = tile->bottom;
		*jumping = false;
		return;
	}
	if (
		velocity.x > 0 &&
		pRight + velocity.x > tile->left &&
		pLeft + velocity.x < tile->left &&
		pBottom > tile->top &&
		pTop < tile->bottom - maxVelocity.y
	) {
		//std::cout << "right collision" << std::endl;
		velocity.x = 0;
		position.x = tile->position.x - size.x;
		return;
	}
	if (
		velocity.x < 0 &&
		pLeft + velocity.x < tile->right &&
	  pRight + velocity.x > tile->right &&
		pBottom > tile->top &&
		pTop < tile->bottom - maxVelocity.y
	) {
		// std::cout << "left collision" << std::endl;
		velocity.x = 0;
		position.x = tile->right;
		return;
	}
	
	if (
		velocity.y > 0 &&
		pBottom + velocity.y > tile->top &&
		pTop + velocity.y < tile->top &&
		pRight > tile->left &&
		pLeft < tile->right	
	) {
		// std::cout << "bottom collision" << std::endl;
		velocity.y = 0;
		position.y = tile->top - size.y;	
	}
};

 
