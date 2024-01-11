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

  if (IsKeyPressed(KEY_X)) {
    *jumping = true;
    xPressedCount += 1;
    velocity.y = 0;
    jumpVelocity = initialJumpVelocity;
    jumpAcceleration = initialJumpAcceleration;
    jumpInitialHeight = position.y;
		hitMapboxTop = false;
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

} 


