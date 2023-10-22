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

	position.x += velocity.x;
	position.y += velocity.y;

	if (velocity.x > 0) velocity.x -= 0.5f;
	if (velocity.x < 0) velocity.x += 0.5f;

	if (velocity.y < maxVelocity.y) velocity.y++;
}

void Player::Show() {
  DrawRectangleV(position, size, MAROON);
};


CollisionTile Player::CheckCollisionWithTiles(std::vector<Tile>* collisions) {
	CollisionTile result;
	Tile tmp = {
		{ (float)50, (float)50 },
		{ (float)50, (float)50 },
	};
	result.tile = tmp;
	result.collisionSide = top;
	result.didCollisionHappen = false;

	for (auto tile : *collisions) {
		bool leftOverlap = 
			position.x < (tile.position.x + tile.size.x) &&
			position.x > tile.position.x;
		bool rightOverlap =
			(position.x + size.x) > tile.position.x &&
			(position.x + size.x) < tile.position.x + tile.size.x;
		bool topOverlap =
			position.y < (tile.position.y + tile.size.y) &&
			position.y > tile.position.y;
		bool bottomOverlap =
			(position.y + size.y) > tile.position.y &&
			(position.y + size.y) < tile.position.y + size.y;
 
		if ((rightOverlap || leftOverlap) && (topOverlap || bottomOverlap)) {
			result.didCollisionHappen = true;
			result.tile = tile;
			if (oldPosition.y > position.y) result.collisionSide = top;
			if (oldPosition.y < position.y) result.collisionSide = bottom;
			if (oldPosition.x > position.x) result.collisionSide = left;
			if (oldPosition.x < position.x) result.collisionSide = right;
		}
	};
	return result;
};

void Player::CollisionManager(CollisionTile collision) {
	if (collision.didCollisionHappen == 1) {
		switch(collision.collisionSide) {
			case top:
				velocity.y = 0;
				position.y = collision.tile.position.y + collision.tile.size.y;
				break;
			case bottom:
				velocity.y = 0;
				position.y = collision.tile.position.y - size.y;
				break;
			case left:
				velocity.x = 0;
				position.x = collision.tile.position.x + collision.tile.size.x;
				break;
			case right:
				velocity.x = 0;
				position.x = collision.tile.position.x - size.x;
				break;
		}		
	}
}



