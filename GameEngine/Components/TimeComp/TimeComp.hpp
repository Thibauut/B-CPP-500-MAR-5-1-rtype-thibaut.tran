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
                TimeComp() : AComponent() {};
                TimeComp(CONFIG::CompType type, int id, double timeout_value)
                : AComponent(),  _type(type), _idComponent(id) {
                    _coulDown.timeout_ = timeout_value;
                    _coulDown.Start();
                }
                ~TimeComp() = default;

                template<class Archive>
                void serialize(Archive & ar, const unsigned int version) {
                    ar.template register_type<TimeComp>();
                    ar & boost::serialization::base_object<AComponent>(*this);
                    ar & _idComponent;
                    ar & _type;
                    // ar &_coulDown;
                }

                bool couldown_is_finish()
                {
                    if (_coulDown.can_execute())
                        return true;
                    return false;
                }

                void reset_couldown() {
                    _coulDown.Start();
                }

                void set_new_coulDown(double new_value)
                {
                    _coulDown.timeout_ = new_value;
                }

                virtual CONFIG::CompType getType() {return _type;};
                virtual void setType(const CONFIG::CompType type) {_type = type;};
                virtual int getId() {return _idComponent;};
                virtual void setId(const int id) {_idComponent = id;};

            protected:
                int _idComponent;
                CONFIG::CompType _type;

            private:
                Timeout _coulDown;
        };
    }

    BOOST_CLASS_EXPORT_KEY(GameEngine::TimeComp);