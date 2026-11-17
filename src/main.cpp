#include <raylib.h>
#include <deque>
#include <raymath.h>

constexpr int scream_width{950}, scream_height{550};
constexpr Color green = {173, 204, 96, 255};
constexpr Color darkGreen = {43, 51, 24, 255};
double lastUpdateTime{0};

class Player {
private:
    
public:

    float x{scream_width / 2};
    float y{scream_height / 2};
    int speed{3};

    void Draw(){
        DrawRectangle(x, y, 30, 30, WHITE);
    }

    void Update(int pos){
        
    }

    void Collision(){
        if(y + 30 >= GetScreenHeight()){
		y = GetScreenHeight() - 30;
	}
	if(y <= 0){
		y = 0;
	}
	if (x + 30 >= GetScreenWidth()){
		x = GetScreenWidth() - 30;
	}
	if (x <= 0){
		x = 0;
	}
    }

    void Reset(){
        
    }
};

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
    }

    void Update(){
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
        ClearBackground(BLACK);
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