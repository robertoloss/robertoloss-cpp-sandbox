#pragma once
#include "raylib.h"

class Player  {
public:
  void CollisionWithScreenBorder
  (
    Vector2* position, 
    Vector2* velocity, 
    int screenWidth, 
    int screenHeight, 
    Vector2 size,
    bool * jumping,
    bool * jumpingEnabled
  );
};
