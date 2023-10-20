/*
** EPITECH PROJECT, 2023
** Weapon
** File description:
** Weapon
*/

#pragma once
    #include "../AComponent/AComponent.hpp"
    #include "../../Utils/Timeout.hpp"
    #include "../../Utils/Utils.hpp"

    namespace GameEngine {

        class Weapon : public AComponent {
            public:
                friend class boost::serialization::access;
                friend class AComponent;
                Weapon() : AComponent() {
                    _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
                };
                Weapon(CONFIG::CompType type, int id)
                : AComponent(),  _type(type), _idComponent(id), _weaponType(CONFIG::Weapon1) {
                    _coolDown = 1.5;
                    _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
                }
                Weapon(CONFIG::CompType type, int id, CONFIG::WeaponType weaponType)
                : AComponent(),  _type(type), _idComponent(id), _weaponType(weaponType)
                {
                    _isShooting = false;
                    if (weaponType == CONFIG::WeaponType::Weapon1) {_coolDown = 1.5;}
                    if (weaponType == CONFIG::WeaponType::Weapon2) { _coolDown = 2.5;}
                    if (weaponType == CONFIG::WeaponType::Weapon3){ _coolDown = 0.2;}
                    _coolDown.Start();
                    _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
                }
                ~Weapon() = default;

                template<class Archive>
                void serialize(Archive & ar, const unsigned int version) {
                    ar.template register_type<Weapon>();
                    ar & boost::serialization::base_object<AComponent>(*this);
                    ar & _idComponent;
                    // ar & _uuid;
                    ar & _type;
                    ar & _isShooting;
                    ar & _timePressed;
                }

                bool canShoot()
                {
                    if (_coolDown.can_execute()) {
                        _coolDown.Start();
                        return true;
                    }
                    return false;
                }

                void resetCooldown() {
                    _coolDown.Start();
                }

                Timeout getCoolDown() {
                    return _coolDown;
                }

                bool getIsShooting() {
                    return _isShooting;
                }

                double getTimePressed() {
                    return _timePressed;
                }

                void setWeapon(CONFIG::WeaponType weaponType) {
                    _weaponType = weaponType;
                }
                void setWeaponWithString(std::string weaponType) {
                    if (weaponType == "Weapon1") {
                        _weaponType = CONFIG::WeaponType::Weapon1;
                        _coolDown = 1.5;
                        return;
                    }
                    if (weaponType == "Weapon2") {
                        _weaponType = CONFIG::WeaponType::Weapon2;
                        _coolDown = 2.5;
                        return;
                    }
                    if (weaponType == "Weapon3") {
                        _weaponType = CONFIG::WeaponType::Weapon3;
                        _coolDown = 0.2;
                        return;
                    }
                }

                void setShooting(bool isShooting, double timePressed) {
                    _isShooting = isShooting;
                    _timePressed = timePressed;
                }

                CONFIG::WeaponType getWeaponType(){return _weaponType;}
                virtual CONFIG::CompType getType() {return _type;};
                virtual void setType(const CONFIG::CompType type) {_type = type;};
                virtual int getId() {return _idComponent;};
                virtual void setId(const int id) {_idComponent = id;};
                virtual std::string getUuid() {return _uuid;};

            protected:
                int _idComponent;
                CONFIG::CompType _type;
                bool _isShooting;
                double _timePressed;
                std::string _uuid;

            private:
                Timeout _coolDown;
                CONFIG::WeaponType _weaponType;
        };
    }

    BOOST_CLASS_EXPORT_KEY(GameEngine::Weapon);