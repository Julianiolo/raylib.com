/*******************************************************************************************
*
*   raylib [text] example - Font filters
*
*   After font loading, font texture atlas filter could be configured for a softer
*   display of the font when scaling it to different sizes, that way, it's not required
*   to generate multiple fonts at multiple sizes (as long as the scaling is not very different)
*
*   This example has been created using raylib 1.3.0 (www.raylib.com)
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

const char msg[50] = "Loaded Font";

Font font = { 0 };
float fontSize = 0.0f;
Vector2 fontPosition = { 0 };
Vector2 textSize = { 0 };

int currentFontFilter = 0;      // FILTER_POINT

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
    InitWindow(screenWidth, screenHeight, "raylib [text] example - font filters");

    // NOTE: Textures/Fonts MUST be loaded after Window initialization (OpenGL context is required)

    // TTF Font loading with custom generation parameters
    font = LoadFontEx("resources/KAISG.ttf", 96, 0, 0);

    // Generate mipmap levels to use trilinear filtering
    // NOTE: On 2D drawing it won't be noticeable, it looks like FILTER_BILINEAR
    GenTextureMipmaps(&font.texture);

    fontSize = font.baseSize;

    SetTextureFilter(font.texture, TEXTURE_FILTER_POINT);
    
    fontPosition = (Vector2){ 40, screenHeight/2 - 70 };

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
    UnloadFont(font);           // Font unloading

    ClearDroppedFiles();        // Clear internal buffers

    CloseWindow();              // Close window and OpenGL context
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
    fontSize += GetMouseWheelMove()*4.0f;

    // Choose font texture filter method
    if (IsKeyPressed(KEY_ONE))
    {
        SetTextureFilter(font.texture, TEXTURE_FILTER_POINT);
        currentFontFilter = 0;
    }
    else if (IsKeyPressed(KEY_TWO))
    {
        SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);
        currentFontFilter = 1;
    }
    else if (IsKeyPressed(KEY_THREE))
    {
        // NOTE: Trilinear filter won't be noticed on 2D drawing
        SetTextureFilter(font.texture, TEXTURE_FILTER_TRILINEAR);
        currentFontFilter = 2;
    }

    textSize = MeasureTextEx(font, msg, fontSize, 0);

    if (IsKeyDown(KEY_LEFT)) fontPosition.x -= 10;
    else if (IsKeyDown(KEY_RIGHT)) fontPosition.x += 10;

    // Load a dropped TTF file dynamically (at current fontSize)
    if (IsFileDropped())
    {
        int count = 0;
        char **droppedFiles = GetDroppedFiles(&count);

        // NOTE: We only support first ttf file dropped
        if (IsFileExtension(droppedFiles[0], ".ttf"))
        {
            UnloadFont(font);
            font = LoadFontEx(droppedFiles[0], fontSize, 0, 0);
            ClearDroppedFiles();
        }
    }
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Use mouse wheel to change font size", 20, 20, 10, GRAY);
        DrawText("Use KEY_RIGHT and KEY_LEFT to move text", 20, 40, 10, GRAY);
        DrawText("Use 1, 2, 3 to change texture filter", 20, 60, 10, GRAY);
        DrawText("Drop a new TTF font for dynamic loading", 20, 80, 10, DARKGRAY);

        DrawTextEx(font, msg, fontPosition, fontSize, 0, BLACK);

        // TODO: It seems texSize measurement is not accurate due to chars offsets...
        //DrawRectangleLines(fontPosition.x, fontPosition.y, textSize.x, textSize.y, RED);

        DrawRectangle(0, screenHeight - 80, screenWidth, 80, LIGHTGRAY);
        DrawText(TextFormat("Font size: %02.02f", fontSize), 20, screenHeight - 50, 10, DARKGRAY);
        DrawText(TextFormat("Text size: [%02.02f, %02.02f]", textSize.x, textSize.y), 20, screenHeight - 30, 10, DARKGRAY);
        DrawText("CURRENT TEXTURE FILTER:", 250, 400, 20, GRAY);

        if (currentFontFilter == 0) DrawText("POINT", 570, 400, 20, BLACK);
        else if (currentFontFilter == 1) DrawText("BILINEAR", 570, 400, 20, BLACK);
        else if (currentFontFilter == 2) DrawText("TRILINEAR", 570, 400, 20, BLACK);

    EndDrawing();
    //----------------------------------------------------------------------------------
}