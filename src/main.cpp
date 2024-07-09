#include <iostream>
#include <fstream>
#include <sstream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int saveHighestScore(int score) 
{
    std::string line;
    int highest = 0;
    std::ifstream stream("record");
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> highest;
        stream.close();
    }
    if (score > highest) {
        std::ofstream outstream("record");
        if (outstream.is_open()) {
            outstream << score;
            outstream.close();
            highest = score;
        }
    }
    return highest;
}

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);

  int score = game.GetScore();
  int highest = saveHighestScore(score);
  
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << score << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  std::cout << "Highest record: " << highest << "\n";
  return 0;
}