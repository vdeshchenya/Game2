#pragma once
#ifndef GMAE_GAME_SCENE_H
#define GMAE_GAME_SCENE_H
#include "Scene.h"

class Game_scene : public Scene {
 public:
  Game_scene(const int &width_, const int &height, RenderWindow &window);

  void draw(RenderWindow &window, ll &time) override;
  void keyRelease(Keyboard::Key &code);
  void setLevel(const int& new_level);

 private:
  int score;
  int lifes;

  unsigned long long int t;


  Texture levelsPlatform_texture[3];
  Sprite levelsPlatform_sprites[3];
  Image levelsPlatform_images[3];
  Texture player_texture;
  Sprite player_sprite;
  Image player_image;

  Texture hearth_texture;
  Sprite hearth_sprite;
  Image hearth_image;
  Texture textGameOver_texture;
  Sprite textGameOver_sprite;
  Image textGameOver_image;
  int SpaceForTop;
  int WField, HField;
  int TimeForNewBlock;
  double K;
  int scoreForHit;
  Text text;
  int scoreForStep;
  int level;
  double OneX, OneY;
  double playerX, playerY, playerY0;
  int levelWidth = 9, levelHeight = 50, levelVisibleHeight = 15;
  char LEVEL[50][9];

  void DrawGameStats(RenderWindow &window);
  void DrawPlayer(RenderWindow &window);
  void DrawMap(RenderWindow &texture);
  void GetMove();
  void LoadLevel();
};

#endif //GMAE_GAME_SCENE_H
