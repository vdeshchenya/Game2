#include "Game_scene.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>

Game_scene::Game_scene(const int &width_, const int &height_, RenderWindow &window) : Scene(width_, height_),
                                                                                      K(1),
                                                                                      SpaceForTop(30),
                                                                                      lifes(3),
                                                                                      TimeForNewBlock(0),
                                                                                      score(0),
                                                                                      t(0),
                                                                                      scoreForStep(1),
                                                                                      scoreForHit(10),
                                                                                      WField(5),
                                                                                      HField(9) {
  font.loadFromFile(std::string(path) + "Fonts/rita.ttf");
  hearth_image.loadFromFile(std::string(path) + "Images/Hearth.png");
  backgroundTexture.loadFromFile(std::string(path) + "Backgrounds/Game.png");
  textGameOver_image.loadFromFile(std::string(path) + "Images/textGameOver.png");
  hearth_texture.loadFromImage(hearth_image);
  textGameOver_texture.loadFromImage(textGameOver_image);
  textGameOver_sprite.setPosition(width / 2.5, height / 3.0);
  width = 400;
  height = 700;
  text.setFillColor(Color::Black);
  text.setPosition(width - 22, -6);
  player_image.loadFromFile((std::string(path) + "Textures/alienPink.png"));
  player_texture.loadFromImage(player_image);
  player_sprite.setTexture(player_texture);

  OneX = (double) width / levelWidth;
  OneY = (double) height / levelVisibleHeight;
}

void Game_scene::setLevel(const int &new_level) {
  level = new_level;
  LoadLevel();
}

void Game_scene::LoadLevel() {
  std::ifstream in(std::string(path) + "Levels/level" + std::to_string(level));
  for (int i = 0; i < levelHeight; ++i) {
    std::string temp;
    std::getline(in, temp);
    for (int j = 0; j < levelHeight; ++j) {
      LEVEL[i][j] = temp[j];
      if (temp[j] == '#') {
        playerY0 = i * OneY;
        playerX = j * OneX;
        playerY = i * OneY;
      }
    }
  }
  switch (level) {
    case 0 : {
      levelsPlatform_images[0].loadFromFile((std::string(path) + "Textures/levelGrassLeft.png"));
      levelsPlatform_images[1].loadFromFile((std::string(path) + "Textures/levelGrassMid.png"));
      levelsPlatform_images[2].loadFromFile((std::string(path) + "Textures/levelGrassRight.png"));
      break;
    }
    case 1 : {
      levelsPlatform_images[0].loadFromFile((std::string(path) + "Textures/levelCandyLeft.png"));
      levelsPlatform_images[1].loadFromFile((std::string(path) + "Textures/levelCandyMid.png"));
      levelsPlatform_images[2].loadFromFile((std::string(path) + "Textures/levelCandyRight.png"));
      break;
    }
    case 2 : {
      levelsPlatform_images[0].loadFromFile((std::string(path) + "Textures/levelIceLeft.png"));
      levelsPlatform_images[1].loadFromFile((std::string(path) + "Textures/levelIceMid.png"));
      levelsPlatform_images[2].loadFromFile((std::string(path) + "Textures/levelIceRight.png"));
      break;
    }
  }

  for (int i = 0; i < 3; ++i) {
    levelsPlatform_texture[i].loadFromImage(levelsPlatform_images[i]);
    levelsPlatform_sprites[i].setTexture(levelsPlatform_texture[i]);
  }
  in.close();
}

void Game_scene::draw(RenderWindow &window, ll &time) {
  backgroundSprite.setTexture(backgroundTexture);
  window.draw(backgroundSprite);
  if (lifes <= 0) {
    textGameOver_sprite.setTexture(backgroundTexture);
    window.draw(textGameOver_sprite);
    return;
  }
  DrawMap(window);
  DrawPlayer(window);
  DrawGameStats(window);
  if (TimeForNewBlock == 3) {
    TimeForNewBlock = 0;
    K *= 1.1;
  }
  if (time > 1000000 / K) {
    time = 0;
    TimeForNewBlock += 1;
  }
}

