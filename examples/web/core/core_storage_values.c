/*******************************************************************************************
*
*   raylib [core] example - Storage save/load values (adapted for HTML5 platform)
*
*   This example has been created using raylib 1.4 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

// NOTE: Storage positions must start with 0, directly related to file memory layout
typedef enum {
    STORAGE_POSITION_SCORE      = 0,
    STORAGE_POSITION_HISCORE    = 1
} StorageData;

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
const int screenWidth = 800;
const int screenHeight = 450;

int score = 0;
int hiscore = 0;

int framesCounter = 0;

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void);     // Update and Draw one frame

//----------------------------------------------------------------------------------
// Program Main Entry Point
//----------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "raylib [core] example - storage save/load values");

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void UpdateDrawFrame(void)
{
    // Update
    //----------------------------------------------------------------------------------
    if (IsKeyPressed(KEY_R))
    {
        score = GetRandomValue(1000, 2000);
        hiscore = GetRandomValue(2000, 4000);
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        SaveStorageValue(STORAGE_POSITION_SCORE, score);
        SaveStorageValue(STORAGE_POSITION_HISCORE, hiscore);
    }
    else if (IsKeyPressed(KEY_SPACE))
    {
        // NOTE: If requested position could not be found, value 0 is returned
        score = LoadStorageValue(STORAGE_POSITION_SCORE);
        hiscore = LoadStorageValue(STORAGE_POSITION_HISCORE);
    }

    framesCounter++;
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText(TextFormat("SCORE: %i", score), 280, 130, 40, MAROON);
        DrawText(TextFormat("HI-SCORE: %i", hiscore), 210, 200, 50, BLACK);

        DrawText(TextFormat("frames: %i", framesCounter), 10, 10, 20, LIME);

        DrawText("Press R to generate random numbers", 220, 40, 20, LIGHTGRAY);
        DrawText("Press ENTER to SAVE values", 250, 310, 20, LIGHTGRAY);
        DrawText("Press SPACE to LOAD values", 252, 350, 20, LIGHTGRAY);

    EndDrawing();
    //----------------------------------------------------------------------------------
}