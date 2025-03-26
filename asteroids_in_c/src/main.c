#include "raygui.h"
#include "raylib.h"
#include "raymath.h"
#include "stdio.h"

#include "asteroid.h"
#include "constants.h"

void UpdateDrawFrame(void);
void AddAsteroid(Vector2 position, AsteroidSize size);
Vector2 GetNextAsteroidPosition(void);

const Vector2 screenCenter = {(float)(SCREEN_WIDTH) / 2,
                              (float)(SCREEN_HEIGHT) / 2};

static AsteroidSize _sizes[] = {ASTEROID_SMALL, ASTEROID_MEDIUM,
                                ASTEROID_LARGE};
static Asteroid _asteroids[MAX_ASTEROIDS] = {0};
static float _lastAsteroidCreationTime = -1.0f;
// Debug

bool _isDebug = false;
bool _showDebugMenu = false;
bool _showAsteroidCount = false;
bool _showAngleCone = false;
Vector2 line0[2] = {0};
Vector2 line1[2] = {0};
//

int main() {
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
  InitWindow(SCREEN_WIDTH, SCREEN_WIDTH, "Asteroids");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    // Update
    UpdateDrawFrame();
    if (_isDebug) {
      printf("%f\n", GetTime());
    }
    // Draw
  }

  CloseWindow();
  return 0;
}

void UpdateDrawFrame(void) {

  float frametime = GetFrameTime();
  float time = GetTime();
  for (int i = 0; i < MAX_ASTEROIDS; i++) {
    AsteroidUpdate(_asteroids + i, frametime, time);
  }

  if (_isDebug) {
    printf("Window Time %f\n", time);
    printf("Last Creation Time %f\n", _lastAsteroidCreationTime);
  }

  if (time > _lastAsteroidCreationTime + ASTEROID_DELAY) {
    AsteroidSize nextSize = _sizes[GetRandomValue(0, 2)];
    AddAsteroid(GetNextAsteroidPosition(), nextSize);
    _lastAsteroidCreationTime = time;
  }

  if (IsKeyPressed(KEY_GRAVE)) {
    _showDebugMenu = !_showDebugMenu;
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

  if (_showAsteroidCount) {
    int count = 0;
    for (int i = 0; i < MAX_ASTEROIDS; i++) {
      if (_asteroids[i].active) {
        count++;
      }
    }
    DrawRectangle(10, 10, 100, 52, Fade(BLACK, 0.6f));
    DrawText(TextFormat("ASTEROIDS: %d", count), 20, 20, 32, WHITE);
  }

  if (_showDebugMenu) {
    Rectangle r = {10, SCREEN_HEIGHT - 40, 20, 20};
    GuiCheckBox(r, "Toggle Asteroid Count", &_showAsteroidCount);

    r.y -= 25;
    GuiCheckBox(r, "Show Asteroid Cone", &_showAngleCone);
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

Vector2 GetNextAsteroidPosition(void) {
  int padding = 128;
  Vector2 result = {-padding, padding};
  if (GetRandomValue(0, 1)) {
    if (GetRandomValue(0, 1)) {
    } else {
      result.y = SCREEN_HEIGHT + padding;
    }
    result.x = GetRandomValue(-padding, SCREEN_WIDTH + padding);
  } else {
    if (GetRandomValue(0, 1)) {
    } else {
      result.x = SCREEN_WIDTH + padding;
    }
    result.y = GetRandomValue(-padding, SCREEN_HEIGHT + padding);
  }

  return result;
}
