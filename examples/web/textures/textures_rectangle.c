/*******************************************************************************************
*
*   raylib [core] example - Texture loading and drawing a part defined by a rectangle (adapted for HTML5 platform)
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

#define MAX_FRAME_SPEED     15
#define MIN_FRAME_SPEED      1

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
const int screenWidth = 800;
const int screenHeight = 450;

// NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
Texture2D scarfy = { 0 };

Vector2 position = { 0 };
Rectangle frameRec = { 0 };

int currentFrame = 0;

int framesCounter = 0;
int framesSpeed = 8;            // Number of spritesheet frames shown by second

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
    InitWindow(screenWidth, screenHeight, "raylib [texture] example - texture rectangle");

    scarfy = LoadTexture("resources/scarfy.png");        // Texture loading
    position = (Vector2){ 350.0f, 280.0f };

    // NOTE: On PLATFORM_WEB, NPOT textures support is limited
    frameRec = (Rectangle){ 0, 0, scarfy.width/6, scarfy.height };

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
    UnloadTexture(scarfy);       // Texture unloading

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
    framesCounter++;

    if (framesCounter >= (60/framesSpeed))
    {
        framesCounter = 0;
        currentFrame++;

        if (currentFrame > 5) currentFrame = 0;

        frameRec.x = currentFrame*scarfy.width/6;
    }

    if (IsKeyPressed(KEY_RIGHT)) framesSpeed++;
    else if (IsKeyPressed(KEY_LEFT)) framesSpeed--;

    if (framesSpeed > MAX_FRAME_SPEED) framesSpeed = MAX_FRAME_SPEED;
    else if (framesSpeed < MIN_FRAME_SPEED) framesSpeed = MIN_FRAME_SPEED;
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTexture(scarfy, 15, 40, WHITE);
        DrawRectangleLines(15, 40, scarfy.width, scarfy.height, LIME);
        DrawRectangleLines(15 + frameRec.x, 40 + frameRec.y, frameRec.width, frameRec.height, RED);

        DrawText("FRAME SPEED: ", 165, 210, 10, DARKGRAY);
        DrawText(TextFormat("%02i FPS", framesSpeed), 575, 210, 10, DARKGRAY);
        DrawText("PRESS RIGHT/LEFT KEYS to CHANGE SPEED!", 290, 240, 10, DARKGRAY);

        for (int i = 0; i < MAX_FRAME_SPEED; i++)
        {
            if (i < framesSpeed) DrawRectangle(250 + 21*i, 205, 20, 20, RED);
            DrawRectangleLines(250 + 21*i, 205, 20, 20, MAROON);
        }

        DrawTextureRec(scarfy, frameRec, position, WHITE);  // Draw part of the texture

        DrawText("(c) Scarfy sprite by Eiden Marsal", screenWidth - 200, screenHeight - 20, 10, GRAY);

    EndDrawing();
    //----------------------------------------------------------------------------------
}