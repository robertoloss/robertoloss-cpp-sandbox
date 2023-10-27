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

	position.x += velocity.x;
	position.y += velocity.y;

	if (velocity.x < maxVelocity.x) velocity.x += 0.5f;
	if (velocity.y < maxVelocity.y) velocity.y++;
}

void Player::Show() {
  DrawRectangleV(position, size, MAROON);
};

bool Player::CheckIfCollision(Tile* tile) {
	return (
		pLeft < tile->right &&
		pRight > tile->left &&
		pTop < tile->bottom &&
		pBottom > tile->top
	);
};

CollisionTile Player::CollisionDirection(Tile* tile) {
	if (velocity.x > 0) {
		if (velocity.y < 0) {
			float deltaY = tile->bottom - oldPosition.y;
			float velXvelYRatio = velocity.x / velocity.y;
			float inter = oldPosition.x + (deltaY * velXvelYRatio);
			if (inter < tile->left) return {*tile, right};
			else return {*tile, top};
		}
	}

};

void Player::CollisionManager(CollisionTile collision) {
	collision.tile.collision = true;
	switch (collision.collisionSide) {
		case right:
			pLeft = collision.tile.position.x - size.x;
			velocity.x = 0;
			std::cout << "right collision" << std::endl;
			break;
		 case left:
			pLeft = collision.tile.position.x + collision.tile.size.x;
			velocity.x = 0;
			std::cout << "left collision" << std::endl;
			break;
		 case top:
			position.y = collision.tile.position.y + collision.tile.size.y;
			velocity.y = 0;
			*jumping = false;
			std::cout << "top collision" << std::endl;
			break;
		 case bottom:
			position.y = collision.tile.position.y - (size.y);
			velocity.y = 0;
			std::cout << "bottom collision" << std::endl;
			break;
		 default:
			std::cout << "Default" << std::endl;
		}




} 

