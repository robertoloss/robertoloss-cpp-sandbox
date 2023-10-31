#include "raylib.h"
#include <charconv>
#include <cmath>
#include <cstring>
#include <ios>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include "player.h"

std::vector<std::vector<int> > gameMap { // 24 by 12
  { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , },
};

 

int main(void)
{
    const float screenWidth = gameMap[0].size() * 50.0f;
    const float screenHeight = gameMap.size() * 50.0f;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");
    // SetTargetFPS(60);               
		SetConfigFlags(FLAG_VSYNC_HINT);
    std::vector<Tile> collisions;
    
    for (float Y = 0; Y < gameMap.size(); Y++) {
      for (float X = 0; X < gameMap[0].size(); X++) {
        if (gameMap[Y][X] == 1.0f) {
          Vector2 size = {(float)50, (float)50};
          Vector2 position = {(float)X*size.x, (float)Y*size.y};
          Tile newTile = {size, position};
          collisions.push_back(newTile);
        };
      }
    }

		std::vector<Tile> * collisionsPtr = &collisions;
    
    Player player;
    player.position.x = screenWidth/2.0f;
    player.position.y = screenHeight/2.0f;
    
    while (!WindowShouldClose()) {
      player.EventListeners();
      player.Move(); 
      player.CollisionWithScreenBorder(screenWidth, screenHeight);
			
		  for (auto tile: collisions) {
				Tile* tilePtr = &tile;
				player.CheckIfCollision(tilePtr);
			};

      BeginDrawing();
      ClearBackground(BLACK);
      
      for (auto tile : collisions) {
				DrawRectangleV(tile.position, tile.size, BLUE);
      } 
      player.Show();
			
			std::string velX = "velocity.x : ";
			std::string velY = "velocity.i : ";
		  std::string strVelX = velX + std::to_string(player.velocity.x);
			std::string strVelY = velY + std::to_string(player.velocity.y);
			std::string strGetFrame = std::to_string(GetFrameTime());

			DrawText(strVelX.c_str(), 10,  0, 16, WHITE);
			DrawText(strVelY.c_str(), 10, 20, 16, WHITE);
			DrawFPS(10, 40);
			DrawText(strGetFrame.c_str(), 10,  60, 16, WHITE);
      EndDrawing();
    }
  
    CloseWindow();    
    return 0;
}

