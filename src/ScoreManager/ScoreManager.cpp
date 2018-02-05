//
// ScoreManager.cpp for indie_studio in /home/baldas/Prog/repos/tek2/cpp/cpp_indie_studio/src/ScoreManager
// 
// Made by Hugo Baldassin
// Login   <baldas@epitech.net>
// 
// Started on  Fri May  5 16:32:04 2017 Hugo Baldassin
// Last update Fri May  5 16:32:05 2017 Hugo Baldassin
//

#include 	"ScoreManager.hpp"

game::ScoreManager::ScoreManager():
  _scores(4, 0)
{
}

game::ScoreManager::~ScoreManager()
{
}

void		game::ScoreManager::addScore(int id, int val)
{
  _scores[id] += val;
}

int		game::ScoreManager::getScoreById(int id) const
{
  return _scores[id];
}

std::vector<int> game::ScoreManager::getScores() const&
{
  return _scores;
}