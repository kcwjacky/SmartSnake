#ifndef ROUTE_PLANNER_H
#define ROUTE_PLANNER_H

#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include "SDL.h"
#include "sdl_point_utils.h"


class Node {
public:
  Node(const SDL_Point &);
  int f_value() const;

  int h_value; 
  int g_value; 
  SDL_PointDirection dir;
  SDL_Point point;
  Node *parent;
};


class RoutePlanner {
public:
  RoutePlanner(int grid_width, int grid_height, 
               SDL_Point head, SDL_Point food, 
               const std::vector<SDL_Point> &body, SDL_PointDirection dir);

  ~RoutePlanner();
  void AStarSearch();
  Path getPath() { return path; };

private:
  int CalculateHValue(const SDL_Point &) const;
  void AddNeighbors(Node *, SDL_PointDirection);
  Node *NextNode();
  void ConstructFinalPath(Node *);

  std::unordered_set<SDL_Point, SDL_PointHash, SDL_PointEqual> visited;
  std::vector<std::vector<Node *>> nodes;

  struct CompareNodes {
    bool operator()(const Node* a, const Node* b) const {
        return a->f_value() > b->f_value();
    }
  };

  std::priority_queue<Node *, std::vector<Node *>, 
    CompareNodes> open_list;

  std::unordered_map<SDL_PointDirection, SDL_PointDirection> oppositeDir = {
    {SDL_PointDirection::Up, SDL_PointDirection::Down}, 
    {SDL_PointDirection::Down, SDL_PointDirection::Up}, 
    {SDL_PointDirection::Left, SDL_PointDirection::Right}, 
    {SDL_PointDirection::Right, SDL_PointDirection::Left}, 
  };

  std::unordered_map<SDL_PointDirection, std::pair<int, int>> sdl_point_offsets = {
    {SDL_PointDirection::Up, {0, -1}}, {SDL_PointDirection::Right, {1, 0}}, 
    {SDL_PointDirection::Down, {0, 1}}, {SDL_PointDirection::Left, {-1, 0}}
  };


  SDL_Point start_point;
  SDL_Point end_point;

  int grid_width;
  int grid_height;

  SDL_PointDirection start_direction{SDL_PointDirection::None};
  Path path;
};


#endif