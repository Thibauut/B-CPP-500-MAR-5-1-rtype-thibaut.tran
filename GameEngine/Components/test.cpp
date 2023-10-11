#include <boost/serialization/export.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include "Position/Position.hpp"
#include "Health/Health.hpp"
#include "Sprite/Sprite.hpp"
#include "Velocity/Velocity.hpp"
#include "Weapon/Weapon.hpp"

BOOST_SERIALIZATION_ASSUME_ABSTRACT(GameEngine::AComponent)
BOOST_CLASS_EXPORT_IMPLEMENT(GameEngine::Health)
BOOST_CLASS_EXPORT_IMPLEMENT(GameEngine::Position)
BOOST_CLASS_EXPORT_IMPLEMENT(GameEngine::Sprite)
BOOST_CLASS_EXPORT_IMPLEMENT(GameEngine::Velocity)
BOOST_CLASS_EXPORT_IMPLEMENT(GameEngine::Weapon)
