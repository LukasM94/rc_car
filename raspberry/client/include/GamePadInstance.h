#ifndef GAME_PAD_INSTANCE_H
#define GAME_PAD_INSTANCE_H

#include <GamePad.h>
#include <atomic>

class GamePadInstance
{
  public:
    static GamePadInstance* instance();
    ~GamePadInstance();

    GamePad* getGamePad();
    
    inline void startGamePadClient()
    {
      active_game_pad_client_ = 1;
    }
    inline void exitGamePadClient()
    {
      game_pad_.reset();
      active_game_pad_client_ = 0;
    }
    inline void incrementUController()
    {
      active_u_controller_++;
    }
    inline void decrementUController()
    {
      active_u_controller_--;
    }

  private:
    GamePadInstance();
    GamePadInstance(const GamePadInstance&);

    static GamePadInstance* instance_;

    GamePad game_pad_;

    std::atomic_int8_t active_game_pad_client_;
    std::atomic_int8_t active_u_controller_;
};

#endif