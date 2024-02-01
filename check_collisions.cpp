#include "player.h"
#include "raylib.h"

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


