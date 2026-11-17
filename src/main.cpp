#include <raylib.h>
#include <raymath.h>
#include <algorithm>
#include <vector>

constexpr int scream_width{900}, scream_height{480};
constexpr Color green = {173, 204, 96, 255};
constexpr Color darkGreen = {43, 51, 24, 255};
double lastUpdateTime{0};

class Bullet {
public:
    Vector2 position;
    float speed{12};
    bool active{true};

    Bullet(Vector2 startPosition)
        : position(startPosition) {}

    void Update(){
        position.x += speed;
        if(position.x > scream_width){
            active = false;
        }
    }

    void Draw(){
        if(active){
            DrawRectangle(static_cast<int>(position.x), static_cast<int>(position.y), 16, 6, YELLOW);
        }
    }
};

class Player {
private:
    Texture2D texture;
public:
    int x{scream_width / 2};
    int y{scream_height / 2};
    int speed{6};
    std::vector<Bullet> bullets;

    void Draw(){
        DrawTexture(texture, x, y, WHITE);
    }

    void Update(int pos){
        
    }

    void Shoot(){
        bullets.emplace_back(Vector2{
            static_cast<float>(x + texture.width / 2 + (texture.width / 2)),
            static_cast<float>(y + texture.height / 2)
        });
    }

    void UpdateBullets(){
        for(Bullet &bullet : bullets){
            bullet.Update();
        }

        bullets.erase(
            std::remove_if(bullets.begin(), bullets.end(),
                [](const Bullet &bullet){ return !bullet.active; }),
            bullets.end()
        );
    }

    void DrawBullets(){
        for(Bullet &bullet : bullets){
            bullet.Draw();
        }
    }

    void Collision(){

    if(y + texture.height >= GetScreenHeight()){
		y = GetScreenHeight() - texture.height;
	}
	if(y <= 0){
		y = 0;
	}
	if (x + texture.width >= GetScreenWidth()){
		x = GetScreenWidth() - texture.width;
	}
	if (x <= 0){
		x = 0;
	}
    }

    void Reset(){
        
    }

    Player(){
        Image image = LoadImage("Graphics/Player.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }

    ~Player() { UnloadTexture(texture); }
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
        player.DrawBullets();
    }

    void Update(){

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