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
	// printf("\n\noldPosition.x %f", oldPosition.x);
	// printf("\nposition.x %f", position.x);
	position.x += velocity.x;
	position.y += velocity.y;
	// printf("\nposition.x %f", position.x);
	// printf("\noldPosition.x %f", oldPosition.x);
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
		pLeft < tile->right &&
		pRight > tile->left &&
		pTop < tile->bottom &&
		pBottom > tile->top
	);
};

float Player::overlap(direction direction, Tile* tile) {
	switch (direction) {
		case top:
			return tile->bottom - pTop;
		case bottom:
			return pBottom - tile->top;
		case left:
			return tile->right - pLeft;
		case right:
			return pRight - tile->left;
	}
}

float Player::axisOverlap(MovementAxis axis, Tile* tile) {
	switch (axis) {
		case xAxis:
			if (pRight > tile->right) {
				return (tile->right) - pLeft;
			} else if (pLeft < tile->left) {
				return (pRight) - tile->left;
			}
			return size.x;
		case yAxis:
			if (position.y + size.y > tile->bottom) {
				return (tile->bottom) - position.y;
			} else if (position.y < tile->left) {
				return (position.y + size.y) - tile->left;
			}
			return size.y;
	}
}

CollisionTile Player::CollisionDirection(Tile* tile) {
	// printf("\noldPosition.x %f", oldPosition.x);
	// printf("\npLeft %f", pLeft);
	// bool condition = oldPosition.x < pLeft ;
	// bool condition = oldPosition.x < pLeft && pLeft < tile->left;
	// std::cout << "\ncondition :" << condition << std::endl;
	if (velocity.x > 0 && pLeft < tile->left) {
		std::cout << "right hit" << std::endl;
		if (velocity.y == 0 ) return {*tile, right}; 
		if (pTop <= tile->top && pBottom >= tile->bottom) return {*tile, right};
		if (velocity.y < 0) {
			if (pTop > tile->top) return {*tile, right};
			else {
				float yXratio = (pTop - (oldPosition.y)) / (pRight - (oldPosition.x + size.x)); 
				float diffY = oldPosition.y - tile->bottom;
				float xOfYtile = oldPosition.x + (diffY * yXratio);

				if (xOfYtile > tile->left) return {*tile, top};
				else return {*tile, right};
			}
		} else {
			if (pBottom > tile->bottom) return {*tile, right};
			else {
				float yXratio = (pBottom - (oldPosition.y + size.y)) / (pRight - (oldPosition.x + size.x));
				float diffY = tile->top - (oldPosition.y + size.y);
				float xOfYtile = oldPosition.x + (diffY * yXratio);

				if (xOfYtile > tile->left) return {*tile, top};
				else return {*tile, right};
			}
		}
	}

	// if (oldPosition.x > pLeft &&
	// 		pRight > tile->right &&
	// 		overlap(left,tile) < axisOverlap(yAxis,tile)
	// ) return {*tile, left};

	// if (oldPosition.y < position.y &&
	// 		pTop < tile->top &&
	// 		overlap(bottom, tile) < axisOverlap(xAxis,tile) 
	// 	) return {*tile, bottom};

	// if (oldPosition.y > position.y &&
	// 		pBottom > tile->bottom &&
	// 		overlap(top,tile) < axisOverlap(xAxis,tile)
	// ) return {*tile, top};
	// return {*tile,top};
};

void Player::CollisionManager(CollisionTile collision) {
	switch (collision.collisionSide) {
		case right:
			pLeft = collision.tile.position.x - (size.x - 50);
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
			std::cout << "Manager: bottom" << std::endl;
			position.y = collision.tile.position.y - (size.y);
			velocity.y = 0;
			std::cout << "bottom collision" << std::endl;
			break;
		}
} 

