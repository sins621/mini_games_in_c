#include <stdlib.h>
#include <time.h>

#include "raylib.h"
#include "raymath.h"

#include "asteroid.h"

void UpdateDrawFrame(void);
void AddAsteroid(Vector2 position, AsteroidSize size);

#define screenWidth 600
#define screenHeight 600
const Vector2 screenCenter = {(float)(screenWidth) / 2,
                              (float)(screenHeight) / 2};
#define NEARBLACK CLITERAL(Color){15, 15, 15, 255}

#define MAX_ASTEROIDS 64
#define ASTEROID_RANDOM_ANGLE 30 * DEG2RAD
static AsteroidSize _sizes[] = {ASTEROID_SMALL, ASTEROID_MEDIUM,
                                ASTEROID_LARGE};
static Asteroid _asteroids[MAX_ASTEROIDS] = {0};

// Debug
bool _showAngleCone = true;
Vector2 line0[2] = {0};
Vector2 line1[2] = {0};
//

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
    AsteroidSize nextSize = _sizes[GetRandomValue(0, 2)];
    AddAsteroid(GetMousePosition(), nextSize);
  }

  BeginDrawing();

  ClearBackground(NEARBLACK);

  for (size_t i = 0; i < MAX_ASTEROIDS; i++) {
    AsteroidDraw(_asteroids[i]);
  }

  if (_showAngleCone) {
    DrawLineV(line0[0], line0[1], RED);
    DrawLineV(line1[0], line1[1], BLUE);
  }

  EndDrawing();
}

void AddAsteroid(Vector2 position, AsteroidSize size) {

  bool created = false;
  Vector2 velocity = Vector2Subtract(screenCenter, position);
  velocity =
      Vector2Scale(Vector2Normalize(velocity),
                   GetRandomValue(ASTEROID_SPEED_MIN, ASTEROID_SPEED_MAX));
  velocity =
      Vector2Rotate(velocity, (float)GetRandomValue(-ASTEROID_RANDOM_ANGLE,
                                                    ASTEROID_RANDOM_ANGLE));

  if (_showAngleCone) {
    line0[0] = position;
    line1[0] = position;

    line0[1] = Vector2Add(position, Vector2Rotate(Vector2Scale(velocity, 10),
                                                  -ASTEROID_RANDOM_ANGLE));
    line1[1] = Vector2Add(position, Vector2Rotate(Vector2Scale(velocity, 10),
                                                  ASTEROID_RANDOM_ANGLE));
  }

  for (int i = 0; i < MAX_ASTEROIDS; i++) {
    if (_asteroids[i].active) {
      continue;
    }

    _asteroids[i] = CreateAsteroid(position, velocity, size);

    created = true;
    break;
  }

  if (!created) {
    TraceLog(LOG_ERROR, "Failed to create an asteroid because there was no "
                        "inactive spots in the array!");
  }
}
