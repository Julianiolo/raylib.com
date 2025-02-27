/*******************************************************************************************
*
*   raylib [core] example - Input multitouch
*
*   This example has been created using raylib 2.1 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Example contributed by Berni (@Berni8k) and reviewed by Ramon Santamaria (@raysan5)
*
*   Copyright (c) 2019 Berni (@Berni8k) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#define MAX_TOUCH_POINTS 10

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
const int screenWidth = 800;
const int screenHeight = 450;

// NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

Vector2 ballPosition = { -100.0f, -100.0f };
Color ballColor = BEIGE;

int touchCounter = 0;
Vector2 touchPosition = { 0 };

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
    InitWindow(screenWidth, screenHeight, "raylib [core] example - input multitouch");

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
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

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void)
{
    // Update
    //----------------------------------------------------------------------------------
    ballPosition = GetMousePosition();

    ballColor = BEIGE;

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) ballColor = MAROON;
    if (IsMouseButtonDown(MOUSE_MIDDLE_BUTTON)) ballColor = LIME;
    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) ballColor = DARKBLUE;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) touchCounter = 10;
    if (IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON)) touchCounter = 10;
    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) touchCounter = 10;

    if (touchCounter > 0) touchCounter--;
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);

        // Multitouch
        for (int i = 0; i < MAX_TOUCH_POINTS; ++i)
        {
            touchPosition = GetTouchPosition(i);                    // Get the touch point

            if ((touchPosition.x >= 0) && (touchPosition.y >= 0))   // Make sure point is not (-1,-1) as this means there is no touch for it
            {
                // Draw circle and touch index number
                DrawCircleV(touchPosition, 34, ORANGE);
                DrawText(TextFormat("%d", i), touchPosition.x - 10, touchPosition.y - 70, 40, BLACK);
            }
        }

        // Draw the normal mouse location
        DrawCircleV(ballPosition, 30 + (touchCounter*3), ballColor);

        DrawText("move ball with mouse and click mouse button to change color", 10, 10, 20, DARKGRAY);
        DrawText("touch the screen at multiple locations to get multiple balls", 10, 30, 20, DARKGRAY);

    EndDrawing();
    //----------------------------------------------------------------------------------
}
