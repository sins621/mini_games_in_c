#include "raylib.h"
#include "stdio.h"

#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 320

const int BLOCK_SIZE = WINDOW_HEIGHT / 20;
const float PADDLE_SPEED = 5;
float ball_speed = 4.0f;
float vertical_direction = 0;

int collidesWithPaddle1(struct Rectangle *ball, struct Rectangle *paddle_1);
int collidesWithPaddle2(struct Rectangle *ball, struct Rectangle *paddle_2);
float calculateCollisionOffset(struct Rectangle *ball,
                               struct Rectangle *paddle);

int main() {
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pong");

  struct Rectangle paddle_1 = {BLOCK_SIZE, WINDOW_HEIGHT / 2, BLOCK_SIZE,
                               BLOCK_SIZE * 2};
  struct Rectangle paddle_2 = {WINDOW_WIDTH - BLOCK_SIZE * 2, WINDOW_HEIGHT / 2,
                               BLOCK_SIZE, BLOCK_SIZE * 2};
  struct Rectangle ball = {WINDOW_WIDTH / 2 - BLOCK_SIZE / 2,
                           WINDOW_HEIGHT / 2 + BLOCK_SIZE / 2, BLOCK_SIZE,
                           BLOCK_SIZE};

  SetTargetFPS(30);

  while (!WindowShouldClose()) {
    // Update
    if (IsKeyDown(KEY_W))
      paddle_1.y -= PADDLE_SPEED;
    if (IsKeyDown(KEY_S))
      paddle_1.y += PADDLE_SPEED;

    if (collidesWithPaddle1(&ball, &paddle_1)) {
      ball_speed *= -1.0f;
      ball_speed *= 1.1f;
      vertical_direction += calculateCollisionOffset(&ball, &paddle_1);
    }
    if (collidesWithPaddle2(&ball, &paddle_2))
      ball_speed *= -1.0f;

    if (ball.y < 0 || ball.y > WINDOW_HEIGHT - BLOCK_SIZE)
      vertical_direction *= -1;
    ball.x += ball_speed;
    ball.y += vertical_direction;
    paddle_2.y = ball.y;

    printf("\n %f", ball_speed);

    BeginDrawing();
    DrawRectangleRec(paddle_1, GREEN);
    DrawRectangleRec(paddle_2, GREEN);
    DrawRectangleRec(ball, GREEN);

    ClearBackground(BLACK);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}

int collidesWithPaddle1(struct Rectangle *ball, struct Rectangle *paddle_1) {
  if (ball->x < paddle_1->x + BLOCK_SIZE + 2) {
    if (ball->y > paddle_1->y - BLOCK_SIZE &&
        ball->y < paddle_1->y + BLOCK_SIZE * 2) {
      return 1;
    }
  } else {
    return 0;
  }
}

int collidesWithPaddle2(struct Rectangle *ball, struct Rectangle *paddle_2) {
  if (ball->x > paddle_2->x - BLOCK_SIZE - 2) {
    return 1;
  } else {
    return 0;
  }
}

float calculateCollisionOffset(struct Rectangle *ball,
                               struct Rectangle *paddle) {
  const float PADDLE_CENTER_POSITION = paddle->y + 8;
  const float BALL_CENTER_POSITION = ball->y;

  return (BALL_CENTER_POSITION - PADDLE_CENTER_POSITION) / 5;
}