/*
** EPITECH PROJECT, 2023
** SOUND-BRANCH
** File description:
** Sound
*/

#pragma once

#include "../../Components/AComponent/AComponent.hpp"
#include <SFML/Audio.hpp>

namespace GameEngine {
    class Sound : public AComponent {
        public:
            friend class boost::serialization::access;
            friend class AComponent;
            Sound() : AComponent() {
                _idComponent = 0;
                _type = CONFIG::CompType::SOUND;
                _soundPath = "";
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
            }
            Sound(CONFIG::CompType type, int id, std::string soundPath)
            : AComponent(), _type(type), _idComponent(id), _soundPath(soundPath) {
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
            }
            Sound(const Sound& other) {
                _idComponent = other._idComponent;
                _type = other._type;
                _soundPath = other._soundPath;
                _uuid = other._uuid;
            }
            ~Sound() = default;

            template<class Archive>
            void serialize(Archive & ar, const unsigned int version) {
                ar.template register_type<Sound>();
                ar & boost::serialization::base_object<AComponent>(*this);
                ar & _idComponent;
                // ar & _uuid;
                ar & _type;
                ar & _soundPath;
            }

            void setSoundPath(std::string soundPath) {
                _soundPath = soundPath;
            }

            std::string getSoundPath() {
                return _soundPath;
            }

            sf::Music& getSound() {
                return _sound;
            }

            void playSound() {
                _sound.openFromFile(_soundPath);
                _sound.play();
                _sound.setVolume(3);
                _sound.setLoop(false);
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
            std::string _soundPath;
            sf::Music _sound;
    };
}

BOOST_CLASS_EXPORT_KEY(GameEngine::Sound);