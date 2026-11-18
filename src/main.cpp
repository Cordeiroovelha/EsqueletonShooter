#include <raylib.h>
#include <raymath.h>
#include <algorithm>
#include <vector>
#include "Bullet.hpp"
#include "Player.hpp"

constexpr int scream_width{900}, scream_height{480};
constexpr Color green = {173, 204, 96, 255};
constexpr Color darkGreen = {43, 51, 24, 255};
double lastUpdateTime{0};

class Enemy {
private:
    // Texture2D texture;
public:

    void Draw(){
        
    }

    // Vector2 GenerateRandomPos(std::deque<Vector2> snakeBody){
        
    // }

    Enemy() {
        
    }

    // ~Enemy() { UnloadTexture(texture); }

};

class Game {
private:
    
public:
    Player player;

    bool running = true;
    int score = 0;
    Sound eatSound;
    Sound wallSound;

    void Draw(){
        player.Draw();
        player.DrawBullets();
    }

    void Update(){

        player.Update();

        if(IsKeyPressed(KEY_Z)){
            player.Shoot();
        }

        player.UpdateBullets();

        if (IsKeyDown(KEY_UP)){
            player.y -= player.speed;
            player.Collision();
            running = true;
        }
        if (IsKeyDown(KEY_DOWN)){
            player.y += player.speed;
            player.Collision();
            running = true;
        }   
        if (IsKeyDown(KEY_LEFT)){
            player.x -= player.speed;
            player.Collision();
            running = true;
        }
        if (IsKeyDown(KEY_RIGHT)){
            player.x += player.speed;
            player.Collision();
            running = true;
        }
    }

    void CheckCollisionsWithFood(){
        
    }

    void CheckCollisionsWithWall(){
        
    }

    void CheckCollisionsWithBody(){
        
    }

    void GameOver(){
        
    }

    Game() {
        
    }

    ~Game()
    {
        // UnloadSound(eatSound);
        // UnloadSound(wallSound);
        // CloseAudioDevice();
    }
};

int main() {
    
    // inicialização da tela com as medidas, o nome do programa e o fps
    InitWindow(scream_width, scream_height, "Esquelleton Shooter");
    SetTargetFPS(60);

    Game game;

    // Game Loop
    while (!WindowShouldClose()) {
        // Updating Positions
        if(game.running)
            game.Update();

        
        
        // Drawing
        BeginDrawing();
        ClearBackground(GRAY);
        // UI
        DrawText("Score:", scream_height - 60 , 16, 32, darkGreen);
        DrawText(TextFormat("%i", game.score), scream_height - 90 , 16, 32, darkGreen);
        // Objs
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}