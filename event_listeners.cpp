#include "player.h"
#include <ios>
#include <iostream>
#include "raylib.h"
#include <cmath>
#include <cstdio>

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
  
  if (*jumping && hitMapboxTop == false) {
    if (jumpInitialHeight - position.y  >= jumpMaxHeight) {
      *jumping = false;
      jumpAcceleration = initialJumpAcceleration;         
      jumpVelocity = initialJumpVelocity;
    } else {
      if (abs(velocity.y) < maxJumpVelocity && position.y > 0) velocity.y -= jumpVelocity;
    }
	} else if (*jumping && hitMapboxTop == true) {
		if (alreadyJumped + deltaMapYMovement >= jumpMaxHeight) {
			*jumping = false;
			hitMapboxTop = false;
			alreadyJumped = 0;
			deltaMapYMovement = 0;
			jumpAcceleration = initialJumpAcceleration;         
			jumpVelocity = initialJumpVelocity;
			hitMapboxTop = false;
		} else {
      if (abs(velocity.y) < maxJumpVelocity && position.y > 0) velocity.y -= jumpVelocity;
    }
	} 
	if (velocity.y > 0) {
		hitMapboxTop = false;
	}
} 


