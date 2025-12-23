#include "assets.h"
#include "ball.h"
#include "game.h"
#include "graphics.h"
#include "level.h"
#include "paddle.h"
#include "raylib.h"


void update()
{
    // TODO
    // exit from the game and close the window.
    if (IsKeyPressed(KEY_DELETE) || IsKeyPressed(KEY_BACKSPACE)) {
        CloseWindow();
        return;
    }

    switch (game_state ) {
    case menu_state:
        if(IsKeyPressed((KEY_ENTER))){
            StopMusicStream(menu_music); // Main music
            game_state=in_game_state;
        }
        break;
    case in_game_state:

        if (IsKeyPressed(KEY_ESCAPE)) {
            game_state = paused_state;
        }
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
            move_paddle(-paddle_speed);
        }
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
            move_paddle(paddle_speed);
        }
        move_ball();
        if (!is_ball_inside_level()) {
            load_level();
            PlaySound(lose_sound);
            game_state=game_over_state;
        } else if (current_level_blocks == 0) {
            PlaySound(win_sound);
            if (current_level_index==level_count-1){
                derive_graphics_metrics();
                init_victory_menu();
                //animation of victory screen
                game_state=victory_state;
            }  else {
                load_level(1); //back to 1st level
            }
        }
        break;

        // WHAT WAS ADDED.
    
    case paused_state:
        if(IsKeyPressed((KEY_ESCAPE))){
            game_state=in_game_state;
        }
        break;
    case victory_state:
        draw_victory_menu();
        if(IsKeyPressed(KEY_ENTER)){
            current_level_index=0; // go to level 1.
            load_level(0);
            game_state = in_game_state;
        }
        break;

    case game_over_state: // when game over
        if(IsKeyPressed((KEY_ENTER))){ // try again
            load_level();
            game_state=in_game_state;
        }
        if (IsKeyPressed(KEY_ESCAPE)) {   // back to menu
            current_level_index=0;
            load_level(0);
            game_state = menu_state;

            PlayMusicStream(menu_music);     // Back to main, back to music.
            menu_music.looping = true;
            SetMusicVolume(menu_music, 0.4f);



        }

        break;

    default:;

    
    }
}

void draw()
{
    // TODO
    game_frame++;

    switch (game_state){
    case menu_state:
        draw_menu();
        break;

    case in_game_state:

        draw_level();

        draw_paddle();
        draw_ball();
        draw_ui();
        break;
    case paused_state:
        draw_pause_menu();
        break;
    case victory_state:
        draw_victory_menu();
        break;
        // new game state.
    case game_over_state:
        draw_gameover_menu();
        break;

    default:;

    }
}

int main()
{
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(1280, 720, "Breakout");
    SetTargetFPS(60);

    load_fonts();
    load_textures();
    load_level();

    load_sounds();
    load_music();

    // New Music to Main Screen
    PlayMusicStream(menu_music);
    menu_music.looping = true;
    SetMusicVolume(menu_music, 0.4f);


    while (!WindowShouldClose()) {
        UpdateMusicStream(menu_music);
        BeginDrawing();
        SetExitKey(KEY_NULL); // used for pause_state
        draw();
        update();

        EndDrawing();
    }
    CloseWindow();

    unload_sounds();
    unload_level();
    unload_textures();
    unload_fonts();
    unload_music();

    return 0;
}
