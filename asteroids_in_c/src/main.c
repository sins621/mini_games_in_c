#include <stdlib.h>
#include <time.h>

#include "raylib.h"

#include "asteroid.h"

void UpdateDrawFrame(void);
void AddAsteroid(Vector2 position, Vector2 velocity, AsteroidSize size);

#define screenWidth 600
#define screenHeight 600
const Vector2 screenSize = {screenWidth, screenHeight};
#define NEARBLACK CLITERAL(Color){15, 15, 15, 255}

#define MAX_ASTEROIDS 64
static Asteroid _asteroids[MAX_ASTEROIDS] = {0};

int main() {
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
  InitWindow(screenWidth, screenHeight, "Asteroids");

  /*srand(time(0));*/

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    // Update
    UpdateDrawFrame();
    // Draw
  }

  CloseWindow();
  return 0;
}

void UpdateDrawFrame(void) {

  float frametime = GetFrameTime();
  for (int i = 0; i < MAX_ASTEROIDS; i++) {
    AsteroidUpdate(_asteroids + i, frametime);
  }

  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    GetRandomValue(0, 3);
    AddAsteroid(GetMousePosition(), (Vector2){200, 0}, ASTEROID_SMALL);
  }

  BeginDrawing();

  ClearBackground(NEARBLACK);

  for (size_t i = 0; i < MAX_ASTEROIDS; i++) {
    AsteroidDraw(_asteroids[i]);
  }

  EndDrawing();
}

void AddAsteroid(Vector2 position, Vector2 velocity, AsteroidSize size) {

  bool created = false;
  for (int i = 0; i < MAX_ASTEROIDS; i++) {
    if (_asteroids[i].active) {
      continue;
    }

    _asteroids[i] = CreateAsteroid(position, velocity, size);
    ;
    created = true;
    break;
  }

  if (!created) {
    TraceLog(LOG_ERROR, "Failed to create an asteroid because there was no "
                        "inactive spots in the array!");
  }
}
