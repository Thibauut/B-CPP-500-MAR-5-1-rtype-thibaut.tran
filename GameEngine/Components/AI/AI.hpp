/*
** EPITECH PROJECT, 2023
** AI
** File description:
** AI
*/

#pragma once
#include "../AComponent/AComponent.hpp"
#include <boost/serialization/unique_ptr.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/export.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <chrono>
#include "../../Utils/Timeout.hpp"

namespace GameEngine {

    class AI : public AComponent {
        public:
            friend class boost::serialization::access;
            friend class AComponent;
            AI() : AComponent(), _moveCooldown(100) {
                _moveCooldown.Start();
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
            };
            AI(CONFIG::CompType type, CONFIG::AiType aiType, int id, float couldown) : _moveCooldown(couldown), _idComponent(id), _type(type), _aiType(aiType), _couldown(couldown), _activate(false) {
                _moveCooldown.Start();
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
            }
            ~AI() = default;

            void setAIActive(bool activate) {
                _activate = activate;
                std::cout << "AI setter: active = " << (_activate ? "true" : "false") << std::endl;
            }

            bool isAIactive() const {
                std::cout << "AI getter : state = " << _activate << std::endl;
                return _activate;
            }

            template<class Archive>
            void serialize(Archive & ar, const unsigned int version) {
                ar.template register_type<AI>();
                ar & boost::serialization::base_object<AComponent>(*this);
                // ar & _uuid;
                ar & _idComponent;
                ar & _type;
            }

            bool canMove() {
                if (_moveCooldown.can_execute()) {
                    _moveCooldown.Start();
                    return true;
                }
                return false;
            }

            void resetCooldown() {
                _moveCooldown.Start();
            }

            virtual CONFIG::CompType getType() {return _type;};
            virtual void setType(const CONFIG::CompType type) {_type = type;};
            virtual int getId() {return _idComponent;};
            virtual void setId(const int id) {_idComponent = id;};
            virtual std::string getUuid() {return _uuid;};
            CONFIG::AiType getAiType() {return _aiType;};
            void setAiType(const CONFIG::AiType aiType) {_aiType = aiType;};
            float getCouldown() {return _couldown;};

            bool _stateMobOneX = false;
            bool _stateMobOneY = false;

            bool _setSpawn = false;
            int _spawnX = 0;
            int _spawnY = 0;

        protected:
            int _idComponent;
            CONFIG::CompType _type;
            CONFIG::AiType _aiType;
            float _couldown;
            std::string _uuid;

        private:
            Timeout _moveCooldown;
            bool _activate;
            // bool isAI_;
    };
}
BOOST_CLASS_EXPORT_KEY(GameEngine::AI);
