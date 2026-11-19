#include <raylib.h>
#include <raymath.h>
#include <array>
#include "Game.hpp"

constexpr int scream_width{900}, scream_height{480};
constexpr Color green = {173, 204, 96, 255};
constexpr Color darkGreen = {43, 51, 24, 255};
double lastUpdateTime{0};

int main() {
    // inicialização da tela com as medidas, o nome do programa e o fps
    InitWindow(scream_width, scream_height, "Esquelleton Shooter");
    SetTargetFPS(60);

    Font font;
    int spacings = 2;
    std::array<Vector2, 2> positions;
    font = LoadFont("Graphics/alagard.png");
    positions[0] = {scream_height - 140 , 20};
    positions[1] = {scream_height - 10 , 20};

    Texture2D BackGround = LoadTexture("Graphics/BackGround.png");
    float scrollingBackground = 0.0f;
    constexpr float backgroundSpeed = 60.0f;

    Game game;

    // Game Loop
    while (!WindowShouldClose()) {
        if (!game.GameRuning &&
            (GetKeyPressed() != 0 ||
             IsKeyPressed(KEY_UP) ||
             IsKeyPressed(KEY_DOWN) ||
             IsKeyPressed(KEY_LEFT) ||
             IsKeyPressed(KEY_RIGHT) ||
             IsKeyPressed(KEY_Z))) {
            game.Start();
        }

        // Updating Positions
        if (game.GameRuning && game.running) {
            game.Update();
        }
        
        if (game.GameRuning && BackGround.id != 0) {
            scrollingBackground -= backgroundSpeed * GetFrameTime();
            if (scrollingBackground <= -static_cast<float>(BackGround.width)) {
                scrollingBackground += static_cast<float>(BackGround.width);
            }
        }
        
        // Drawing
        BeginDrawing();
        ClearBackground(GetColor(0x052c46ff));
        if (BackGround.id != 0) {
            DrawTextureEx( BackGround, (Vector2){ scrollingBackground, 0.0f }, 0.0f, 1.0f, WHITE );
            DrawTextureEx( BackGround, (Vector2){ static_cast<float>(BackGround.width) + scrollingBackground,
                 0.0f }, 0.0f, 1.0f, WHITE );
        }
        // Objs
        game.Draw();

        // UI
        DrawTextEx(font, "SCORE:", positions[0], 40, spacings, WHITE);
        DrawTextEx(font, TextFormat("%i", game.score), positions[1], 40, spacings, WHITE);

        EndDrawing();
    }

    UnloadTexture(BackGround);
    UnloadFont(font);
    CloseWindow();
    return 0;
}