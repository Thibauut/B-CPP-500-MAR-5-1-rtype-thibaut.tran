#include "GameEngine.hpp"

using namespace GameEngine;

int main() {
    // 2 PLAYER
    // 3 HEALTH
    Entity player(1); // Create player with id 1
    Entity mob(2); // Create mob with id 2


    // Create components
    std::shared_ptr<Health> healthComponent = std::make_shared<Health>(ListComp::HEALTH, 3, 100);
    std::shared_ptr<Position> positionComponent = std::make_shared<Position>(ListComp::POSITION, 4, 1920, 1080);
    std::shared_ptr<Health> healthComponentMob = std::make_shared<Health>(ListComp::HEALTH, 3, 100);
    std::shared_ptr<Position> positionComponentMob = std::make_shared<Position>(ListComp::POSITION, 4, 1920, 1080);
    std::shared_ptr<AI> aiComponentMob = std::make_shared<AI>(ListComp::AIC, 1);


    // Add components to player
    player.addComponent(healthComponent);
    player.addComponent(positionComponent);
    mob.addComponent(healthComponentMob);
    mob.addComponent(positionComponentMob);
    mob.addComponent(aiComponentMob);


    // Initialize EntityManager
    EntityManager manager;
    manager.addEntity(player); // Add player entity to EntityManager
    manager.addEntity(mob); // Add mob entity to EntityManager

    Engine r_type(manager);
    r_type.run(); // Run game

    return 0;
}
