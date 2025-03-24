#include "asteroid.h"
#include "raymath.h"

Asteroid CreateAsteroid(Vector2 position, Vector2 velocity, AsteroidSize size) {
  return (Asteroid){.active = true,
                    .position = position,
                    .rotation = GetRandomValue(0, 359),
                    .rotationSpeed = GetRandomValue(ASTEROID_ROT_SPEED_MIN,
                                                    ASTEROID_ROT_SPEED_MAX),
                    .size = size,
                    .velocity = velocity};
}

void AsteroidUpdate(Asteroid *asteroid, float frametime) {

  if (!asteroid->active) {
    return;
  }

  asteroid->position = Vector2Add(asteroid->position,
                                  Vector2Scale(asteroid->velocity, frametime));
  asteroid->rotation += asteroid->rotationSpeed * frametime;
}

void AsteroidDraw(Asteroid asteroid) {
  DrawPolyLines(asteroid.position, 3, 64, asteroid.rotation, WHITE);
}
