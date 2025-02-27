/*******************************************************************************************
*
*   raylib [audio] example - Sound loading and playing
*
*   NOTE: This example requires OpenAL Soft library installed
*
*   This example has been created using raylib 1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
const int screenWidth = 800;
const int screenHeight = 450;

Sound fxWav = { 0 };
Sound fxOgg = { 0 };

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
    InitWindow(screenWidth, screenHeight, "raylib [audio] example - sound loading and playing");

    InitAudioDevice();      // Initialize audio device

    fxWav = LoadSound("resources/sound.wav");         // Load WAV audio file
    fxOgg = LoadSound("resources/target.ogg");      // Load OGG audio file

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
    UnloadSound(fxWav);     // Unload sound data
    UnloadSound(fxOgg);     // Unload sound data

    CloseAudioDevice();     // Close audio device
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;

}

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void)
{
    // Update
    //----------------------------------------------------------------------------------
    if (IsKeyPressed(KEY_SPACE)) PlaySound(fxWav);      // Play WAV sound

    if (IsKeyPressed(KEY_ENTER)) PlaySound(fxOgg);      // Play OGG sound
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Press SPACE to PLAY the WAV sound!", 200, 180, 20, LIGHTGRAY);

        DrawText("Press ENTER to PLAY the OGG sound!", 200, 220, 20, LIGHTGRAY);

    EndDrawing();
    //----------------------------------------------------------------------------------
}