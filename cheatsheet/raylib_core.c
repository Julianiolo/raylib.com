
    // Window-related functions
    void InitWindow(int width, int height, const char *title);              // Initialize window and OpenGL context
    bool WindowShouldClose(void);                                           // Check if KEY_ESCAPE pressed or Close icon pressed
    void CloseWindow(void);                                                 // Close window and unload OpenGL context
    bool IsWindowReady(void);                                               // Check if window has been initialized successfully
    bool IsWindowFullscreen(void);                                          // Check if window is currently fullscreen
    bool IsWindowHidden(void);                                              // Check if window is currently hidden (only PLATFORM_DESKTOP)
    bool IsWindowMinimized(void);                                           // Check if window is currently minimized (only PLATFORM_DESKTOP)
    bool IsWindowMaximized(void);                                           // Check if window is currently maximized (only PLATFORM_DESKTOP)
    bool IsWindowFocused(void);                                             // Check if window is currently focused (only PLATFORM_DESKTOP)
    bool IsWindowResized(void);                                             // Check if window has been resized last frame
    bool IsWindowState(unsigned int flag);                                  // Check if one specific window flag is enabled
    void SetWindowState(unsigned int flags);                                // Set window configuration state using flags
    void ClearWindowState(unsigned int flags);                              // Clear window configuration state flags
    void ToggleFullscreen(void);                                            // Toggle window state: fullscreen/windowed (only PLATFORM_DESKTOP)
    void MaximizeWindow(void);                                              // Set window state: maximized, if resizable (only PLATFORM_DESKTOP)
    void MinimizeWindow(void);                                              // Set window state: minimized, if resizable (only PLATFORM_DESKTOP)
    void RestoreWindow(void);                                               // Set window state: not minimized/maximized (only PLATFORM_DESKTOP)
    void SetWindowIcon(Image image);                                        // Set icon for window (only PLATFORM_DESKTOP)
    void SetWindowTitle(const char *title);                                 // Set title for window (only PLATFORM_DESKTOP)
    void SetWindowPosition(int x, int y);                                   // Set window position on screen (only PLATFORM_DESKTOP)
    void SetWindowMonitor(int monitor);                                     // Set monitor for the current window (fullscreen mode)
    void SetWindowMinSize(int width, int height);                           // Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
    void SetWindowSize(int width, int height);                              // Set window dimensions
    void *GetWindowHandle(void);                                            // Get native window handle
    int GetScreenWidth(void);                                               // Get current screen width
    int GetScreenHeight(void);                                              // Get current screen height
    int GetMonitorCount(void);                                              // Get number of connected monitors
    int GetCurrentMonitor(void);                                            // Get current connected monitor
    Vector2 GetMonitorPosition(int monitor);                                // Get specified monitor position
    int GetMonitorWidth(int monitor);                                       // Get specified monitor width (max available by monitor)
    int GetMonitorHeight(int monitor);                                      // Get specified monitor height (max available by monitor)
    int GetMonitorPhysicalWidth(int monitor);                               // Get specified monitor physical width in millimetres
    int GetMonitorPhysicalHeight(int monitor);                              // Get specified monitor physical height in millimetres
    int GetMonitorRefreshRate(int monitor);                                 // Get specified monitor refresh rate
    Vector2 GetWindowPosition(void);                                        // Get window position XY on monitor
    Vector2 GetWindowScaleDPI(void);                                        // Get window scale DPI factor
    const char *GetMonitorName(int monitor);                                // Get the human-readable, UTF-8 encoded name of the primary monitor
    void SetClipboardText(const char *text);                                // Set clipboard text content
    const char *GetClipboardText(void);                                     // Get clipboard text content

    // Cursor-related functions
    void ShowCursor(void);                                                  // Shows cursor
    void HideCursor(void);                                                  // Hides cursor
    bool IsCursorHidden(void);                                              // Check if cursor is not visible
    void EnableCursor(void);                                                // Enables cursor (unlock cursor)
    void DisableCursor(void);                                               // Disables cursor (lock cursor)
    bool IsCursorOnScreen(void);                                            // Check if cursor is on the current screen.

    // Drawing-related functions
    void ClearBackground(Color color);                                      // Set background color (framebuffer clear color)
    void BeginDrawing(void);                                                // Setup canvas (framebuffer) to start drawing
    void EndDrawing(void);                                                  // End canvas drawing and swap buffers (double buffering)
    void BeginMode2D(Camera2D camera);                                      // Initialize 2D mode with custom camera (2D)
    void EndMode2D(void);                                                   // Ends 2D mode with custom camera
    void BeginMode3D(Camera3D camera);                                      // Initializes 3D mode with custom camera (3D)
    void EndMode3D(void);                                                   // Ends 3D mode and returns to default 2D orthographic mode
    void BeginTextureMode(RenderTexture2D target);                          // Initializes render texture for drawing
    void EndTextureMode(void);                                              // Ends drawing to render texture
    void BeginShaderMode(Shader shader);                                    // Begin custom shader drawing
    void EndShaderMode(void);                                               // End custom shader drawing (use default shader)
    void BeginBlendMode(int mode);                                          // Begin blending mode (alpha, additive, multiplied)
    void EndBlendMode(void);                                                // End blending mode (reset to default: alpha blending)
    void BeginScissorMode(int x, int y, int width, int height);             // Begin scissor mode (define screen area for following drawing)
    void EndScissorMode(void);                                              // End scissor mode
    void BeginVrStereoMode(VrStereoConfig config);                          // Begin stereo rendering
    void EndVrStereoMode(void);                                             // End stereo rendering

    // VR stereo config functions for VR simulator
    VrStereoConfig LoadVrStereoConfig(VrDeviceInfo device);                 // Load VR stereo config for VR simulator device parameters
    void UnloadVrStereoConfig(VrStereoConfig config);                       // Unload VR stereo config

    // Shader management functions
    // NOTE: Shader functionality is not available on OpenGL 1.1
    Shader LoadShader(const char *vsFileName, const char *fsFileName);      // Load shader from files and bind default locations
    Shader LoadShaderFromMemory(const char *vsCode, const char *fsCode);    // Load shader from code strings and bind default locations
    int GetShaderLocation(Shader shader, const char *uniformName);          // Get shader uniform location
    int GetShaderLocationAttrib(Shader shader, const char *attribName);     // Get shader attribute location
    void SetShaderValue(Shader shader, int locIndex, const void *value, int uniformType);               // Set shader uniform value
    void SetShaderValueV(Shader shader, int locIndex, const void *value, int uniformType, int count);   // Set shader uniform value vector
    void SetShaderValueMatrix(Shader shader, int locIndex, Matrix mat);     // Set shader uniform value (matrix 4x4)
    void SetShaderValueTexture(Shader shader, int locIndex, Texture2D texture); // Set shader uniform value for texture (sampler2d)
    void UnloadShader(Shader shader);                                       // Unload shader from GPU memory (VRAM)

    // Screen-space-related functions
    Ray GetMouseRay(Vector2 mousePosition, Camera camera);                  // Returns a ray trace from mouse position
    Matrix GetCameraMatrix(Camera camera);                                  // Returns camera transform matrix (view matrix)
    Matrix GetCameraMatrix2D(Camera2D camera);                              // Returns camera 2d transform matrix
    Vector2 GetWorldToScreen(Vector3 position, Camera camera);              // Returns the screen space position for a 3d world space position
    Vector2 GetWorldToScreenEx(Vector3 position, Camera camera, int width, int height); // Returns size position for a 3d world space position
    Vector2 GetWorldToScreen2D(Vector2 position, Camera2D camera);          // Returns the screen space position for a 2d camera world space position
    Vector2 GetScreenToWorld2D(Vector2 position, Camera2D camera);          // Returns the world space position for a 2d camera screen space position

    // Timing-related functions
    void SetTargetFPS(int fps);                                             // Set target FPS (maximum)
    int GetFPS(void);                                                       // Returns current FPS
    float GetFrameTime(void);                                               // Returns time in seconds for last frame drawn (delta time)
    double GetTime(void);                                                   // Returns elapsed time in seconds since InitWindow()
            
    // Misc. functions          
    int GetRandomValue(int min, int max);                                   // Returns a random value between min and max (both included)
    void TakeScreenshot(const char *fileName);                              // Takes a screenshot of current screen (filename extension defines format)
    void SetConfigFlags(unsigned int flags);                                // Setup init configuration flags (view FLAGS)
            
    void TraceLog(int logLevel, const char *text, ...);                     // Show trace log messages (LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR)
    void SetTraceLogLevel(int logLevel);                                    // Set the current threshold (minimum) log level
    void *MemAlloc(int size);                                               // Internal memory allocator
    void *MemRealloc(void *ptr, int size);                                  // Internal memory reallocator
    void MemFree(void *ptr);                                                // Internal memory free

    // Set custom callbacks
    // WARNING: Callbacks setup is intended for advance users
    void SetTraceLogCallback(TraceLogCallback callback);                    // Set custom trace log
    void SetLoadFileDataCallback(LoadFileDataCallback callback);            // Set custom file binary data loader
    void SetSaveFileDataCallback(SaveFileDataCallback callback);            // Set custom file binary data saver
    void SetLoadFileTextCallback(LoadFileTextCallback callback);            // Set custom file text data loader
    void SetSaveFileTextCallback(SaveFileTextCallback callback);            // Set custom file text data saver

    // Files management functions
    unsigned char *LoadFileData(const char *fileName, unsigned int *bytesRead);     // Load file data as byte array (read)
    void UnloadFileData(unsigned char *data);                               // Unload file data allocated by LoadFileData()
    bool SaveFileData(const char *fileName, void *data, unsigned int bytesToWrite); // Save data to file from byte array (write), returns true on success
    char *LoadFileText(const char *fileName);                               // Load text data from file (read), returns a '\0' terminated string
    void UnloadFileText(unsigned char *text);                               // Unload file text data allocated by LoadFileText()
    bool SaveFileText(const char *fileName, char *text);                    // Save text data to file (write), string must be '\0' terminated, returns true on success
    bool FileExists(const char *fileName);                                  // Check if file exists
    bool DirectoryExists(const char *dirPath);                              // Check if a directory path exists
    bool IsFileExtension(const char *fileName, const char *ext);            // Check file extension (including point: .png, .wav)
    const char *GetFileExtension(const char *fileName);                     // Get pointer to extension for a filename string (includes dot: ".png")
    const char *GetFileName(const char *filePath);                          // Get pointer to filename for a path string
    const char *GetFileNameWithoutExt(const char *filePath);                // Get filename string without extension (uses static string)
    const char *GetDirectoryPath(const char *filePath);                     // Get full path for a given fileName with path (uses static string)
    const char *GetPrevDirectoryPath(const char *dirPath);                  // Get previous directory path for a given path (uses static string)
    const char *GetWorkingDirectory(void);                                  // Get current working directory (uses static string)
    char **GetDirectoryFiles(const char *dirPath, int *count);              // Get filenames in a directory path (memory should be freed)
    void ClearDirectoryFiles(void);                                         // Clear directory files paths buffers (free memory)
    bool ChangeDirectory(const char *dir);                                  // Change working directory, return true on success
    bool IsFileDropped(void);                                               // Check if a file has been dropped into window
    char **GetDroppedFiles(int *count);                                     // Get dropped files names (memory should be freed)
    void ClearDroppedFiles(void);                                           // Clear dropped files paths buffer (free memory)
    long GetFileModTime(const char *fileName);                              // Get file modification time (last write time)

    unsigned char *CompressData(unsigned char *data, int dataLength, int *compDataLength);        // Compress data (DEFLATE algorithm)
    unsigned char *DecompressData(unsigned char *compData, int compDataLength, int *dataLength);  // Decompress data (DEFLATE algorithm)

    // Persistent storage management
    bool SaveStorageValue(unsigned int position, int value);                // Save integer value to storage file (to defined position), returns true on success
    int LoadStorageValue(unsigned int position);                            // Load integer value from storage file (from defined position)

    void OpenURL(const char *url);                                          // Open URL with default system browser (if available)

    // Input-related functions: keyboard
    bool IsKeyPressed(int key);                                             // Detect if a key has been pressed once
    bool IsKeyDown(int key);                                                // Detect if a key is being pressed
    bool IsKeyReleased(int key);                                            // Detect if a key has been released once
    bool IsKeyUp(int key);                                                  // Detect if a key is NOT being pressed
    void SetExitKey(int key);                                               // Set a custom key to exit program (default is ESC)
    int GetKeyPressed(void);                                                // Get key pressed (keycode), call it multiple times for keys queued
    int GetCharPressed(void);                                               // Get char pressed (unicode), call it multiple times for chars queued

    // Input-related functions: gamepads
    bool IsGamepadAvailable(int gamepad);                                   // Detect if a gamepad is available
    bool IsGamepadName(int gamepad, const char *name);                      // Check gamepad name (if available)
    const char *GetGamepadName(int gamepad);                                // Return gamepad internal name id
    bool IsGamepadButtonPressed(int gamepad, int button);                   // Detect if a gamepad button has been pressed once
    bool IsGamepadButtonDown(int gamepad, int button);                      // Detect if a gamepad button is being pressed
    bool IsGamepadButtonReleased(int gamepad, int button);                  // Detect if a gamepad button has been released once
    bool IsGamepadButtonUp(int gamepad, int button);                        // Detect if a gamepad button is NOT being pressed
    int GetGamepadButtonPressed(void);                                      // Get the last gamepad button pressed
    int GetGamepadAxisCount(int gamepad);                                   // Return gamepad axis count for a gamepad
    float GetGamepadAxisMovement(int gamepad, int axis);                    // Return axis movement value for a gamepad axis
    int SetGamepadMappings(const char *mappings);                           // Set internal gamepad mappings (SDL_GameControllerDB)

    // Input-related functions: mouse
    bool IsMouseButtonPressed(int button);                                  // Detect if a mouse button has been pressed once
    bool IsMouseButtonDown(int button);                                     // Detect if a mouse button is being pressed
    bool IsMouseButtonReleased(int button);                                 // Detect if a mouse button has been released once
    bool IsMouseButtonUp(int button);                                       // Detect if a mouse button is NOT being pressed
    int GetMouseX(void);                                                    // Returns mouse position X
    int GetMouseY(void);                                                    // Returns mouse position Y
    Vector2 GetMousePosition(void);                                         // Returns mouse position XY
    void SetMousePosition(int x, int y);                                    // Set mouse position XY
    void SetMouseOffset(int offsetX, int offsetY);                          // Set mouse offset
    void SetMouseScale(float scaleX, float scaleY);                         // Set mouse scaling
    float GetMouseWheelMove(void);                                          // Returns mouse wheel movement Y
    void SetMouseCursor(int cursor);                                        // Set mouse cursor

    // Input-related functions: touch
    int GetTouchX(void);                                                    // Returns touch position X for touch point 0 (relative to screen size)
    int GetTouchY(void);                                                    // Returns touch position Y for touch point 0 (relative to screen size)
    Vector2 GetTouchPosition(int index);                                    // Returns touch position XY for a touch point index (relative to screen size)

    // Gestures and Touch Handling Functions (Module: gestures)
    void SetGesturesEnabled(unsigned int flags);                            // Enable a set of gestures using flags
    bool IsGestureDetected(int gesture);                                    // Check if a gesture have been detected
    int GetGestureDetected(void);                                           // Get latest detected gesture
    int GetTouchPointsCount(void);                                          // Get touch points count
    float GetGestureHoldDuration(void);                                     // Get gesture hold time in milliseconds
    Vector2 GetGestureDragVector(void);                                     // Get gesture drag vector
    float GetGestureDragAngle(void);                                        // Get gesture drag angle
    Vector2 GetGesturePinchVector(void);                                    // Get gesture pinch delta
    float GetGesturePinchAngle(void);                                       // Get gesture pinch angle

    // Camera System Functions (Module: camera)
    void SetCameraMode(Camera camera, int mode);                            // Set camera mode (multiple camera modes available)
    void UpdateCamera(Camera *camera);                                      // Update camera position for selected mode

    void SetCameraPanControl(int keyPan);                                   // Set camera pan key to combine with mouse movement (free camera)
    void SetCameraAltControl(int keyAlt);                                   // Set camera alt key to combine with mouse movement (free camera)
    void SetCameraSmoothZoomControl(int keySmoothZoom);                     // Set camera smooth zoom key to combine with mouse (free camera)
    void SetCameraMoveControls(int frontKey, int backKey, 
                               int rightKey, int leftKey, 
                               int upKey, int downKey);                     // Set camera move controls (1st person and 3rd person cameras)

