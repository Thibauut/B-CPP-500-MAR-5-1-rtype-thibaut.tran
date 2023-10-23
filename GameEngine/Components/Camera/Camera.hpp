/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Camera.hpp
*/

#include "../../Entity/EntityManager/EntityManager.hpp"
#include "../AComponent/AComponent.hpp"
#include "../../Utils/Utils.hpp"
#include "../Position/Position.hpp"

#pragma once

namespace GameEngine {
    class Camera : public AComponent{
        public:
            friend class boost::serialization::access;
            friend class AComponent;
            Camera() : AComponent() {};
            Camera(int id) : AComponent(), _type(CONFIG::CompType::CAMERA), _name("Camera"), _idComponent(id) {}
            ~Camera() {}

            void pop() {
                _entities.erase(_entities.begin());
            }

            void push(Entity entity) {
                _entities.push_back(entity);
            }

            std::vector<Entity> getEntities() {
                return _entities;
            }

            template<class Archive>
                void serialize(Archive & ar, const unsigned int version) {
                    ar.template register_type<Camera>();
                    ar & boost::serialization::base_object<AComponent>(*this);
                    // ar & _uuid;
                    ar & _idComponent;
                    ar & _type;
                }


            void sortEntitiesByX() {
                std::sort(_entities.begin(), _entities.end(), [](Entity a, Entity b) {
                    return a.getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionX() < b.getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionX();
                });
                // A ENLEVER - START
                for (auto& entity : _entities)
                    std::cout << "x: " << entity.getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionX() << std::endl;
                std::cout << "--------------------" << std::endl;
                // A ENLEVER - END
            }

            virtual CONFIG::CompType getType() {return _type;};
            virtual void setType(const CONFIG::CompType type) {_type = type;};
            virtual int getId() {return _idComponent;};
            virtual void setId(const int id) {_idComponent = id;};
            virtual std::string getUuid() {return _uuid;};

        private:
            std::string _name;
            std::vector<Entity> _entities;
            CONFIG::CompType _type;
            int _idComponent;
            std::string _uuid;

    };
}

BOOST_CLASS_EXPORT_KEY(GameEngine::Camera);
