#include "GameEngine.hpp"
#include "Components/Position/Position.hpp"
#include "Components/Health/Health.hpp"

using namespace GameEngine;

int main() {
    Entity player(2); // Create entity of player


    // Create components
    std::shared_ptr<Health> healthComponent = std::make_shared<Health>(1, 3, 100);
    std::shared_ptr<Position> positionComponent = std::make_shared<Position>(2, 4, 1920, 1080);


    // Add components to player
    player.addComponent(healthComponent);
    player.addComponent(positionComponent);


    // Initialize GameEngine
    EntityManager manager;
    manager.addEntity(player);
    Engine r_type(manager);


    // Check value in player's components
    int pos_x = r_type._manager.getEntity(2).get()->getComponentByType<Position>(2).get()->getPosition().first;
    int pos_y = r_type._manager.getEntity(2).get()->getComponentByType<Position>(2).get()->getPosition().second;

    std::cout << "    💜 Player's health: " << std::to_string(r_type._manager.getEntity(2).get()->getComponentByType<Health>(1).get()->getHealth()) << std::endl;
    std::cout << "    --Player's position: " << std::to_string(pos_x) << " " << std::to_string(pos_y)  << std::endl;
    std::cout << "🗡  Player take 33 damages 🗡 " << std::endl;

    // Maybe a future system ?
    r_type._manager.getEntity(2).get()->getComponentByType<Health>(1).get()->setHealth(r_type._manager.getEntity(2).get()->getComponentByType<Health>(1).get()->getHealth() - 33);

    std::cout << "    💜 Player's health: " << std::to_string(r_type._manager.getEntity(2).get()->getComponentByType<Health>(1).get()->getHealth()) << std::endl;
    std::cout << "    --Player's position: " << std::to_string(pos_x) << " " << std::to_string(pos_y)  << std::endl;


    return 0;
}
