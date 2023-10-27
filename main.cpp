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
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
};

 

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 600;

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
				if (player.CheckIfCollision(tilePtr)) {
					std::cout << "collision" << std::endl;
					player.CollisionManager(player.CollisionDirection(tilePtr));
			 }
			};

      BeginDrawing();
      ClearBackground(BLACK);
      
      for (auto tile : collisions) {
        DrawRectangleV(tile.position, tile.size, BLUE);
      } 

      player.Show();
      EndDrawing();
    }
  
    CloseWindow();    
    return 0;
}

