
    // Image loading functions
    // NOTE: This functions do not require GPU access
    Image LoadImage(const char *fileName);                                                             // Load image from file into CPU memory (RAM)
    Image LoadImageRaw(const char *fileName, int width, int height, int format, int headerSize);       // Load image from RAW file data
    Image LoadImageAnim(const char *fileName, int *frames);                                            // Load image sequence from file (frames appended to image.data)
    Image LoadImageFromMemory(const char *fileType, const unsigned char *fileData, int dataSize);      // Load image from memory buffer
    void UnloadImage(Image image);                                                                     // Unload image from CPU memory (RAM)
    bool ExportImage(Image image, const char *fileName);                                               // Export image data to file, returns true on success
    bool ExportImageAsCode(Image image, const char *fileName);                                         // Export image as code file defining an array of bytes, returns true on success

    // Image generation functions
    Image GenImageColor(int width, int height, Color color);                                           // Generate image: plain color
    Image GenImageGradientV(int width, int height, Color top, Color bottom);                           // Generate image: vertical gradient
    Image GenImageGradientH(int width, int height, Color left, Color right);                           // Generate image: horizontal gradient
    Image GenImageGradientRadial(int width, int height, float density, Color inner, Color outer);      // Generate image: radial gradient
    Image GenImageChecked(int width, int height, int checksX, int checksY, Color col1, Color col2);    // Generate image: checked
    Image GenImageWhiteNoise(int width, int height, float factor);                                     // Generate image: white noise
    Image GenImagePerlinNoise(int width, int height, int offsetX, int offsetY, float scale);           // Generate image: perlin noise
    Image GenImageCellular(int width, int height, int tileSize);                                       // Generate image: cellular algorithm. Bigger tileSize means bigger cells

    // Image manipulation functions
    Image ImageCopy(Image image);                                                                      // Create an image duplicate (useful for transformations)
    Image ImageFromImage(Image image, Rectangle rec);                                                  // Create an image from another image piece
    Image ImageText(const char *text, int fontSize, Color color);                                      // Create an image from text (default font)
    Image ImageTextEx(Font font, const char *text, float fontSize, float spacing, Color tint);         // Create an image from text (custom sprite font)
    void ImageFormat(Image *image, int newFormat);                                                     // Convert image data to desired format
    void ImageToPOT(Image *image, Color fill);                                                         // Convert image to POT (power-of-two)
    void ImageCrop(Image *image, Rectangle crop);                                                      // Crop an image to a defined rectangle
    void ImageAlphaCrop(Image *image, float threshold);                                                // Crop image depending on alpha value
    void ImageAlphaClear(Image *image, Color color, float threshold);                                  // Clear alpha channel to desired color
    void ImageAlphaMask(Image *image, Image alphaMask);                                                // Apply alpha mask to image
    void ImageAlphaPremultiply(Image *image);                                                          // Premultiply alpha channel
    void ImageResize(Image *image, int newWidth, int newHeight);                                       // Resize image (Bicubic scaling algorithm)
    void ImageResizeNN(Image *image, int newWidth,int newHeight);                                      // Resize image (Nearest-Neighbor scaling algorithm)
    void ImageResizeCanvas(Image *image, int newWidth, int newHeight, int offsetX, int offsetY, Color fill);  // Resize canvas and fill with color
    void ImageMipmaps(Image *image);                                                                   // Generate all mipmap levels for a provided image
    void ImageDither(Image *image, int rBpp, int gBpp, int bBpp, int aBpp);                            // Dither image data to 16bpp or lower (Floyd-Steinberg dithering)
    void ImageFlipVertical(Image *image);                                                              // Flip image vertically
    void ImageFlipHorizontal(Image *image);                                                            // Flip image horizontally
    void ImageRotateCW(Image *image);                                                                  // Rotate image clockwise 90deg
    void ImageRotateCCW(Image *image);                                                                 // Rotate image counter-clockwise 90deg
    void ImageColorTint(Image *image, Color color);                                                    // Modify image color: tint
    void ImageColorInvert(Image *image);                                                               // Modify image color: invert
    void ImageColorGrayscale(Image *image);                                                            // Modify image color: grayscale
    void ImageColorContrast(Image *image, float contrast);                                             // Modify image color: contrast (-100 to 100)
    void ImageColorBrightness(Image *image, int brightness);                                           // Modify image color: brightness (-255 to 255)
    void ImageColorReplace(Image *image, Color color, Color replace);                                  // Modify image color: replace color
    Color *LoadImageColors(Image image);                                                               // Load color data from image as a Color array (RGBA - 32bit)
    Color *LoadImagePalette(Image image, int maxPaletteSize, int *colorsCount);                        // Load colors palette from image as a Color array (RGBA - 32bit)
    void UnloadImageColors(Color *colors);                                                             // Unload color data loaded with LoadImageColors()
    void UnloadImagePalette(Color *colors);                                                            // Unload colors palette loaded with LoadImagePalette()
    Rectangle GetImageAlphaBorder(Image image, float threshold);                                       // Get image alpha border rectangle

    // Image drawing functions
    // NOTE: Image software-rendering functions (CPU)
    void ImageClearBackground(Image *dst, Color color);                                                // Clear image background with given color
    void ImageDrawPixel(Image *dst, int posX, int posY, Color color);                                  // Draw pixel within an image
    void ImageDrawPixelV(Image *dst, Vector2 position, Color color);                                   // Draw pixel within an image (Vector version)
    void ImageDrawLine(Image *dst, int startPosX, int startPosY, int endPosX, int endPosY, Color color); // Draw line within an image
    void ImageDrawLineV(Image *dst, Vector2 start, Vector2 end, Color color);                          // Draw line within an image (Vector version)
    void ImageDrawCircle(Image *dst, int centerX, int centerY, int radius, Color color);               // Draw circle within an image
    void ImageDrawCircleV(Image *dst, Vector2 center, int radius, Color color);                        // Draw circle within an image (Vector version)
    void ImageDrawRectangle(Image *dst, int posX, int posY, int width, int height, Color color);       // Draw rectangle within an image
    void ImageDrawRectangleV(Image *dst, Vector2 position, Vector2 size, Color color);                 // Draw rectangle within an image (Vector version)
    void ImageDrawRectangleRec(Image *dst, Rectangle rec, Color color);                                // Draw rectangle within an image
    void ImageDrawRectangleLines(Image *dst, Rectangle rec, int thick, Color color);                   // Draw rectangle lines within an image
    void ImageDraw(Image *dst, Image src, Rectangle srcRec, Rectangle dstRec, Color tint);             // Draw a source image within a destination image (tint applied to source)
    void ImageDrawText(Image *dst, const char *text, int posX, int posY, int fontSize, Color color);   // Draw text (using default font) within an image (destination)
    void ImageDrawTextEx(Image *dst, Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint); // Draw text (custom sprite font) within an image (destination)

    // Texture loading functions
    // NOTE: These functions require GPU access
    Texture2D LoadTexture(const char *fileName);                                                       // Load texture from file into GPU memory (VRAM)
    Texture2D LoadTextureFromImage(Image image);                                                       // Load texture from image data
    TextureCubemap LoadTextureCubemap(Image image, int layout);                                        // Load cubemap from image, multiple image cubemap layouts supported
    RenderTexture2D LoadRenderTexture(int width, int height);                                          // Load texture for rendering (framebuffer)
    void UnloadTexture(Texture2D texture);                                                             // Unload texture from GPU memory (VRAM)
    void UnloadRenderTexture(RenderTexture2D target);                                                  // Unload render texture from GPU memory (VRAM)
    void UpdateTexture(Texture2D texture, const void *pixels);                                         // Update GPU texture with new data
    void UpdateTextureRec(Texture2D texture, Rectangle rec, const void *pixels);                       // Update GPU texture rectangle with new data
    Image GetTextureData(Texture2D texture);                                                           // Get pixel data from GPU texture and return an Image
    Image GetScreenData(void);                                                                         // Get pixel data from screen buffer and return an Image (screenshot)

    // Texture configuration functions
    void GenTextureMipmaps(Texture2D *texture);                                                        // Generate GPU mipmaps for a texture
    void SetTextureFilter(Texture2D texture, int filter);                                              // Set texture scaling filter mode
    void SetTextureWrap(Texture2D texture, int wrap);                                                  // Set texture wrapping mode

    // Texture drawing functions
    void DrawTexture(Texture2D texture, int posX, int posY, Color tint);                               // Draw a Texture2D
    void DrawTextureV(Texture2D texture, Vector2 position, Color tint);                                // Draw a Texture2D with position defined as Vector2
    void DrawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint);  // Draw a Texture2D with extended parameters
    void DrawTextureRec(Texture2D texture, Rectangle source, Vector2 position, Color tint);            // Draw a part of a texture defined by a rectangle
    void DrawTextureQuad(Texture2D texture, Vector2 tiling, Vector2 offset, Rectangle quad, Color tint);  // Draw texture quad with tiling and offset parameters
    void DrawTextureTiled(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, float scale, Color tint);      // Draw part of a texture (defined by a rectangle) with rotation and scale tiled into dest.
    void DrawTexturePro(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint);           // Draw a part of a texture defined by a rectangle with 'pro' parameters
    void DrawTextureNPatch(Texture2D texture, NPatchInfo nPatchInfo, Rectangle dest, Vector2 origin, float rotation, Color tint);   // Draws a texture (or part of it) that stretches or shrinks nicely
    void DrawTexturePoly(Texture2D texture, Vector2 center, Vector2 *points, Vector2 *texcoords, int pointsCount, Color tint);      // Draw a textured polygon

    // Color/pixel related functions
    Color Fade(Color color, float alpha);                                                              // Returns color with alpha applied, alpha goes from 0.0f to 1.0f
    int ColorToInt(Color color);                                                                       // Returns hexadecimal value for a Color
    Vector4 ColorNormalize(Color color);                                                               // Returns Color normalized as float [0..1]
    Color ColorFromNormalized(Vector4 normalized);                                                     // Returns Color from normalized values [0..1]
    Vector3 ColorToHSV(Color color);                                                                   // Returns HSV values for a Color
    Color ColorFromHSV(float hue, float saturation, float value);                                      // Returns a Color from HSV values
    Color ColorAlpha(Color color, float alpha);                                                        // Returns color with alpha applied, alpha goes from 0.0f to 1.0f
    Color ColorAlphaBlend(Color dst, Color src, Color tint);                                           // Returns src alpha-blended into dst color with tint
    Color GetColor(int hexValue);                                                                      // Get Color structure from hexadecimal value
    Color GetPixelColor(void *srcPtr, int format);                                                     // Get Color from a source pixel pointer of certain format
    void SetPixelColor(void *dstPtr, Color color, int format);                                         // Set color formatted into destination pixel pointer
    int GetPixelDataSize(int width, int height, int format);                                           // Get pixel data size in bytes for certain format

    