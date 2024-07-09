#include <cmath>
#include <iostream>
#include "route_planner.h"


Node::Node(const SDL_Point &p) 
  : g_value(0), h_value(std::numeric_limits<int>::max()), 
    dir(SDL_PointDirection::None), point(p), parent(nullptr) {}

int Node::f_value() const
{
  return g_value + h_value;
}


RoutePlanner::RoutePlanner(int w, int h, SDL_Point head, SDL_Point food, 
                           const std::vector<SDL_Point> &body, SDL_PointDirection dir) 
  : grid_width(w), grid_height(h), start_direction(dir)
{
  start_point = head;
  end_point = food;
  for (const auto &p : body)
    visited.insert(p);
  nodes.resize(grid_height, std::vector<Node *>(grid_width, nullptr));
  for (int i = 0; i < grid_height; ++i)
    for (int j = 0; j < grid_width; ++j) 
      nodes[i][j] = new Node(SDL_Point{i, j});  
}

RoutePlanner::~RoutePlanner()
{
  for (int i = 0; i < grid_height; ++i) 
    for (int j = 0; j < grid_width; ++j)
      delete nodes[i][j];
}

void RoutePlanner::AddNeighbors(Node *current_node, SDL_PointDirection current_dir) 
{
  for (const auto [dir, offset] : sdl_point_offsets)
  {
    if (dir == oppositeDir[current_dir]) continue;
    int x = (current_node->point.x + offset.first + grid_width) % grid_width;
    int y = (current_node->point.y + offset.second + grid_height) % grid_height;
    auto point = SDL_Point{x, y};
    if (visited.find(point) == visited.end()) 
    {
      visited.insert(point);
      auto node = nodes[point.x][point.y];
      node->parent = current_node;
      node->g_value = current_node->g_value + 1;
      node->h_value = CalculateHValue(point);
      node->dir = dir;
      open_list.push(node);
    }
  }
}

Node *RoutePlanner::NextNode() 
{
  auto next_node = open_list.top();
  open_list.pop();
  return next_node;
}

void RoutePlanner::ConstructFinalPath(Node *node)
{
  path.clear();
  while (node->parent)
  {
    path[node->parent->point] = {node->dir, node->point};
    node = node->parent;
  }
}

void RoutePlanner::AStarSearch()
{
  AddNeighbors(nodes[start_point.x][start_point.y], start_direction);
  visited.insert(start_point);

  while (open_list.size() > 0) 
  {
    auto current_node = NextNode();
    if (current_node->point.x == end_point.x && 
      current_node->point.y == end_point.y) 
    {
      ConstructFinalPath(current_node);
      break;
    }
    AddNeighbors(current_node, current_node->dir);
  }
}

int RoutePlanner::CalculateHValue(const SDL_Point &p) const
{
  int vdist = std::abs(p.x - end_point.x);
  int hdist = std::abs(p.y - end_point.y);
  int min_vertical = std::min(vdist, grid_height - vdist);
  int min_horizontal = std::min(hdist, grid_width - hdist);
  return min_vertical + min_horizontal;
}