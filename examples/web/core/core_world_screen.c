/*******************************************************************************************
*
*   raylib [core] example - World to screen (adapted for HTML5 platform)
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

// Define the camera to look into our 3d world
Camera camera = { 0 };

Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

Vector2 cubeScreenPosition = { 0 };

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
    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera free");

    // Define the camera to look into our 3d world
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetCameraMode(camera, CAMERA_FREE);         // Set a free camera mode

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
//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void)
{
    // Update
    //----------------------------------------------------------------------------------
    UpdateCamera(&camera);          // Update internal camera and our camera

    // Calculate cube screen space position (with a little offset to be in top)
    cubeScreenPosition = GetWorldToScreen((Vector3){cubePosition.x, cubePosition.y + 2.5f, cubePosition.z}, camera);
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

            DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
            DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);

            DrawGrid(10, 1.0f);

        EndMode3D();

        DrawText("Enemy: 100 / 100", cubeScreenPosition.x - MeasureText("Enemy: 100 / 100", 20) / 2, cubeScreenPosition.y, 20, BLACK);
        DrawText("Text is always on top of the cube", (screenWidth - MeasureText("Text is always on top of the cube", 20)) / 2, 25, 20, GRAY);

    EndDrawing();
    //----------------------------------------------------------------------------------
}