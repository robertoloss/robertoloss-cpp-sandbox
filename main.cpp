#include "raylib.h"
#include <charconv>
#include <cmath>
#include <cstring>
#include <ios>
#include <iostream>
#include <string>
#include "player.h"

// void CollisionWithScreenBorder
// (
//   Vector2* position, 
//   Vector2* velocity, 
//   int screenWidth, 
//   int screenHeight, 
//   Vector2 size,
//   bool jumping,
//   bool jumpingEnabled
// );
// const char * ToString(bool val) {
//   return val ? "true" : "false";
// } 
// 
int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");

//    Vector2 position = { (float)screenWidth/2, (float)screenHeight/2 };
//    Vector2 size = { (float)50, (float)50 };
//    Vector2 velocity = { (float)0, (float)0 };
//    Vector2 maxVelocity = {(float)7, (float)20}; 
//    bool jumping = false;
//    bool jumpingEnabled = true;
//    float maxJumpVelocity = 10.0f;
//    float jumpInitialHeight = 0;
//    float jumpMaxHeight = size.y*2.5;
//    float jumpVelocity = 2.5f;
//    float initialJumpVelocity = jumpVelocity;
//    float jumpAcceleration = 0.5f;
//    float initialJumpAcceleration = jumpAcceleration;
//    float jumpAccIncrease = 0.2f;
//    int xPressedCount = 0; 

    SetTargetFPS(60);               
    Player player;
    player.position.x = screenWidth/2.0f;
    player.position.y = screenHeight/2.0f;
    
    while (!WindowShouldClose())   
    {
      // Update
//      if (IsKeyDown(KEY_RIGHT) && abs(velocity.x) < maxVelocity.x) velocity.x += 1.5f;
//      if (IsKeyDown(KEY_LEFT) && abs(velocity.x) < maxVelocity.x) velocity.x -= 1.5f;
//      if (IsKeuyPressed(KEY_X) && jumpingEnabled == true) {
//        jumping = true;
//        std::cout << "KEY_X pressed" << std::endl;
//        xPressedCount += 1;
//        velocity.y = 0;
//        jumpVelocity = initialJumpVelocity;
//        jumpAcceleration = initialJumpAcceleration;
//        jumpInitialHeight = position.y;
//      }
//      if (IsKeyReleased(KEY_X)) {
//        jumping = false;
//      }
//      if (IsKeyDown(KEY_ESCAPE)) WindowShouldClose();
//      
//      if (jumping) {
//        if (jumpInitialHeight - position.y  >= jumpMaxHeight) {
//          jumping = false;
//          jumpAcceleration = initialJumpAcceleration;         
//          jumpVelocity = initialJumpVelocity;
//        } else {
//          if (abs(velocity.y) < maxJumpVelocity && position.y > 0) velocity.y -= jumpVelocity;
//        }
//      }
      player.Move(); 
      player.CollisionWithScreenBorder(screenWidth, screenHeight);
   
      //DrawText(ToString(jumping), 10, 10, 16, WHITE);
      //DrawText(ToString(jumpingEnabled), 10, 40, 16, WHITE);
      // DrawText(countString.c_str(), 10, 70, 16, WHITE);
      BeginDrawing();
      ClearBackground(BLACK);
      player.Show();
      EndDrawing();
    }

    CloseWindow();    
    return 0;
}


// void CollisionWithScreenBorder(Vector2* position, Vector2* velocity, int screenWidth, 
//                                int screenHeight, Vector2 size, bool jumping, bool jumpingEnabled) {
//   if (position->x <= 0 || position->x+size.x >= screenWidth) {
//     velocity->x = 0;
//     position->x <= 0 ? position->x = 0 : position->x = (screenWidth-size.x);
//   } 
//   if (position->y < 0 || position->y+size.y > screenHeight) {
//     velocity->y = 0;
//     jumping = false;
//     if (position->y < 0) {
//       position->y = 0;
//       jumpingEnabled = false;
//     } else {
//       position->y = (screenHeight-size.y);
//     }
//  } 
// }
