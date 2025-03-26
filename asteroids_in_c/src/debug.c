#include "debug.h"
#include "constants.h"

#include "raygui.h"
#include "raymath.h"

static bool _showDebugMenu = false;
static bool _debugUseCheckbox = false;
static bool _showAsteroidCount = false;
static bool _showAngleCone = false;
static Vector2 line0[2] = {0};
static Vector2 line1[2] = {0};

void ShowDebugMenu(void) {
  if (IsKeyPressed(KEY_GRAVE)) {
    _showDebugMenu = !_showDebugMenu;
  }

  if (_showDebugMenu) {
    if (!_debugUseCheckbox) {
      Rectangle r = {10, SCREEN_HEIGHT - 80, 180, 60};
      GuiToggle(r, "Toggle Asteroid Count", &_showAsteroidCount);

      r.x += 180 + 10;
      GuiToggle(r, "Show Asteroid Cone", &_showAngleCone);

      r.x += 180 + 10;
      if (GuiToggle(r, "Switch Menu Style", false)) {
        _debugUseCheckbox = !_debugUseCheckbox;

      }

    } else {
      Rectangle r = {10, SCREEN_HEIGHT - 40, 20, 20};
      GuiCheckBox(r, "Toggle Asteroid Count", &_showAsteroidCount);

      r.y -= 25;
      GuiCheckBox(r, "Show Asteroid Cone", &_showAngleCone);
    }
  }
}
