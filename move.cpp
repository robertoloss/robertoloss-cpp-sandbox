#include "player.h"
#include <ios>
#include <iostream>
#include "raylib.h"
#include <cmath>
#include <cstdio>


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
		    if (hitMapboxTop == false) {
					alreadyJumped = jumpInitialHeight - position.y;
					deltaMapYMovement = 0;
					map->initialPositionJump = map->position.y; 
					hitMapboxTop = true;
				} 
				deltaMapYMovement = (map->position.y - map->initialPositionJump);
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
	if (position.y < map->box.bottom - size.y || position.y > map->box.bottom) {
		map->box.deltaBottom = 0;
	}
	if (position.y > map->box.top || position.y < map->box.top - size.y) {
		map->box.deltaTop = 0;
	}
	if (position.x < map->box.right - size.x || position.x > map->box.right) {
		map->box.deltaRight = 0;
	}
  if (position.x > map->box.left || position.x < map->box.left - size.x) {
		map->box.deltaLeft = 0;
	}

	
	
}
