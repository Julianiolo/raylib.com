/*******************************************************************************************
*
*   raylib [models] example - Models loading
*
*   raylib supports multiple models file formats:
*
*     - OBJ > Text file, must include vertex position-texcoords-normals information,
*             if files references some .mtl materials file, it will be loaded (or try to)
*     - GLTF > Modern text/binary file format, includes lot of information and it could
*              also reference external files, raylib will try loading mesh and materials data
*     - IQM > Binary file format including mesh vertex data but also animation data,
*             raylib can load .iqm animations.  
*
*   This example has been created using raylib 2.6 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014-2019 Ramon Santamaria (@raysan5)
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

static Camera camera = { 0 };
    
static Model model = { 0 };
static Texture2D texture = { 0 };
static Vector3 position = { 0.0f, 0.0f, 0.0f };
 
static BoundingBox bounds = { 0 };

static bool selected = false;

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
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [models] example - models loading");

    // Define the camera to look into our 3d world
    camera.position = (Vector3){ 50.0f, 50.0f, 50.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 10.0f, 0.0f };     // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type

    model = LoadModel("resources/models/castle.obj");             // Load model
    texture = LoadTexture("resources/models/castle_diffuse.png"); // Load model texture
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;       // Set map diffuse texture

    bounds = MeshBoundingBox(model.meshes[0]);          // Set model bounds

    // NOTE: bounds are calculated from the original size of the model,
    // if model is scaled on drawing, bounds must be also scaled

    SetCameraMode(camera, CAMERA_FREE);     // Set a free camera mode

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
    UnloadTexture(texture);     // Unload texture
    UnloadModel(model);         // Unload model

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//----------------------------------------------------------------------------------
// Module Functions Definitions
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void)
{
    // Update
    //----------------------------------------------------------------------------------
    UpdateCamera(&camera);
    
    // Load new models/textures on drag&drop
    if (IsFileDropped())
    {
        int count = 0;
        char **droppedFiles = GetDroppedFiles(&count);

        if (count == 1) // Only support one file dropped
        {
            if (IsFileExtension(droppedFiles[0], ".obj") ||
                IsFileExtension(droppedFiles[0], ".gltf") ||
                IsFileExtension(droppedFiles[0], ".iqm"))       // Model file formats supported
            {
                UnloadModel(model);                     // Unload previous model
                model = LoadModel(droppedFiles[0]);     // Load new model
                model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture; // Set current map diffuse texture

                bounds = MeshBoundingBox(model.meshes[0]);
                
                // TODO: Move camera position from target enough distance to visualize model properly
            }
            else if (IsFileExtension(droppedFiles[0], ".png"))  // Texture file formats supported
            {
                // Unload current model texture and load new one
                UnloadTexture(texture);
                texture = LoadTexture(droppedFiles[0]);
                model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
            }
        }

        ClearDroppedFiles();    // Clear internal buffers
    }

    // Select model on mouse click
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        // Check collision between ray and box
        if (CheckCollisionRayBox(GetMouseRay(GetMousePosition(), camera), bounds)) selected = !selected;
        else selected = false;
    }
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

            DrawModel(model, position, 1.0f, WHITE);        // Draw 3d model with texture

            DrawGrid(20, 10.0f);         // Draw a grid

            if (selected) DrawBoundingBox(bounds, GREEN);   // Draw selection box

        EndMode3D();
        
        DrawText("Drag & drop model to load mesh/texture.", 10, GetScreenHeight() - 20, 10, DARKGRAY);
        if (selected) DrawText("MODEL SELECTED", GetScreenWidth() - 110, 10, 10, GREEN);

        DrawText("(c) Castle 3D model by Alberto Cano", screenWidth - 200, screenHeight - 20, 10, GRAY);

        DrawFPS(10, 10);

    EndDrawing();
    //----------------------------------------------------------------------------------
}