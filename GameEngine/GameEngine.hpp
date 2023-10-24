/*
** EPITECH PROJECT, 2023
** GameEngine
** File description:
** GameEngine
*/

#pragma once

#include "Interfaces/IComponent/IComponent.hpp"
#include "Entity/EntityManager/EntityManager.hpp"

#include "Components/Position/Position.hpp"
#include "Components/Velocity/Velocity.hpp"
#include "Components/Health/Health.hpp"
#include "Components/AI/AI.hpp"
#include "Components/HitBoxSquare/HitBoxSquare.hpp"
#include "Components/HitBoxCircle/HitBoxCircle.hpp"
#include "Components/Sprite/Sprite.hpp"
#include "Components/Weapon/Weapon.hpp"
#include "Components/Cooldown/Cooldown.hpp"
#include "Components/Sound/Sound.hpp"

#include "Systems/ASystem/ASystem.hpp"
#include "Systems/SysAI/SysAI.hpp"
#include "Systems/SysWeapon/SysWeapon.hpp"
#include "Systems/SysShoot/SysShoot.hpp"
#include "Systems/SysCollision/SysCollision.hpp"
#include "Systems/SysClear/SysClear.hpp"
#include "Systems/SysAnimation/SysAnimation.hpp"
#include "Systems/SysClearClient/SysClearClient.hpp"
// #include "Systems/SysSound/SysSound.hpp"
#include "Systems/SysCamera/SysCamera.hpp"

// #include "Systems/SysMovement/SysMovement.hpp"
// #include "Systems/SysRender/SysRender.hpp"
// #include "Systems/SysCollision/SysCollision.hpp"
#include <iostream>
#include <memory>
#include <list>


namespace GameEngine {

    class Engine {
        public:
            Engine(EntityManager manager) : _manager(std::make_shared<EntityManager>(manager)) {_isRunning = false;}
            ~Engine() {}

            void init() {
                _isRunning = false;
            }

            void run() {
                _isRunning = true;
                for (;;) {
                    for (std::shared_ptr<ISystem> &_system : _systems) {
                        _system->update();
                    }
                }
            }

            void stop() {
                _isRunning = false;
            }

            std::shared_ptr<EntityManager> getManager() {
                return _manager;
            }

            void addSystem(std::shared_ptr<ISystem> system) {
                _systems.push_back(system);
            }

            void removeSystem(std::shared_ptr<ISystem> system) {
                _systems.remove(system);
            }

            std::shared_ptr<EntityManager> _manager;
        private:
            bool _isRunning;
            std::list<std::shared_ptr<ISystem>> _systems;
    };

}
