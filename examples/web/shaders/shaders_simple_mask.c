/*******************************************************************************************
*
*   raylib [shaders] example - Simple shader mask
*
*   This example has been created using raylib 2.5 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Example contributed by Chris Camacho (@codifies) and reviewed by Ramon Santamaria (@raysan5)
*
*   Copyright (c) 2019 Chris Camacho (@codifies) and Ramon Santamaria (@raysan5)
*
********************************************************************************************
*
*   After a model is loaded it has a default material, this material can be
*   modified in place rather than creating one from scratch...
*   While all of the maps have particular names, they can be used for any purpose
*   except for three maps that are applied as cubic maps (see below)
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
const int screenWidth = 800;
const int screenHeight = 450;

static Camera camera = { 0 };

static Mesh torus = { 0 };
static Mesh cube = { 0 };
static Mesh sphere = { 0 };
static Model model1 = { 0 };
static Model model2 = { 0 };
static Model model3 = { 0 };
static Shader shader = { 0 };

static Texture texDiffuse = { 0 };
static Texture texMask = { 0 };

static int shaderFrame = 0;
static int framesCounter = 0;
static Vector3 rotation = { 0 };       // Model rotation angles

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

    InitWindow(screenWidth, screenHeight, "raylib - simple shader mask");

    // Define the camera to look into our 3d world
    camera.position = (Vector3){ 0.0f, 1.0f, 2.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Define our three models to show the shader on
    torus = GenMeshTorus(.3, 1, 16, 32);
    model1 = LoadModelFromMesh(torus);

    cube = GenMeshCube(.8,.8,.8);
    model2 = LoadModelFromMesh(cube);

    // Generate model to be shaded just to see the gaps in the other two
    sphere = GenMeshSphere(1, 16, 16);
    model3 = LoadModelFromMesh(sphere);

    // Load the shader
    shader = LoadShader(0, TextFormat("resources/shaders/glsl%i/mask.fs", GLSL_VERSION));

    // Load and apply the diffuse texture (colour map)
    texDiffuse = LoadTexture("resources/plasma.png");
    model1.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texDiffuse;
    model2.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texDiffuse;

    // Using MATERIAL_MAP_EMISSION as a spare slot to use for 2nd texture
    // NOTE: Don't use MATERIAL_MAP_IRRADIANCE, MATERIAL_MAP_PREFILTER or  MATERIAL_MAP_CUBEMAP
    // as they are bound as cube maps
    texMask = LoadTexture("resources/mask.png");
    model1.materials[0].maps[MATERIAL_MAP_EMISSION].texture = texMask;
    model2.materials[0].maps[MATERIAL_MAP_EMISSION].texture = texMask;
    shader.locs[SHADER_LOC_MAP_EMISSION] = GetShaderLocation(shader, "mask");

    // Frame is incremented each frame to animate the shader
    shaderFrame = GetShaderLocation(shader, "frame");

    // Apply the shader to the two models
    model1.materials[0].shader = shader;
    model2.materials[0].shader = shader;

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
    UnloadModel(model1);
    UnloadModel(model2);
    UnloadModel(model3);
    
    UnloadTexture(texDiffuse);  // Unload default diffuse texture
    UnloadTexture(texMask);     // Unload texture mask
    
    UnloadShader(shader);       // Unload shader

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
    framesCounter++;
    rotation.x += 0.01f;
    rotation.y += 0.005f;
    rotation.z -= 0.0025f;

    // Send frames counter to shader for animation
    SetShaderValue(shader, shaderFrame, &framesCounter, SHADER_UNIFORM_INT);

    // Rotate one of the models
    model1.transform = MatrixRotateXYZ(rotation);

    UpdateCamera(&camera);
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(DARKBLUE);

        BeginMode3D(camera);

            DrawModel(model1, (Vector3){0.5,0,0}, 1, WHITE);
            DrawModelEx(model2, (Vector3){-.5,0,0}, (Vector3){1,1,0}, 50, (Vector3){1,1,1}, WHITE);
            DrawModel(model3,(Vector3){0,0,-1.5}, 1, WHITE);
            DrawGrid(10, 1.0f);        // Draw a grid

        EndMode3D();

        DrawRectangle(16, 698, MeasureText(TextFormat("Frame: %i", framesCounter), 20) + 8, 42, BLUE);
        DrawText(TextFormat("Frame: %i", framesCounter), 20, 700, 20, WHITE);

        DrawFPS(10, 10);

    EndDrawing();
    //----------------------------------------------------------------------------------
}
