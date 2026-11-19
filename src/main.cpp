#include <raylib.h>
#include <raymath.h>
#include "Bullet.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include "Enemy.hpp"

constexpr int scream_width{900}, scream_height{480};
constexpr Color green = {173, 204, 96, 255};
constexpr Color darkGreen = {43, 51, 24, 255};
double lastUpdateTime{0};

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
        DrawText("Score:", scream_height - 140 , 16, 32, darkGreen);
        DrawText(TextFormat("%i", game.score), scream_height - 10 , 16, 32, darkGreen);
        // Objs
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}