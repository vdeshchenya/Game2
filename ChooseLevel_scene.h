#pragma once
#ifndef GAME2__CHOOSE_LEVEL_H_
#define GAME2__CHOOSE_LEVEL_H_
#include "Scene.h"

class ChooseLevel_scene : public Scene {
 public:
  ChooseLevel_scene(const int &width, const int &height, RenderWindow &window);
  void MoveLeft();
  void MoveRight();
  int GetSelected() const;
  void draw(RenderWindow &window, ll &time) override;
  void keyRelease(Keyboard::Key &code);
 private:
  int numberLevels = 3;
  Texture levels_texture[3];
  Sprite levels_sprites[3];
  Image levels_images[3];
  Texture levelsPlatform_texture[3*3];
  Sprite levelsPlatform_sprites[3*3];
  Image levelsPlatform_images[3*3];
  Texture player_texture;
  Sprite player_sprite;
  Image player_image;
  Text text[3];
  int selected;
};

#endif //GAME2__CHOOSE_LEVEL_H_
