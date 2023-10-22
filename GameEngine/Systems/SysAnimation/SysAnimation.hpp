/*
** EPITECH PROJECT, 2023
** SysMovement
** File description:
** SysMovement
*/

#pragma once
#include "../ASystem/ASystem.hpp"
#include "../../Utils/Utils.hpp"
#include <SFML/Graphics.hpp>
#include "../../Components/Sprite/Sprite.hpp"
#include "../../Components/Position/Position.hpp"
#include <list>
#include "../../../client/graphical/utils/sfml_func.hpp"

namespace GameEngine {

    class SysAnimation : public ISystem {
        public:
            SysAnimation(std::shared_ptr<EntityManager> entityManagerPtr) : _entityManager(entityManagerPtr) {};
            virtual ~SysAnimation() = default;

            virtual void update() {
                for (std::shared_ptr<Entity> &entity : _entityManager->getEntities()) {
                    if (entity) {
                        std::vector<std::shared_ptr<Sprite>> SpriteComps = entity->getComponentsByType<Sprite>(CONFIG::CompType::SPRITE);
                        for (std::shared_ptr<Sprite> spriteComp : SpriteComps) {
                            if (spriteComp->getDoAnimationUp() == true && entity->getType() == 1 && spriteComp->getSpriteType() == CONFIG::SpriteType::PLAYERSPRITE) {
                                bool tmpBool = spriteComp->getDoAnimationUp();
                                sf::IntRect tmpRect = spriteComp->getRect();
                                sf::Sprite tmpSprite = spriteComp->getSprite();
                                sf::Clock tmpClock = spriteComp->getClock();

                                AnimationInput(0.15, 99.6, spriteComp->getMaxWidth(), spriteComp->getSpriteWidth(), tmpBool, tmpSprite, tmpRect, tmpClock, false);

                                spriteComp->setDoAnimationUp(tmpBool);
                                spriteComp->setIntRect(tmpRect);
                                spriteComp->initRect();
                                spriteComp->setSprite(tmpSprite);
                                spriteComp->setClock(tmpClock);
                            }
                            if (spriteComp->getDoAnimationDown() == true && entity->getType() == 1 && spriteComp->getSpriteType() == CONFIG::SpriteType::PLAYERSPRITE) {
                                bool tmpBool = spriteComp->getDoAnimationDown();
                                sf::IntRect tmpRect = spriteComp->getRect();
                                sf::Sprite tmpSprite = spriteComp->getSprite();
                                sf::Clock tmpClock = spriteComp->getClock();

                                AnimationInput(0.1, 99.6, 0, spriteComp->getSpriteWidth(), tmpBool, tmpSprite, tmpRect, tmpClock, true);

                                spriteComp->setDoAnimationDown(tmpBool);
                                spriteComp->setIntRect(tmpRect);
                                spriteComp->initRect();
                                spriteComp->setSprite(tmpSprite);
                                spriteComp->setClock(tmpClock);
                            }
                            if (entity->getType() == 2 && spriteComp->getSpriteType() == CONFIG::SpriteType::ENEMYSPRITE) {
                                sf::IntRect tmpRect = spriteComp->getRect();
                                if(getLeft == false) {
                                    tmpLeft = spriteComp->getRect().left;
                                    getLeft = true;
                                }
                                sf::Sprite tmpSprite = spriteComp->getSprite();
                                sf::Clock tmpClock = spriteComp->getClock();
                                AnimateLoop(spriteComp->getAnimDelay(), tmpLeft, spriteComp->getMaxWidth(), spriteComp->getSpriteWidth(), tmpSprite, tmpRect, tmpClock);

                                spriteComp->setIntRect(tmpRect);
                                spriteComp->initRect();
                                spriteComp->setSprite(tmpSprite);
                                spriteComp->setClock(tmpClock);
                            }
                            if (spriteComp->getDoAnimationDead() == true && entity->getType() == 2 && spriteComp->getSpriteType() == CONFIG::SpriteType::DEATHSPRITE) {
                                int x = entity->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionX();
                                int y = entity->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionY();
                                spriteComp->setPositionSprite(sf::Vector2f(x, y));
                                bool tmpBool = spriteComp->getDoAnimationDead();
                                sf::IntRect tmpRect = spriteComp->getRect();
                                sf::Sprite tmpSprite = spriteComp->getSprite();
                                sf::Clock tmpClock = spriteComp->getClock();
                                if(getLeft2 == false) {
                                    tmpLeft2 = spriteComp->getRect().left;
                                    getLeft2 = true;
                                }
                                AnimationInput(spriteComp->getAnimDelay(), tmpLeft2, spriteComp->getMaxWidth(), spriteComp->getSpriteWidth(), tmpBool,tmpSprite, tmpRect, tmpClock, false);
                                spriteComp->setIntRect(tmpRect);
                                spriteComp->initRect();
                                spriteComp->setSprite(tmpSprite);
                                spriteComp->initSprite();
                                spriteComp->setClock(tmpClock);
                                spriteComp->setDoAnimationDead(tmpBool);
                                if (spriteComp->getDoAnimationDead() == false && entity->getIsDeath() == true) {
                                    _entityManager->deleteEntity(entity->getUuid());
                                    return;
                                }
                            }
                        }
                    }
                }
            }

            void AnimationInput(float animDuration, float start, float end, float frameSize, bool &animStart, sf::Sprite &_sprite, sf::IntRect &_rect, sf::Clock &_clock, bool isNeg) {
                sf::Time elapsed = _clock.getElapsedTime();
                if (elapsed.asSeconds() > animDuration) {
                    if (isNeg == false) {
                        _rect.left += frameSize;
                        if (_rect.left >= end - frameSize) {
                            _rect.left = start;
                            animStart = false;
                        }
                    }
                    if (isNeg == true) {
                        _rect.left -= frameSize;
                        if (_rect.left <= end) {
                            _rect.left = start;
                            animStart = false;
                        }
                    }
                    _sprite.setTextureRect(_rect);
                    _clock.restart();
                }
                return;
            }

            void AnimateLoop(float animDuration, float start, float end, float frameSize, sf::Sprite &_sprite, sf::IntRect &_rect, sf::Clock &_clock) {
                sf::Time elapsed = _clock.getElapsedTime();
                if (elapsed.asSeconds() > animDuration) {
                    _rect.left += frameSize;
                    if (_rect.left >= end - frameSize) {
                        _rect.left = start;
                    }
                    _sprite.setTextureRect(_rect);
                    _clock.restart();
                }
                return;
            }

        private:
            std::shared_ptr<EntityManager>  _entityManager;
            SfmlFunc sfmlFunc;
            bool getLeft = false;
            int tmpLeft;

            bool getLeft2 = false;
            int tmpLeft2;
    };
}