void Game_scene::keyRelease(Keyboard::Key &code) {
  switch (code) {
    case Keyboard::A: {
      playerX -= OneX;
      break;
    }
    case Keyboard::Left: {
      playerX -= OneX;
      break;
    }
    case Keyboard::W: {
      playerY += OneY;
      break;
    }
    case Keyboard::D: {
      playerX += OneX;
      break;
    }
    case Keyboard::Right: {
      playerX += 1;
      break;
    }
    case Keyboard::S: {
      playerY -= OneY;
      break;
    }
    case Keyboard::F5: {
      break;
    }
    default: break;
  }
}

void Game_scene::DrawGameStats(RenderWindow &window) {
  text.setFont(font);
  if (score >= 10000) {
    text.setPosition(width - 102, -6);
  } else if (score >= 1000) {
    text.setPosition(width - 82, -6);
  } else if (score >= 100) {
    text.setPosition(width - 62, -6);
  } else if (score >= 10) {
    text.setPosition(width - 42, -6);
  }
  text.setString(std::to_string(score));
  window.draw(text);
  if (lifes >= 1) {
    hearth_sprite.setTexture(hearth_texture);
    hearth_sprite.setPosition(10, 2);
    hearth_sprite.setScale(0.2, 0.2);
    window.draw(hearth_sprite);
  }
  if (lifes >= 2) {
    hearth_sprite.setTexture(hearth_texture);
    hearth_sprite.setPosition(40, 2);
    hearth_sprite.setScale(0.2, 0.2);
    window.draw(hearth_sprite);
  }
  if (lifes >= 3) {
    hearth_sprite.setTexture(hearth_texture);
    hearth_sprite.setPosition(70, 2);
    hearth_sprite.setScale(0.2, 0.2);
    window.draw(hearth_sprite);
  }
  if (lifes >= 4) {
    hearth_sprite.setTexture(hearth_texture);
    hearth_sprite.setPosition(100, 2);
    hearth_sprite.setScale(0.2, 0.2);
    window.draw(hearth_sprite);
  }
}

void Game_scene::DrawMap(RenderWindow &window) {
  for (int i = std::max(0, int(playerY/OneY) - 5); i < std::min(levelVisibleHeight, int(playerY/OneY + 11)); ++i) {
    for (int j = 0; j < levelWidth; ++j) {
      switch (LEVEL[i][j]) {
        case '*': break;
        case 'A': {
          levelsPlatform_sprites[0].setTexture(levelsPlatform_texture[0]);
          levelsPlatform_sprites[0].setPosition(0 + OneX * j, 0 + OneY * i - (playerY0 - playerY));
          levelsPlatform_sprites[0].setScale(
              OneX / levelsPlatform_sprites[0].getLocalBounds().width,
              OneY / levelsPlatform_sprites[0].getLocalBounds().height);
          window.draw(levelsPlatform_sprites[0]);
          break;
        }

        case 'B': {
          levelsPlatform_sprites[1].setTexture(levelsPlatform_texture[1]);
          levelsPlatform_sprites[1].setPosition(0 + OneX * j, 0 + OneY * i - (playerY0 - playerY));
          levelsPlatform_sprites[1].setScale(
              OneX / levelsPlatform_sprites[1].getLocalBounds().width,
              OneY / levelsPlatform_sprites[1].getLocalBounds().height);
          window.draw(levelsPlatform_sprites[1]);
          break;
        }

        case 'C': {
          levelsPlatform_sprites[2].setTexture(levelsPlatform_texture[2]);
          levelsPlatform_sprites[2].setPosition(0 + OneX * j, 0 + OneY * i - (playerY0 - playerY));
          levelsPlatform_sprites[2].setScale(
              OneX / levelsPlatform_sprites[2].getLocalBounds().width,
              OneY / levelsPlatform_sprites[2].getLocalBounds().height);
          window.draw(levelsPlatform_sprites[2]);
          break;
        }
      }
    }
  }
}

void Game_scene::DrawPlayer(RenderWindow &window) {
  player_sprite.setTexture(player_texture);
  player_sprite.setPosition(playerX, OneY * 7);
  player_sprite.setScale(
      OneX / player_sprite.getLocalBounds().width,
      OneY / player_sprite.getLocalBounds().height);
  window.draw(player_sprite);
}