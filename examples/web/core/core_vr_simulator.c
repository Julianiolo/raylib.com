/*******************************************************************************************
*
*   raylib [core] example - VR Simulator (Oculus Rift CV1 parameters)
*
*   This example has been created using raylib 1.7 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

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

// NOTE: screenWidth/screenHeight should match VR device aspect ratio

Camera camera = { 0 };
Shader distortion = { 0 };

Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

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
    InitWindow(screenWidth, screenHeight, "raylib [core] example - oculus rift");

    // Init VR simulator (Oculus Rift CV1 parameters)
    InitVrSimulator();

    VrDeviceInfo hmd = { 0 };               // VR device parameters (head-mounted-device)

    // Oculus Rift CV1 parameters for simulator
    hmd.hResolution = 2160;                 // HMD horizontal resolution in pixels
    hmd.vResolution = 1200;                 // HMD vertical resolution in pixels
    hmd.hScreenSize = 0.133793f;            // HMD horizontal size in meters
    hmd.vScreenSize = 0.0669f;              // HMD vertical size in meters
    hmd.vScreenCenter = 0.04678f;           // HMD screen center in meters
    hmd.eyeToScreenDistance = 0.041f;       // HMD distance between eye and display in meters
    hmd.lensSeparationDistance = 0.07f;     // HMD lens separation distance in meters
    hmd.interpupillaryDistance = 0.07f;     // HMD IPD (distance between pupils) in meters

    // NOTE: CV1 uses a Fresnel-hybrid-asymmetric lenses with specific distortion compute shaders.
    // Following parameters are an approximation to distortion stereo rendering but results differ from actual device.
    hmd.lensDistortionValues[0] = 1.0f;     // HMD lens distortion constant parameter 0
    hmd.lensDistortionValues[1] = 0.22f;    // HMD lens distortion constant parameter 1
    hmd.lensDistortionValues[2] = 0.24f;    // HMD lens distortion constant parameter 2
    hmd.lensDistortionValues[3] = 0.0f;     // HMD lens distortion constant parameter 3
    hmd.chromaAbCorrection[0] = 0.996f;     // HMD chromatic aberration correction parameter 0
    hmd.chromaAbCorrection[1] = -0.004f;    // HMD chromatic aberration correction parameter 1
    hmd.chromaAbCorrection[2] = 1.014f;     // HMD chromatic aberration correction parameter 2
    hmd.chromaAbCorrection[3] = 0.0f;       // HMD chromatic aberration correction parameter 3

    // Distortion shader (uses device lens distortion and chroma)
    distortion = LoadShader(0, TextFormat("resources/distortion%i.fs", GLSL_VERSION));

    SetVrConfiguration(hmd, distortion);    // Set Vr device parameters for stereo rendering
    // Define the camera to look into our 3d world
    camera.position = (Vector3){ 5.0f, 2.0f, 5.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 60.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                   // Camera type

    SetCameraMode(camera, CAMERA_FIRST_PERSON);         // Set first person camera mode

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
    UnloadShader(distortion);   // Unload distortion shader

    CloseVrSimulator();         // Close VR simulator

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
    UpdateCamera(&camera);          // Update camera (simulator mode)

    if (IsKeyPressed(KEY_SPACE)) ToggleVrMode();    // Toggle VR mode

    // Lock mouse cursor if mouse click on canvas
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) DisableCursor();
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginVrDrawing();

            BeginMode3D(camera);

                DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
                DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);

                DrawGrid(40, 1.0f);

            EndMode3D();

        EndVrDrawing();

        DrawFPS(10, 10);

    EndDrawing();
    //----------------------------------------------------------------------------------
}