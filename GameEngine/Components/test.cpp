#include <boost/serialization/export.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include "Position/Position.hpp"
#include "Health/Health.hpp"
#include "Sprite/Sprite.hpp"
#include "Velocity/Velocity.hpp"
#include "Weapon/Weapon.hpp"
#include "Cooldown/Cooldown.hpp"
#include "HitBoxCircle/HitBoxCircle.hpp"
#include "HitBoxSquare/HitBoxSquare.hpp"
#include "Damage/Damage.hpp"
#include "Team/Team.hpp"
#include "AI/AI.hpp"
#include "Direction/Direction.hpp"
#include "Sound/Sound.hpp"
#include "Camera/Camera.hpp"

BOOST_SERIALIZATION_ASSUME_ABSTRACT(GameEngine::AComponent)
BOOST_CLASS_EXPORT_IMPLEMENT(GameEngine::Health)
BOOST_CLASS_EXPORT_IMPLEMENT(GameEngine::Position)
BOOST_CLASS_EXPORT_IMPLEMENT(GameEngine::Sprite)
BOOST_CLASS_EXPORT_IMPLEMENT(GameEngine::Velocity)
BOOST_CLASS_EXPORT_IMPLEMENT(GameEngine::Weapon)
BOOST_CLASS_EXPORT_IMPLEMENT(GameEngine::AI)
BOOST_CLASS_EXPORT_IMPLEMENT(GameEngine::Cooldown)
BOOST_CLASS_EXPORT_IMPLEMENT(GameEngine::HitBoxCircle)
BOOST_CLASS_EXPORT_IMPLEMENT(GameEngine::HitBoxSquare)
BOOST_CLASS_EXPORT_IMPLEMENT(GameEngine::Damage)
BOOST_CLASS_EXPORT_IMPLEMENT(GameEngine::Direction)
BOOST_CLASS_EXPORT_IMPLEMENT(GameEngine::Team)
BOOST_CLASS_EXPORT_IMPLEMENT(GameEngine::Sound)
BOOST_CLASS_EXPORT_IMPLEMENT(GameEngine::Camera)