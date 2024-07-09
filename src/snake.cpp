#include "snake.h"
#include "route_planner.h"
#include <cmath>
#include <iostream>


void Snake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  

  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  body.push_back(prev_head_cell);
  body_set.insert(prev_head_cell);

  if (!growing) {
    auto tail_cell = *body.begin();
    body_set.erase(tail_cell);
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }

  SDL_Point head{current_head_cell.x, current_head_cell.y};
  if (body_set.find(head) != body_set.end())
    alive = false;
}

void Snake::GrowBody() { growing = true; }

bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) 
    return true;

  SDL_Point p{x, y};
  return body_set.find(p) != body_set.end();
}

bool Snake::IsAuto() const 
{
  return auto_mode == true;
}

void Snake::SetAuto(bool mode) 
{
  auto_mode = mode;
}

void Snake::SetDirection(Direction d)
{
  direction = d;
}

SDL_PointDirection Snake::SnakeDirToSDLDir(Snake::Direction dir) const
{
  if (dir == Snake::Direction::kDown)
    return SDL_PointDirection::Down;
  else if (dir == Snake::Direction::kUp)
    return SDL_PointDirection::Up;
  else if (dir == Snake::Direction::kLeft)
    return SDL_PointDirection::Left;
  return SDL_PointDirection::Right;
}

Snake::Direction Snake::SDLDirToSnakeDir(SDL_PointDirection dir) const
{
  if (dir == SDL_PointDirection::Down)
    return Snake::Direction::kDown;
  else if (dir == SDL_PointDirection::Up)
    return Snake::Direction::kUp;
  else if (dir == SDL_PointDirection::Left)
    return Snake::Direction::kLeft;
  else 
    return Snake::Direction::kRight;
}

void Snake::Navigate(SDL_Point food)
{
  int x = static_cast<int>(head_x);
  int y = static_cast<int>(head_y);
  SDL_Point head = SDL_Point{x, y};
  if (path.size() == 0 || path.find(head) == path.end()) 
  {
    SDL_PointDirection dir = SnakeDirToSDLDir(direction);
    auto rp = RoutePlanner(grid_width, grid_height, head, food, body, dir);
    rp.AStarSearch();
    if (rp.getPath().size() == 0)
    {
      alive = false;
      std::cout << "cannot find a path to the food, snake goes die...\n";
    } 
    SetPath(std::move(rp.getPath())); 
  }
  SetDirection(SDLDirToSnakeDir(GetPath()[head].first));
}

Path Snake::GetPath() const {
  return path;
}

void Snake::SetPath(const Path &&path_) {
  path = std::move(path_);
}

void Snake::ResetPath() {
  path.clear();
}