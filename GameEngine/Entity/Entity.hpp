/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Entity.hpp
*/

#pragma once
#include <memory>
#include <list>
#include "../Components/AComponent/AComponent.hpp"
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/unique_ptr.hpp>
#include <boost/serialization/array.hpp>
#include "../Utils/Timeout.hpp"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>


using namespace GameEngine;

namespace GameEngine {
    class Entity {
        public:
            Entity() {}
            Entity(unsigned int id, int type) : _id(id), _entityType(type), _isDeath(false) {
                _Destroy.timeout_ = 0.05;
            }

            Entity(int type) : _id(0), _entityType(type), _isDeath(false) {
                _Destroy.timeout_ = 0.05;
            }

            void init() {
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
                // std::cout << "UUID: " << _uuid << std::endl;
            }

            ~Entity() {}

            template <class Archive>
            void serialize(Archive & ar, const unsigned int version) {
                ar & _id;
                ar & _uuid;
                ar & _entityType;
                ar & _entityContent;
                ar & _isDeath;
            }

            bool canDestroy() {
                if (_Destroy.can_execute())
                    return true;
                return false;
            }

            void startDestroy() {
                _Destroy.Start();
            }

            bool DestroyStarted(){return _Destroy.isStarted();}

            unsigned int getId() const {
                return _id;
            }

            std::string getUuid() {
                return _uuid;
            }

            template <typename T>
            void addComponent(T &component) {
                _entityContent.push_back(component);
            }

            template <typename T>
            void deleteComponent(std::shared_ptr<T> component) {
                _entityContent.remove(component);
            }

            template <typename T>
            std::shared_ptr<T> getComponentByType(CONFIG::CompType type) {
                for (auto &component : _entityContent) {
                    if (component.get()->getType() == type)
                        return std::dynamic_pointer_cast<T>(component);
                }
                return nullptr;
            }

            template <typename T>
            std::vector<std::shared_ptr<T>> getComponentsByType(CONFIG::CompType type) {
                std::vector<std::shared_ptr<T>> result;
                for (auto &component : _entityContent) {
                    if (component->getType() == type) {
                        auto derivedComponent = std::dynamic_pointer_cast<T>(component);
                        if (derivedComponent) {
                            result.push_back(derivedComponent);
                        }
                    }
                }
                return result;
            }

            template <typename T>
            std::shared_ptr<T> getComponentById(int id) {
                for (auto &component : _entityContent) {
                    if (component.get()->getId() == id)
                        return component;
                }
                return nullptr;
            }

            template <typename T>
            std::shared_ptr<T> getComponentByUuid(std::string uuid) {
                for (auto &component : _entityContent) {
                    if (component.get()->getUuid() == uuid)
                        return component;
                }
                return nullptr;
            }

            std::list<std::shared_ptr<AComponent>> &getComponents() {
                return _entityContent;
            }

            void setEntityContent(std::list<std::shared_ptr<AComponent>> &entity) {
                _entityContent = entity;
            }

            void setIsDeath(bool status){_isDeath = status;}
            void setType(int type) {_entityType = type;}
            int getType() const {return _entityType;}
            int getIsDeath(){return _isDeath;}
            std::string getUuid() const {return _uuid;}

            void setId(unsigned int id) {
                _id = id;
            }

        private:
            Timeout _Destroy;
            bool _isDeath;
            std::list<std::shared_ptr<AComponent>> _entityContent;
            unsigned int _id;
            int _entityType;
            std::string _uuid;
    };
}