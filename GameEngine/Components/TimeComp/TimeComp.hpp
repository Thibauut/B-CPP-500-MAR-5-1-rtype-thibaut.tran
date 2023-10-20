/*
** EPITECH PROJECT, 2023
** TimeComp
** File description:
** Timeout
*/

#pragma once
    #include "../AComponent/AComponent.hpp"
    #include "../../Utils/Timeout.hpp"
    #include "../../Utils/Utils.hpp"

    namespace GameEngine {

        class TimeComp : public AComponent {
            public:
                friend class boost::serialization::access;
                friend class AComponent;
                TimeComp() : AComponent() {
                    _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
                };
                TimeComp(CONFIG::CompType type, int id)
                : AComponent(),  _type(type), _idComponent(id) {
                    // _coulDown.timeout_ = timeout_value;
                    // _coulDown.Start();
                    _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
                }
                ~TimeComp() = default;

                template<class Archive>
                void serialize(Archive & ar, const unsigned int version) {
                    ar.template register_type<TimeComp>();
                    ar & boost::serialization::base_object<AComponent>(*this);
                    // ar & _uuid;
                    ar & _idComponent;
                    ar & _type;
                }

                void create_new_coulDown(double new_value, std::string name)
                {
                      for (auto &_coulDown : _timeout) {
                        if (_coulDown._name == name)
                            return;
                    }
                    Timeout new_couldown = Timeout(new_value);
                    new_couldown._name = name;
                    _timeout.push_back(new_couldown);
                }

                bool couldown_is_finish(std::string name)
                {
                    for (auto &_coulDown : _timeout) {
                        if (_coulDown._name == name) {
                            if (_coulDown.can_execute())
                                return true;
                        }
                    }
                    return false;
                }

                void reset_couldown(std::string name) {
                    for (auto &_coulDown : _timeout) {
                        if (_coulDown._name == name)
                            _coulDown.Start();
                    }
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
                std::vector<Timeout> _timeout;
        };
    }

    BOOST_CLASS_EXPORT_KEY(GameEngine::TimeComp);