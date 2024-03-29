#pragma once
#include "raylib.h"
#include <vector>
#include <string>

struct mapBox {
	float left;
	float right;
	float top;
	float bottom;
	float deltaLeft = 0.0;
	float deltaRight = 0.0;
	float deltaBottom = 0.0;
	float deltaTop = 0.0;
};

struct Map {
	Vector2 position;
	Vector2 size;
	mapBox box;
	float screenWidth;
	float screenHeight;
	float initialPositionJump;
	bool mapShouldMoveX;
	bool mapShouldMoveY;
};

struct Tile {
  Vector2 size;
	Vector2 gridPosition;
  Vector2 position;
	float top = Tile::position.y;
	float bottom = Tile::position.y + Tile::size.y;
	float left = Tile::position.x;
	float right = Tile::position.x + Tile::size.x;
};

enum direction {top, bottom, left, right};

struct CollisionTile {
	Tile tile;
	direction collisionSide;	
};

enum MovementAxis {xAxis, yAxis};

class Player  {
public:
  void CollisionWithScreenBorder (int screenWidth, int screenHeight);
  void Move(Map *); 
  void EventListeners();
	void CheckIfCollision(Tile*, Map*);
	CollisionTile CollisionDirection(Tile*);
	void CollisionManager(CollisionTile);
	float overlap(direction, Tile*);
	float axisOverlap(MovementAxis, Tile*);
    
  Vector2 position; 
	Vector2 oldPosition;
	float pLeft = Player::position.x;
	float pRight;
	float pTop;
	float pBottom;
	float gravity = 0.04f;
	Vector2 size = { (float)50, (float)50 };
	Vector2 velocity = { (float)0, (float)0 };
	Vector2 maxVelocity = { (float)4.5, (float)5.0 }; 
	MovementAxis axis;
  bool jumpingTmp = false;
  bool jumpingEnabledTmp = true;
  bool * jumping = &jumpingTmp;
  bool * jumpingEnabled = &jumpingEnabledTmp;
	bool goLeft;
	bool goRight;
	bool hitMapboxTop = false;
  float maxJumpVelocity =  7.0f;
  float jumpInitialHeight = 0;
  float jumpMaxHeight = size.y*2.0;
  float jumpVelocity = 0.5f;
	float jumpVelocityX = 0;
	float incrementJumpVelX = 0.2f;
  float initialJumpVelocity = jumpVelocity;
  float jumpAcceleration = 1.5;
  float initialJumpAcceleration = jumpAcceleration;
  float jumpAccIncrease = 0.2f;
	float alreadyJumped = 0;
	float deltaMapYMovement = 0;
  int xPressedCount = 0; 

  void Show();
  };
