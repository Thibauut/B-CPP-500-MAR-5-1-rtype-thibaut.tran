/*
** EPITECH PROJECT, 2023
** Team
** File description:
** Team
*/

#pragma once

#include "../../Components/AComponent/AComponent.hpp"

namespace GameEngine {
    class Team : public AComponent {
        public:
            friend class boost::serialization::access;
            friend class AComponent;
            Team() : AComponent() {
                _idComponent = 0;
                _type = CONFIG::CompType::TEAM;
                _team = 1;
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
            }
            Team(CONFIG::CompType type, int id, int value) : AComponent(CONFIG::CompType::TEAM), _idComponent(id), _type(type), _team(value) {
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
            }

            ~Team() = default;
            template<class Archive>
            void serialize(Archive & ar, const unsigned int version) {
                ar.template register_type<Team>();
                ar & boost::serialization::base_object<AComponent>(*this);
                // ar & _uuid;
                ar & _idComponent;
                ar & _type;
                ar & _team;
            }
            int getTeam() {
                return _team;
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
            int _team;
    };
}

BOOST_CLASS_EXPORT_KEY(GameEngine::Team);