#include <functional>
#include "sdl_point_utils.h"


std::size_t SDL_PointHash::operator()(const SDL_Point &p) const {
  return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
}

bool SDL_PointEqual::operator()(const SDL_Point &a, const SDL_Point &b) const {
  return a.x == b.x && a.y == b.y;
}