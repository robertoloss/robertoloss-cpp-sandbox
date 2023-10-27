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
  { 1 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , },
};

 

int main(void)
{
    const int screenWidth = gameMap[0].size() * 50;
    const int screenHeight = gameMap.size() * 50;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");
    SetTargetFPS(60);               

    std::vector<Tile> collisions;
    
    for (int Y = 0; Y < gameMap.size(); Y++) {
      for (int X = 0; X < gameMap[0].size(); X++) {
        if (gameMap[Y][X] == 1) {
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
			
			DrawText(strVelX.c_str(), 10,0,16, WHITE);
			DrawText(strVelY.c_str(), 10,20, 16, WHITE);
			DrawFPS(10, 40);
      EndDrawing();
    }
  
    CloseWindow();    
    return 0;
}

