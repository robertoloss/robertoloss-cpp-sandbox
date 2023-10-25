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
//	if(fabs(oldPosition.x - position.x) > 1 ) {
//		printf("\noldPosition.x : %f, position.x %f", oldPosition.x, position.x);
//	}
	if (velocity.x > 0) velocity.x -= 0.5f;
	if (velocity.x < 0) velocity.x += 0.5f;

	if (velocity.y < maxVelocity.y) velocity.y++;
}

void Player::Show() {
  DrawRectangleV(position, size, MAROON);
};

bool Player::CheckIfCollision(Tile* tile) {
	return (
		position.x < tile->position.x + tile->size.x &&
		position.x + size.x > tile->position.x &&
		position.y < tile->position.y + tile->size.y &&
		position.y + size.y > tile->position.y
	);
};

float Player::overlap(direction direction, Tile* tile) {
	switch (direction) {
		case top:
			return (tile->position.y + tile->size.y )  - position.y;
		case bottom:
			return (position.y + size.y) - tile->position.y;
		case left:
			return (tile->position.x + tile->size.x) - position.x;
		case right:
			return (position.x + size.x) - tile->position.x;
	}
}

float Player::axisOverlap(MovementAxis axis, Tile* tile) {
	switch (axis) {
		case xAxis:
			if (position.x + size.x > tile->position.x + tile->size.x) {
				return (tile->position.x + tile->size.x) - position.x;
			} else if (position.x < tile->position.x) {
				return (position.x + size.x) - tile->position.x;
			}
			return size.x;
		case yAxis:
			if (position.y + size.y > tile->position.y + tile->size.y) {
				return (tile->position.y + tile->size.y) - position.y;
			} else if (position.y < tile->position.y) {
				return (position.y + size.y) - tile->position.y;
			}
			return size.y;
	}
}

CollisionTile Player::CollisionDirection(Tile* tile) {

	if (oldPosition.x < position.x &&
			pLeft < tile->left &&
			overlap(right,tile) < axisOverlap(yAxis, tile) 
	) {
		std::cout << "Coll Dir: Right" << std::endl;
		return {*tile, right};
	}

	if (oldPosition.x > position.x &&
			pRight > tile->right &&
			overlap(left,tile) < axisOverlap(yAxis,tile)
	) return {*tile, left};

	if (oldPosition.y < position.y &&
			pTop < tile->top &&
			overlap(bottom, tile) < axisOverlap(xAxis,tile) 
		) return {*tile, bottom};

	if (oldPosition.y > position.y &&
			pBottom > tile->bottom &&
			overlap(top,tile) < axisOverlap(xAxis,tile)
	) return {*tile, top};
	return {*tile,top};
};

void Player::CollisionManager(CollisionTile collision) {
	switch (collision.collisionSide) {
		case right:
			position.x = collision.tile.position.x - (size.x);
			velocity.x = 0;
			std::cout << "right collision" << std::endl;
			break;
		 case left:
			position.x = collision.tile.position.x + collision.tile.size.x;
			velocity.x = 0;
			std::cout << "left collision" << std::endl;
			break;
		 case top:
			position.y = collision.tile.position.y + collision.tile.size.y;
			velocity.y = 0;
			*jumping = false;
			break;
		 case bottom:
			std::cout << "Manager: bottom" << std::endl;
			position.y = collision.tile.position.y - (size.y);
			velocity.y = 0;
			break;
		}
} 

