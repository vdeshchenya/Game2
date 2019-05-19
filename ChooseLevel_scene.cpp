#include <iostream>
#include "ChooseLevel_scene.h"

ChooseLevel_scene::ChooseLevel_scene(const int &width, const int &height, RenderWindow &window) : Scene(width, height),
                                                                                                  selected(0) {
  for (int i = 0; i < numberLevels; ++i) {
    levels_images[i].loadFromFile((std::string(path) + "Textures/level" + std::to_string(i) + ".png"));
    levels_texture[i].loadFromImage(levels_images[i]);
    levels_sprites->setTexture(levels_texture[i]);
  }
  levelsPlatform_images[0].loadFromFile((std::string(path) + "Textures/levelGrassLeft.png"));
  levelsPlatform_images[1].loadFromFile((std::string(path) + "Textures/levelGrassMid.png"));
  levelsPlatform_images[2].loadFromFile((std::string(path) + "Textures/levelGrassRight.png"));
  levelsPlatform_images[3].loadFromFile((std::string(path) + "Textures/levelCandyLeft.png"));
  levelsPlatform_images[4].loadFromFile((std::string(path) + "Textures/levelCandyMid.png"));
  levelsPlatform_images[5].loadFromFile((std::string(path) + "Textures/levelCandyRight.png"));
  levelsPlatform_images[6].loadFromFile((std::string(path) + "Textures/levelIceLeft.png"));
  levelsPlatform_images[7].loadFromFile((std::string(path) + "Textures/levelIceMid.png"));
  levelsPlatform_images[8].loadFromFile((std::string(path) + "Textures/levelIceRight.png"));
  for (int i = 0; i < 3 * numberLevels; ++i) {
    levelsPlatform_texture[i].loadFromImage(levelsPlatform_images[i]);
    levelsPlatform_sprites[i].setTexture(levelsPlatform_texture[i]);
  }
  backgroundTexture.loadFromFile(std::string(path) + "Backgrounds/Menu.png");
  backgroundSprite.setTexture(backgroundTexture);
  player_image.loadFromFile(std::string(path) + "Textures/alienPink.png");
  player_texture.loadFromImage(player_image);
  player_sprite.setTexture(player_texture);
}

void ChooseLevel_scene::MoveLeft() {
  if (selected >= 1) {
    text[selected--].setFillColor(mainColor);
    text[selected].setFillColor(selectedColor);
  }
}

void ChooseLevel_scene::MoveRight() {
  if (selected <= numberLevels - 2) {
    text[selected++].setFillColor(mainColor);
    text[selected].setFillColor(selectedColor);
  }
}

void ChooseLevel_scene::keyRelease(Keyboard::Key &code) {
  switch (code) {
    case Keyboard::Left: {
      MoveLeft();
      break;
    }
    case Keyboard::A: {
      MoveLeft();
      break;
    }
    case Keyboard::Down: {
      MoveRight();
      break;
    }
    case Keyboard::D: {
      MoveRight();
      break;
    }
    default:break;
  }
}

void ChooseLevel_scene::draw(RenderWindow &window, ll &time) {
  backgroundSprite.setTexture(backgroundTexture);
  window.draw(backgroundSprite);
  double tempx = 150;
  double tempy = 150;

  player_sprite.setTexture(player_texture);
  player_sprite.setPosition(tempx + 90 * selected + 20, tempy - 50);
  player_sprite.setScale(
      40 / player_sprite.getLocalBounds().width,
      50 / player_sprite.getLocalBounds().height);
  window.draw(player_sprite);

  for (int i = 0; i < numberLevels; ++i) {
    double tempx = 150 + 90 * i;
    for (int j = 0; j < 3; ++j) {
      levelsPlatform_sprites[i * 3 + j].setTexture(levelsPlatform_texture[i * 3 + j]);
      levelsPlatform_sprites[i * 3 + j].setPosition(tempx + 20 * j, tempy);
      levelsPlatform_sprites[i * 3 + j].setScale(
          40 / levelsPlatform_sprites[i].getLocalBounds().width,
          40 / levelsPlatform_sprites[i].getLocalBounds().height);
      window.draw(levelsPlatform_sprites[i * 3 + j]);
    }
  }
}

int ChooseLevel_scene::GetSelected() const { return selected; }
