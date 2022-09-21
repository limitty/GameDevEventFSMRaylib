//
#include "EnumEntityName.h" // Enum: Miner_Bob, Wife_Elsa
#include "Miner.h"

// #include "Locations.h"
#include "SingletonMessage.h"
#define SMI SingletonMessage::Instance()

#include <string>
#include <vector>

// Only this "main.cpp" code requires "raylib.h"
#include "raylib.h"

using namespace std;

#define RECT_WIDTH 800
#define RECT_HEIGHT 150

void DrawDialogueBox(const char *message, int frames_counter, bool enabled,
                     Texture2D texture);

int main() {
  // create a Miner instance
  Miner miner(Miner_Bob);

  int window_width = 1000; 
  int window_height = 450;

  // SetTraceLogLevel(LOG_NONE);
  // SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(window_width, window_height, "Miner - Finite State Machine");
  int frames_counter = 0;
  int len = 0;

  bool enabled_to_skip = false;

  // vector<string> vec{};
  string str{"( Press Space Key to Continue )"};

  Image image_miner =
      LoadImage("resources/miner.png"); // Load image in CPU memory (RAM)
  ImageResize(&image_miner, 128, 128);  // Resize flipped-cropped image

  // Image converted to texture, GPU memory (RAM -> VRAM)
  Texture2D texture = LoadTextureFromImage(image_miner);
  // Unload image data from CPU memory (RAM)
  UnloadImage(image_miner);

  // FPS=200
  SetTargetFPS(200);

  while (!WindowShouldClose()) {
    frames_counter++;
    // press space key to play each message
    if (IsKeyPressed(KEY_SPACE) && enabled_to_skip) {
      frames_counter = 0;
      enabled_to_skip = false;

      // if message buffer is empty, then allow to Update
      if (SMI->CheckEmpty() == true) {
        miner.Update(); // call Update()
      }
      str = SMI->GetVal(); // get string vector from SingletonMessage buffer
      SMI->DelFirstVal();
      // SMI->ClearVector(); // clear SingletonMessage buffer
    }

    // control message play speed
    len = str.length();
    if (frames_counter >= len * 3.5) {
      enabled_to_skip = true;
    }

    // Draw message box
    BeginDrawing();
    ClearBackground(BLACK);
    DrawDialogueBox(str.c_str(), frames_counter, enabled_to_skip, texture);
    EndDrawing();
    // }
  }
  CloseWindow();
  return 0;
}

void DrawDialogueBox(const char *message, int frames_counter, bool enabled,
                     Texture2D texture) {
  Rectangle box = {(float)(GetScreenWidth() / 2 - RECT_WIDTH / 2),
                   (float)(GetScreenHeight() - (RECT_HEIGHT + 50)), 
                   RECT_WIDTH,
                   RECT_HEIGHT};
  // Draw message box background
  DrawRectangleRec(box, DARKBLUE);
  // Draw message box's frame
  DrawRectangleLinesEx(box, 5, LIGHTGRAY);
  // Draw character's avatar
  DrawTexture(texture, 
              GetScreenWidth() / 6 - texture.width / 2,
              GetScreenHeight() * 0.73 - texture.height / 2, 
              WHITE);
  // Draw message
  DrawText(TextSubtext(message, 0, frames_counter / 3), box.x + 120, box.y + 40,
           20, WHITE);

  // Draw message ending mark
  if (enabled) {
    // Draw rectangle
    // DrawRectangle(box.x + RECT_WIDTH - 48, box.y + 105, 32, 32, WHITE);

    // Draw triangle
    DrawTriangle(
        // triangle vertices
        {box.x + RECT_WIDTH - 60, box.y + 105},
        {box.x + RECT_WIDTH - 60 + 15, box.y + 105 + 30},
        {box.x + RECT_WIDTH - 60 + 30, box.y + 105},
        // triangle color
        WHITE);
  }
}
