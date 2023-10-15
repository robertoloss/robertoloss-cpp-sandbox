#include "raylib.h"
#include <charconv>
#include <cmath>
#include <cstring>
#include <ios>
#include <iostream>
#include <string>
#include "player.h"

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

const char * ToString(bool val) {
  return val ? "true" : "false";
} 

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");

    Player player;
    Vector2 position = { (float)screenWidth/2, (float)screenHeight/2 };
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

    SetTargetFPS(60);               

    while (!WindowShouldClose())   
    {
      // Update
      if (IsKeyDown(KEY_RIGHT) && abs(velocity.x) < maxVelocity.x) velocity.x += 1.5f;
      if (IsKeyDown(KEY_LEFT) && abs(velocity.x) < maxVelocity.x) velocity.x -= 1.5f;
      if (IsKeyPressed(KEY_X)) {
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
      
      if (*jumping == true) {
        if (jumpInitialHeight - position.y  >= jumpMaxHeight) {
          *jumping = false;
          jumpAcceleration = initialJumpAcceleration;         
          jumpVelocity = initialJumpVelocity;
        } else {
          if (abs(velocity.y) < maxJumpVelocity && position.y > 0) velocity.y -= jumpVelocity;
        }
      }
      
      if (velocity.x > 0) velocity.x -= 0.5f;
      if (velocity.x < 0) velocity.x += 0.5f;
    
      if (velocity.y < maxVelocity.y) velocity.y++;

      position.x += velocity.x;
      position.y += velocity.y;

      std::string countString = std::to_string(xPressedCount);
      std::string jString = (std::string)"jumping : " + ToString(*jumping);

      player.CollisionWithScreenBorder(&position, &velocity, screenWidth, 
                                screenHeight, size, jumping, jumpingEnabled);
      DrawText(jString.c_str(), 10, 10, 16, WHITE);
      DrawText(countString.c_str(), 10, 70, 16, WHITE);
      BeginDrawing();
      ClearBackground(BLACK);
      DrawRectangleV(position, size, MAROON);
      EndDrawing();
    }

    CloseWindow();    
    return 0;
}


void CollisionWithScreenBorder(Vector2* position, Vector2* velocity, int screenWidth, 
                               int screenHeight, Vector2 size, bool* jumping, bool* jumpingEnabled) {
  if (position->x <= 0 || position->x+size.x >= screenWidth) {
    velocity->x = 0;
    position->x <= 0 ? position->x = 0 : position->x = (screenWidth-size.x);
  } 
  if (position->y < 0 || position->y+size.y > screenHeight) {
    velocity->y = 0;
    *jumping = false;
    if (position->y < 0) {
      position->y = 0;
    } else {
      position->y = (screenHeight-size.y);
    }
 } 
}
