/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Event.hpp
*/

#pragma once

#include <iostream>
#include <memory>
#include <string>
#include "../../Components/AComponent/AComponent.hpp"
#include "../../Entity/EntityManager/EntityManager.hpp"
#include <SFML/Graphics.hpp>


namespace GameEngine {

    class Event : public AComponent {
        public:
            friend class boost::serialization::access;
            friend class AComponent;

            struct event_data {
                std::shared_ptr<EntityManager> entity_manager;
                std::shared_ptr<Entity> entity;
                sf::Event *event;
                sf::Vector2f mouse;
                std::shared_ptr<StateManager> is_running;
            };

            struct event_config {
                bool (*isActive)(event_data &data);
                void (*action)(event_data &data);
            };

            Event() : AComponent() {
                _idComponent = 0;
                _type = CONFIG::CompType::EVENT;
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());

            }
            Event(event_config config) : AComponent(CONFIG::CompType::EVENT), _type(CONFIG::CompType::EVENT) {
                _config.action = config.action;
                _config.isActive = config.isActive;
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
            }
            virtual ~Event() = default;


            template<class Archive>
            void serialize(Archive & ar, const unsigned int version) {
                ar.template register_type<Event>();
                ar & boost::serialization::base_object<AComponent>(*this);
                ar & _idComponent;
                // ar & _uuid;
                ar & _type;
            }

            void run(event_data data) {
                if (_config.isActive(data))
                    _config.action(data);
            }

            virtual CONFIG::CompType getType() {return _type;};
            virtual void setType(const CONFIG::CompType type) {_type = type;};
            virtual int getId() {return _idComponent;};
            virtual void setId(const int id) {_idComponent = id;};
            virtual std::string getUuid() {return _uuid;};

        protected:
            int _idComponent;
            CONFIG::CompType _type;
            std::string _uuid;

        private:
            event_config _config;
    };
}