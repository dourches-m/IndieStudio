//
// ScoreManager.hpp for indie_studio in /home/baldas/Prog/repos/tek2/cpp/cpp_indie_studio/src/ScoreManager
// 
// Made by Hugo Baldassin
// Login   <baldas@epitech.net>
// 
// Started on  Fri May  5 16:31:50 2017 Hugo Baldassin
// Last update Fri May  5 16:31:52 2017 Hugo Baldassin
//

#ifndef		SCOREMANAGER_HPP_
# define	SCOREMANAGER_HPP_

# include	<vector>

namespace game
{
  class ScoreManager {
    public:
    ScoreManager();
    ~ScoreManager();

    void addScore(int id, int val);
    int getScoreById(int id) const;
    std::vector<int> getScores() const&;

    private:
    std::vector<int> _scores;
  };
}

#endif		/* !SCOREMANAGER_HPP_ */
