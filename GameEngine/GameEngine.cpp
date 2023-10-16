#include "GameEngine.hpp"
#include "Utils/Utils.hpp"

using namespace GameEngine;

int main() {
    // 2 PLAYER
    // 3 HEALTH
    Entity player(1); // Create player with id 1
    Entity mob(2); // Create mob with id 2


    // Create components
    std::shared_ptr<Health> healthComponent = std::make_shared<Health>(CONFIG::CompType::HEALTH, 3, 100);
    std::shared_ptr<Position> positionComponent = std::make_shared<Position>(CONFIG::CompType::POSITION, 4, 1920, 1080);
    // std::shared_ptr<Direction> directionComponent = std::make_shared<Direction>(CONFIG::CompType::DIRECTION, 36, CONFIG::Dir::DOWN);
    std::shared_ptr<Velocity> velocityComponent = std::make_shared<Velocity>(CONFIG::CompType::VELOCITY, 5, 1);
    // std::shared_ptr<HitBoxCircle> circleHitBoxComponent = std::make_shared<HitBoxCircle>(CONFIG::CompType::HITBOXCIRCLE, 6, 5);
    // std::shared_ptr<HitBoxSquare> squareHitBoxComponent = std::make_shared<HitBoxSquare>(CONFIG::CompType::HITBOXSQUARE, 7, 5, 5);
    std::shared_ptr<Weapon> weaponComponent = std::make_shared<Weapon>(CONFIG::CompType::WEAPON, 8, 5, 5, 5, 5, 5);

    std::shared_ptr<Health> healthComponentMob = std::make_shared<Health>(CONFIG::CompType::HEALTH, 3, 100);
    std::shared_ptr<Position> positionComponentMob = std::make_shared<Position>(CONFIG::CompType::POSITION, 4, 1920, 1080);
    // std::shared_ptr<HitBoxSquare> hitboxComponentMob = std::make_shared<HitBoxSquare>(CONFIG::CompType::HITBOXSQUARE, 5775, 3, 3);
    // std::shared_ptr<AI> aiComponentMob = std::make_shared<AI>(CONFIG::CompType::AI, 1);


    // Add components to player
    player.addComponent(healthComponent);
    player.addComponent(positionComponent);
    // player.addComponent(directionComponent);
    player.addComponent(velocityComponent);
    // player.addComponent(squareHitBoxComponent);

    mob.addComponent(healthComponentMob);
    mob.addComponent(positionComponentMob);
    // mob.addComponent(hitboxComponentMob);

    // mob.addComponent(aiComponentMob);

    // Initialize EntityManager
    EntityManager manager;
    manager.addEntity(player); // Add player entity to EntityManager
    manager.addEntity(mob); // Add mob entity to EntityManager

    Engine r_type(manager);

    // Initialize System
    // std::shared_ptr<SysMovement> mouv_system = std::make_shared<SysMovement>(r_type.getManager());
    // std::shared_ptr<SysRender> render_system = std::make_shared<SysRender>(r_type.getManager());
    // std::shared_ptr<SysCollision> collision_system = std::make_shared<SysCollision>(r_type.getManager());

    // r_type.addSystem(mouv_system);
    // r_type.addSystem(render_system);
    // r_type.addSystem(collision_system);

    r_type.run(); // Run game

    return 0;
}
