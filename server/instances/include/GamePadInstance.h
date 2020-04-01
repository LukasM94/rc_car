#ifndef GAME_PAD_INSTANCE_H
#define GAME_PAD_INSTANCE_H

class GamePad;

class GamePadInstance
{
  public:
    static GamePadInstance* instance();
    ~GamePadInstance();
    GamePad* getGamePad();
    void setGamePad(GamePad* const game_pad);
  private:
    GamePadInstance();
    static GamePadInstance* instance_;
    GamePad* game_pad_;
};

#endif