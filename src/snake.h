#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <unordered_set>
#include <mutex>
#include <memory>
#include <unordered_map>
#include "SDL.h"
#include "sdl_point_utils.h"


class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);

  bool IsAuto() const;
  void SetAuto(bool mode);
  void SetDirection(Direction);
  void Navigate(SDL_Point);
  Path GetPath() const;
  void SetPath(const Path &&);
  void ResetPath();

  Direction direction = Direction::kUp;

  float speed{0.05f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;
  bool pause{false};

private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);
  SDL_PointDirection SnakeDirToSDLDir(Snake::Direction) const;
  Snake::Direction SDLDirToSnakeDir(SDL_PointDirection) const;


  std::unordered_set<SDL_Point, SDL_PointHash, SDL_PointEqual> body_set;

  bool growing{false};
  int grid_width;
  int grid_height;

  bool auto_mode{false};
  Path path;
};

#endif