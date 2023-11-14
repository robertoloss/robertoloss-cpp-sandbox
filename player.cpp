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
  if (IsKeyPressed(KEY_RIGHT)) {
		goRight = true;
		goLeft = false;
	}
	if (IsKeyReleased(KEY_RIGHT)) {
		goRight = false;
	}

  if (IsKeyPressed(KEY_LEFT)) {
		goLeft = true;
		goRight = false;
	};

  if (IsKeyReleased(KEY_LEFT)) {
		goLeft = false;
	}

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

	if (IsKeyPressed(KEY_S)) {
		if (size.x == 50.0f && abs(velocity.y) > 1 ) {
			size.x = 100.0f;
			size.y = 100.0f;
			// // ("\nbigger");
		} else if (abs(velocity.y) > 1) {
			size.x = 50.0f;
			size.y = 50.0f;
			// // ("\nsmaller");
		}
	}

  if (IsKeyDown(KEY_ESCAPE)) WindowShouldClose();

	if (goLeft && velocity.x > -maxVelocity.x) velocity.x -= 1.5f;
	if (goRight && velocity.x < maxVelocity.x) velocity.x += 1.5f;
  
  if (*jumping) {
    if (velocity.y < -maxVelocity.y) {
      *jumping = false;
      jumpAcceleration = initialJumpAcceleration;         
      jumpVelocity = initialJumpVelocity;
    } else {
      if (abs(velocity.y) < maxJumpVelocity && position.y > 0) velocity.y -= jumpVelocity;
    }
  } 
}

void Player::Move(Map * map) {
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
	
	map->mapShouldMoveX = false;
	map->mapShouldMoveY = false;

	if (  // hits mapBox's right wall
				velocity.x > 1.0f && 
				position.x + size.x + velocity.x > map->box.right + map->box.deltaRight && 
				map->position.x + map->size.x > map->screenWidth
	) {
				// ("\nmapBox RIGHT");	
				map->mapShouldMoveX = true;
				position.x = (map->box.right + map->box.deltaRight) - size.x;
				map->position.x -= velocity.x * GetFrameTime() * num; 
	} 
	if (  // hits mapBox's left wall
				velocity.x < 1.0f &&
				position.x + velocity.x < map->box.left - map->box.deltaLeft &&
				map->position.x < 0
	) {
				// ("\nmapbox LEFT");
				map->mapShouldMoveX = true;
				position.x = map->box.left - map->box.deltaLeft;
				map->position.x -= velocity.x * GetFrameTime() * num;
	} 
	if (  // hits mapBox's ceiling
				velocity.y < 0 &&
				position.y + velocity.y <= map->box.top - map->box.deltaTop &&
				map->position.y < 0		
	) {
				// ("\nmapbox TOP");
				map->mapShouldMoveY = true;
				position.y = map->box.top - map->box.deltaTop;
				map->position.y -= velocity.y * GetFrameTime() * num; 
	}
	if ( // hits mapBox's floor
				velocity.y > gravity &&
				position.y + size.y + velocity.y >= map->box.bottom + map->box.deltaBottom &&
				map->position.y + map->size.y > map->screenHeight
	) {	
				// ("\nmapbox BOTTOM");
				map->mapShouldMoveY = true;
				position.y = (map->box.bottom + map->box.deltaBottom) - size.y;
				map->position.y -= velocity.y * GetFrameTime() * num;
	}

	if (map->mapShouldMoveX == false) {
			position.x += velocity.x * GetFrameTime() * num;
	}
	if (map->mapShouldMoveY == false) {
			position.y += velocity.y * GetFrameTime() * num;
	}
	if (map->position.y + map->size.y <= map->screenHeight) {
		map->box.deltaBottom = 0;
	}
	if (map->position.y  >= 0) {
		map->box.deltaTop = 0;
	}
	if (map->position.x + map->size.x <= map->screenWidth) {
		map->box.deltaRight = 0;
	}
  if (map->position.x  >= 0) {
		map->box.deltaLeft = 0;
	}

	
	// // ("\n\nx : %f", position.x);
	// // ("\ny : %f", position.y);
	
}

void Player::Show() {
  DrawRectangleV(position, size, MAROON);
};

void Player::CheckIfCollision(Tile* tile, Map * map) {
	if ( // TOP
		velocity.y < 0 &&
		pTop + velocity.y < tile->bottom &&
		pBottom + velocity.y > tile->bottom &&
		pRight > tile->left &&
		pLeft < tile->right	
	) {
		// std::cout << "top collision" << std::endl;
		velocity.y = 0;
		position.y = tile->bottom;
		*jumping = false;
		if (position.y < map->box.top - map->box.deltaTop && 
				map->position.y < 0 
		) {
			float delta = (map->box.top - position.y);
			map->box.deltaTop = delta;
		}
		return;
	}
	if ( // 
		velocity.x > 0 &&
		pRight + velocity.x > tile->left &&
		pLeft + velocity.x < tile->left &&
		pBottom > tile->top &&
		pTop < tile->bottom - maxVelocity.y
	) {
		// std::cout << "right collision" << std::endl;
		velocity.x = 0;	
		position.x = tile->position.x - size.x;
		if (position.x + size.x > map->box.right && 
				map->position.x + map->size.x >	map->screenWidth 
		) {
			float delta = (position.x + size.x) - map->box.right;
			map->box.deltaRight = delta;
		}
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
		if (position.x < map->box.left - map->box.deltaLeft && 
				map->position.x > 0 
		) {
			float delta = (map->box.left - position.x);
			map->box.deltaLeft = delta;
		}
		return;
	}
	
	if (
		velocity.y > 0 &&
		pBottom + velocity.y > tile->top &&
		pTop + velocity.y < tile->top &&
		pRight > tile->left &&
		pLeft < tile->right	
	) {
		// std::cout << "\nbottom collision\n" << std::endl;
		
		velocity.y = 0;	
		position.y = tile->top - size.y;	
		if (position.y + size.y > map->box.bottom + map->box.deltaBottom && 
				map->position.y+map->size.y > map->screenHeight
		) {
			float delta = ((position.y + size.y) - map->box.bottom);
			map->box.deltaBottom = delta;
		}
		return;
	}
	if(position.y + size.y > map->screenHeight - tile->size.y && velocity.y == 0) {
		float delta = (position.y + size.y) - (map->screenHeight -tile->size.y);
		position.y -= delta;
		map->position.y -= delta;
	}
};

 
