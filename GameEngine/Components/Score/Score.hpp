/*
** EPITECH PROJECT, 2023
** Health
** File description:
** Health
*/

#pragma once

#include "../../Components/AComponent/AComponent.hpp"

namespace GameEngine {
    class Score : public AComponent {
        public:
            friend class boost::serialization::access;
            friend class AComponent;
            Score() : AComponent() {
                _idComponent = 0;
                _type = CONFIG::CompType::SCORE;
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
            }
            Score(CONFIG::CompType type, int id, int value) : AComponent(CONFIG::CompType::SCORE), _idComponent(id), _type(type), _score(value) {
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
            }

            ~Score() = default;

            template<class Archive>
            void serialize(Archive & ar, const unsigned int version) {
                ar.template register_type<Score>();
                ar & boost::serialization::base_object<AComponent>(*this);
                // ar & _uuid;
                ar & _idComponent;
                ar & _type;
                ar & _score;
            }

            void setScore(int score) {
                _score = score;
            }

            int getScore() const {
                return _score;
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
            int _score;
    };
}

BOOST_CLASS_EXPORT_KEY(GameEngine::Score);
