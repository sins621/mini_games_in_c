#ifndef DEBUG_H_
#define DEBUG_H_

#include "raylib.h"

/// @brief Call from within a BeginDrawing2D!
void ShowDebugMenu(void);

/// @brief Call from within a BeginDrawing2D!
void ShowDebugVisualization(int asteroidCount);

void SetLastCone(Vector2 position, Vector2 velocity);

#endif
