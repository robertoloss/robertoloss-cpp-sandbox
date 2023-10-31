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

struct Map {
	Vector2 position;
	Vector2 size;
}; 

float tileSize = 100.0f;

int main(void)
{
    const float screenWidth = gameMap[0].size() * ( tileSize / 2 ); 
    const float screenHeight = gameMap.size() * ( tileSize / 2 ); 
		
		Map map;
		map.size = {
			(float)gameMap[0].size(),
			(float)gameMap.size(),
		};
		map.position = {
			0.0f,
			screenHeight - map.size.y,
		};

    InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");
    // SetTargetFPS(60);               
		SetConfigFlags(FLAG_VSYNC_HINT);
    std::vector<Tile*> collisions;
    
    for (float Y = 0; Y < gameMap.size(); Y++) {
      for (float X = 0; X < gameMap[0].size(); X++) {
        if (gameMap[Y][X] == 1.0f) {
          Vector2 size = {tileSize, tileSize};
          Vector2 gridPosition = {(float)X, (float)Y};
          Tile newTile = {size, gridPosition};
          collisions.push_back(&newTile);
        };
      }
    }
 
    Player player;
    player.position.x = screenWidth/2.0f;
    player.position.y = screenHeight/2.0f;
    
    while (!WindowShouldClose()) {
      player.EventListeners();
      player.Move(); 
      player.CollisionWithScreenBorder(screenWidth, screenHeight);

			for (auto tile: collisions) {
				tile->position = {
					map.position.x + (tile->position.x * tile->size.x),
					map.position.y + (tile->position.y * tile->size.y),
				};
			};
			
		  for (auto tile: collisions) {
				player.CheckIfCollision(tile);
			};

      BeginDrawing();
      ClearBackground(BLACK);
      
      for (auto tile : collisions) {
				DrawRectangleV(tile->position, tile->size, BLUE);
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

