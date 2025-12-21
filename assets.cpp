#include "assets.h"

#include "raylib.h"


Music menu_music; // Adding music;


void load_fonts()
{
    // new Font added.
    menu_font = LoadFontEx("data/fonts/orbitron.ttf", 256, nullptr, 0);
}

void unload_fonts()
{
    UnloadFont(menu_font);
}

void load_textures()
{
    wall_texture = LoadTexture("data/images/wall.png");
    void_texture = LoadTexture("data/images/void.png");
    block_texture = LoadTexture("data/images/block.png");
    paddle_texture = LoadTexture("data/images/paddle.png");
    coin_texture= LoadTexture("data/images/coin.png");
    obstacle_texture= LoadTexture("data/images/obstacle.png");
    ball_sprite = load_sprite("data/images/ball/ball", ".png", 8, true, 10);
}

void unload_textures()
{
    UnloadTexture(wall_texture);
    UnloadTexture(void_texture);
    UnloadTexture(block_texture);
    UnloadTexture(paddle_texture);
    UnloadTexture(obstacle_texture);
    UnloadTexture(coin_texture);
    unload_sprite(ball_sprite);
}
void load_music() // music for the main menu

{
    menu_music= LoadMusicStream("data/music/perfect-beauty-191271.mp3");
    menu_music.looping=true;
    SetMusicVolume(menu_music, 0.4f);

}
void unload_music(){
    UnloadMusicStream(menu_music);
}

void load_sounds()
{
    InitAudioDevice();
    win_sound = LoadSound("data/sounds/win.wav");
    lose_sound = LoadSound("data/sounds/lose.wav");
    coin_sound = LoadSound("data/sounds/coin.wav");
    apple_sound= LoadSound("data/sounds/apple.wav");
    paddle_sound= LoadSound("data/sounds/paddle.wav");

}

void unload_sounds()
{
    UnloadSound(win_sound);
    UnloadSound(lose_sound);
    UnloadSound(coin_sound);
    UnloadSound(apple_sound);
    UnloadSound(paddle_sound);
    CloseAudioDevice();
}

