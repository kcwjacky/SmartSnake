#ifndef SDL_POINT_UTILS
#define SDL_POINT_UTILS

#include "SDL.h"

enum class SDL_PointDirection
{
    None, Up, Right, Down, Left
};

struct SDL_PointHash 
{ 
    std::size_t operator()(const SDL_Point &) const; 
};

struct SDL_PointEqual 
{ 
    bool operator()(const SDL_Point &, const SDL_Point &) const; 
};

typedef std::unordered_map<SDL_Point, 
                           std::pair<SDL_PointDirection, SDL_Point>, 
                           SDL_PointHash, SDL_PointEqual> Path;

#endif