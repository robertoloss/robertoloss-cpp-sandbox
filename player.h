#pragma once
#include "raylib.h"
  
class Player  {
public:
  void CollisionWithScreenBorder (int screenWidth, int screenHeight);
  void Move(); 
  void EventListeners();
    
  Vector2 position; 
  Vector2 size = { (float)50, (float)50 };
  Vector2 velocity = { (float)0, (float)0 };
  Vector2 maxVelocity = {(float)7, (float)20}; 
  bool jumpingTmp = false;
  bool jumpingEnabledTmp = true;
  bool * jumping = &jumpingTmp;
  bool * jumpingEnabled = &jumpingEnabledTmp;
  float maxJumpVelocity = 10.0f;
  float jumpInitialHeight = 0;
  float jumpMaxHeight = size.y*2.5;
  float jumpVelocity = 2.5f;
  float initialJumpVelocity = jumpVelocity;
  float jumpAcceleration = 0.5f;
  float initialJumpAcceleration = jumpAcceleration;
  float jumpAccIncrease = 0.2f;
  int xPressedCount = 0; 

  void Show();
  };
