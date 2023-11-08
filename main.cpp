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
  { 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 0 , 0 , 0 , 1 , },
  { 1 , 1 , 1 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 1 , 1 , 1 , },
  { 1 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , },
  { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , },
};

 

void SetMap (Map, std::vector<Tile*>);

float tileSize = 100.0f;

int main(void)
{
    const float screenWidth = gameMap[0].size() * ( tileSize / 2 ); 
    const float screenHeight = gameMap.size() * ( tileSize / 2 ); 
		
		Map map;

		map.screenHeight = screenHeight;
		map.screenWidth = screenWidth;
		map.box = {
			screenWidth / 4,
			(screenWidth / 4) * 3,
			screenHeight / 4,
			(screenHeight / 4) * 3
		};

		map.size = {
			(float)gameMap[0].size() * tileSize,
			(float)gameMap.size() * tileSize,
		};
		map.position = {
			0.0f,
			screenHeight - map.size.y,
		};

    InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");
    // SetTargetFPS(60);               
		SetConfigFlags(FLAG_VSYNC_HINT);
    std::vector<Tile*> collisions;
    
    for (int Y = 0; Y < gameMap.size(); Y++) {
      for (int X = 0; X < gameMap[0].size(); X++) {
        if (gameMap[Y][X] == 1) {
					// printf("\nIt's a one");
          Vector2 size = {tileSize, tileSize};
          Vector2 gridPosition = {(float)X, (float)Y};
          Tile * newTile = new Tile {size, gridPosition};
          collisions.push_back(newTile);
        } else {
					// printf("\nIt's a zero!");
				}
      }
    }
 
    Player player;
    player.position.x = screenWidth/2.0f;
    player.position.y = screenHeight/2.0f;
    
		SetMap(map, collisions);
		
    while (!WindowShouldClose()) {
      player.EventListeners();
      player.Move(&map); 
      player.CollisionWithScreenBorder(screenWidth, screenHeight);
		 	
			SetMap(map, collisions);
			
		  for (auto tile: collisions) {
				player.CheckIfCollision(tile,&map);
			};

      BeginDrawing();
      ClearBackground(BLACK);
      
      for (auto tile : collisions) {
				DrawRectangleV(tile->position, tile->size, BLUE);
      } 

      player.Show();
			
			std::string velX = "velocity.x : ";
			std::string velY = "velocity.y : ";
			std::string jumping = "jumping : ";
			std::string jumpVelocity = "jump velocity : ";
			std::string jumpMaxVel = "jump MAX velocity : ";
			std::string jumpMaxHeight = "jump MAX height : ";
			std::string jumpAcc = "jump accelaration : ";

		  std::string strVelX = velX + std::to_string(player.velocity.x);
			std::string strVelY = velY + std::to_string(player.velocity.y);
			std::string strJump = jumping + (*player.jumping ? "true" : "false");
			std::string strJumpVel = jumpVelocity + std::to_string(player.jumpVelocity); 
			std::string strJumpMaxVel = jumpVelocity + std::to_string(player.maxJumpVelocity); 
			std::string strJumpMaxHeight = jumpVelocity + std::to_string(player.jumpMaxHeight); 
			std::string strJumpAcc = jumpAcc + std::to_string(player.jumpAcceleration); 

			std::string strGetFrame = std::to_string(GetFrameTime());

			DrawText(strVelX.c_str(), 10,  0, 16, YELLOW);
			DrawText(strVelY.c_str(), 10, 20, 16, YELLOW);
			DrawText(strJump.c_str(), 10, 40, 16, YELLOW);
			DrawText(strJumpVel.c_str(), 10, 60, 16, YELLOW);	
			DrawText(strJumpMaxVel.c_str(), 10, 80, 16, YELLOW);
			DrawText(strJumpMaxHeight.c_str(), 10, 100, 16, YELLOW);
			DrawText(strJumpAcc.c_str(), 10, 120, 16, YELLOW);
			// DrawText(strGetFrame.c_str(), 10,  60, 16, WHITE);
			// DrawFPS(10, 40);
			
			// Vector2 boxPosition = {map.box.left, map.box.top};
		  // Vector2 boxSize = {screenWidth/2, screenHeight/2};
			// Color boxColor = { 253, 249, 0, 80 };
			// DrawRectangleV(boxPosition, boxSize, boxColor );
      EndDrawing();
    }
  
    CloseWindow();    
    return 0;
}

void SetMap(Map map, std::vector<Tile*> collisions) {
	for (int i = 0; i < collisions.size(); i++) {
		Tile * tile = collisions[i];
		tile->position = {
			map.position.x + (tile->gridPosition.x * tile->size.x),
			map.position.y + (tile->gridPosition.y * tile->size.y),
		};
		tile->top = tile->position.y;
		tile->bottom = tile->position.y + tile->size.y;
		tile->left = tile->position.x;
		tile->right = tile->position.x + tile->size.x;
		//printf("\n\n%d", i);
		//printf("\ntile grid: %f %f", tile->gridPosition.x, tile->gridPosition.y);
		//printf("\ntile pos: %f %f", tile->position.x, tile->position.y);
	}

}
