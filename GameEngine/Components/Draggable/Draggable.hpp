/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Draggable.hpp
*/

#pragma once

#include <iostream>
#include <memory>
#include <string>
#include "../../Components/AComponent/AComponent.hpp"

namespace GameEngine {

    class Draggable : public AComponent {
        public:
            friend class boost::serialization::access;
            friend class AComponent;
            Draggable() : AComponent() {
                _idComponent = 0;
                _type = CONFIG::CompType::DRAGGABLE;
                _isDragged = false;
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());

            }
            Draggable(CONFIG::CompType type) : AComponent(), _type(type) {
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
                _isDragged = false;
            }
            virtual ~Draggable() = default;


            template<class Archive>
            void serialize(Archive & ar, const unsigned int version) {
                ar.template register_type<Draggable>();
                ar & boost::serialization::base_object<AComponent>(*this);
                ar & _idComponent;
                // ar & _uuid;
                ar & _isDragged;
                ar & _type;
            }

            void startDragging() {
                _isDragged = true;
            }

            void stopDragging() {
                _isDragged = false;
            }

            bool isBeingDragged() const {
                return _isDragged;
            }

            void setEntityDragged(const std::string &uuid) {
                _uuid_entity_dragged = uuid;
            }

            std::string getEntityDragged() const {
                return _uuid_entity_dragged;
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
            bool _isDragged;
            std::string _uuid_entity_dragged;
    };
}