/*
** EPITECH PROJECT, 2023
** SysMovement
** File description:
** SysMovement
*/

#pragma once
#include "../ASystem/ASystem.hpp"
#include "../../Utils/Utils.hpp"
#include <list>

namespace GameEngine {

    class SysMovement : public ISystem {
        public:
            SysMovement(std::shared_ptr<EntityManager> entityManagerPtr) : _entityManager(entityManagerPtr) {};
            virtual ~SysMovement() = default;

            virtual void update() {
                
                
                // for (auto& entity : _entityManager->getEntities()) {

                    // if (entity.get()->getComponentByType<CONFIG::CompType>(CONFIG::CompType::POSITION) != nullptr) {
                    //     // std::shared_ptr< = entity.get()->getComponentByType<CONFIG::CompType>(CONFIG::CompType::POSITION);
                    // }

                    // if (entity.get()->getComponentByType<CONFIG::CompType>(CONFIG::CompType::DIRECTION) != nullptr) {
                        
                    // }

                    // if (entity.get()->getComponentByType<CONFIG::CompType>(CONFIG::CompType::VELOCITY) != nullptr) {
                        
                    // }

                // switch (entity->getComponentByType()) {
                    // case CONFIG::Dir::RIGHT:
                    //     std::cout << "Sys Mov : right detected" << std::endl;
                    //     break;
                    // case CONFIG::Dir::LEFT:
                    //     std::cout << "Sys Mov : left detected" << std::endl;
                    //     break;
                    // case CONFIG::Dir::UP:
                    //     std::cout << "Sys mov : up detected" << std::endl;
                    //     break;
                    // case CONFIG::Dir::DOWN:
                    //     std::cout << "Sys mov : down detected" << std::endl;
                    //     break;
                    // default:
                    //     break;
                // };
            // }
                }
        protected:
        private:
          std::shared_ptr<EntityManager>  _entityManager;
    };
}
