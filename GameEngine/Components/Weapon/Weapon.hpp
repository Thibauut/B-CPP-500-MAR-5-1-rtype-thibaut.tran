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
                Weapon() : AComponent() {};
                Weapon(CONFIG::CompType type, int id, int posX, int posY, CONFIG::WeaponType weaponType)
                : AComponent(),  _type(type), _idComponent(id), _posX(posX), _posY(posY), _weaponType(weaponType)
                {
                    std::cout << "constructeur weapon dans Weapon.hpp" << std::endl;
                    if (weaponType == CONFIG::WeaponType::Weapon1) {_coolDown = 1.5;}
                    if (weaponType == CONFIG::WeaponType::Weapon2) { _coolDown = 1.5;}
                    if (weaponType == CONFIG::WeaponType::Weapon3){ _coolDown = 0.3;}
                    std::cout << "start du couldown" << std::endl;
                    _coolDown.Start();
                    std::cout << "constructeur weapon dans Weapon.hpp" << std::endl;

                }
                ~Weapon() = default;

                template<class Archive>
                void serialize(Archive & ar, const unsigned int version) {
                    ar.template register_type<Weapon>();
                    ar & boost::serialization::base_object<AComponent>(*this);
                    ar & _idComponent;
                    ar & _type;
                    ar & _posX;
                    ar & _posY;
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

                void setWeapon(CONFIG::WeaponType weaponType, int posX, int posY) {
                    _weaponType = weaponType;
                    _posX = posX;
                    _posY = posY;
                }
                CONFIG::WeaponType getWeaponType(){return _weaponType;}
                virtual CONFIG::CompType getType() {return _type;};
                virtual void setType(const CONFIG::CompType type) {_type = type;};
                virtual int getId() {return _idComponent;};
                virtual void setId(const int id) {_idComponent = id;};

            protected:
                int _idComponent;
                CONFIG::CompType _type;

            private:
                Timeout _coolDown;
                CONFIG::WeaponType _weaponType;
                int _posX;
                int _posY;
        };
    }

    BOOST_CLASS_EXPORT_KEY(GameEngine::Weapon);