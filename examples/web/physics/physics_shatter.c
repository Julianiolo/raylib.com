/*******************************************************************************************
*
*   Physac - Body shatter
*
*   NOTE 1: Physac requires multi-threading, when InitPhysics() a second thread is created to manage physics calculations.
*   NOTE 2: Physac requires static C library linkage to avoid dependency on MinGW DLL (-static -lpthread)
*
*   Use the following line to compile:
*
*   gcc -o $(NAME_PART).exe $(FILE_NAME) -s $(RAYLIB_DIR)\raylib\raylib_icon -static -lraylib -lpthread
*   -lglfw3 -lopengl32 -lgdi32 -lopenal32 -lwinmm -std=c99 -Wl,--subsystem,windows -Wl,-allow-multiple-definition
*
*   Copyright (c) 2017 Victor Fisac
*
********************************************************************************************/

#include "raylib.h"

#define PHYSAC_IMPLEMENTATION
#include "physac.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
const int screenWidth = 800;
const int screenHeight = 450;

// Physac logo drawing position
int logoX = 0;
int logoY = 15;

PhysicsBody body = { 0 };

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
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "Physac [raylib] - Body shatter");

    // Physac logo drawing position
    logoX = screenWidth - MeasureText("Physac", 30) - 10;

    // Initialize physics and default physics bodies
    InitPhysics();
    SetPhysicsGravity(0, 0);

    // Create random polygon physics body to shatter
    body = CreatePhysicsBodyPolygon((Vector2){ screenWidth/2, screenHeight/2 }, GetRandomValue(80, 200), GetRandomValue(3, 8), 10);

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
    ClosePhysics();       // Uninitialize physics

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
    PhysicsStep();

    if (IsKeyPressed('R'))    // Reset physics input
    {
        ResetPhysics();

        // Create random polygon physics body to shatter
        body = CreatePhysicsBodyPolygon((Vector2){ screenWidth/2, screenHeight/2 }, GetRandomValue(80, 200), GetRandomValue(3, 8), 10);
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))    // Physics shatter input
    {
        // Note: some values need to be stored in variables due to asynchronous changes during main thread
        int count = GetPhysicsBodiesCount();
        for (int i = count - 1; i >= 0; i--)
        {
            PhysicsBody currentBody = GetPhysicsBody(i);
            if (currentBody != NULL) PhysicsShatter(currentBody, GetMousePosition(), 10/currentBody->inverseMass);
        }
    }
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(BLACK);

        // Draw created physics bodies
        int bodiesCount = GetPhysicsBodiesCount();
        for (int i = 0; i < bodiesCount; i++)
        {
            PhysicsBody currentBody = GetPhysicsBody(i);

            int vertexCount = GetPhysicsShapeVerticesCount(i);
            for (int j = 0; j < vertexCount; j++)
            {
                // Get physics bodies shape vertices to draw lines
                // Note: GetPhysicsShapeVertex() already calculates rotation transformations
                Vector2 vertexA = GetPhysicsShapeVertex(currentBody, j);

                int jj = (((j + 1) < vertexCount) ? (j + 1) : 0);   // Get next vertex or first to close the shape
                Vector2 vertexB = GetPhysicsShapeVertex(currentBody, jj);

                DrawLineV(vertexA, vertexB, GREEN);     // Draw a line between two vertex positions
            }
        }

        DrawText("Left mouse button in polygon area to shatter body\nPress 'R' to reset example", 10, 10, 10, WHITE);

        DrawText("Physac", logoX, logoY, 30, WHITE);
        DrawText("Powered by", logoX + 50, logoY - 7, 10, WHITE);

    EndDrawing();
    //----------------------------------------------------------------------------------
}

