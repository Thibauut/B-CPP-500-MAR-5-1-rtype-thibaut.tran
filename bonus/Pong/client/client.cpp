/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** main.cpp
*/

#include <iostream>
#include <thread>
#include <atomic>

#include "../../../client/graphical/menu/anim.cpp"
#include "../../../client/graphical/menu/handle_events.cpp"
#include "../../../client/graphical/menu/handle_tcp_events.cpp"
#include "../../../client/graphical/menu/init.cpp"
#include "../../../client/graphical/menu.cpp"
#include "../../../client/graphical/menu/tcp_func.cpp"
#include "include/game.hpp"
#include "client.hpp"

int main(int ac, char **av)
{
    Client *client = new Client();
    // EntityManager manager;
    EntityManager manager;
    Engine engine = Engine(manager);
    std::shared_ptr<Engine> sharedEngine = std::make_shared<Engine>(engine);
    std::shared_ptr<AGame> sharedGame = std::make_shared<GamePong>(sharedEngine);

    //Menu entity
    client->gameEngine_._manager->createEntity();
    Entity entity = Entity(1, 1);
    entity.init();

    //Menu component
    MenuComp menu = MenuComp(CONFIG::CompType::MENU, 1, 1, "assets/fonts/WANTONE.otf", "assets/images/bgPong.png", "", "PONG", sharedGame);
    std::shared_ptr<MenuComp> menuPtr = std::make_shared<MenuComp>(menu);
    entity.addComponent(menuPtr);
    client->gameEngine_._manager->addEntity(entity);

    client->gameEngine_.addSystem(std::make_shared<SysRender>(client->gameEngine_.getManager(), CONFIG::Interfaces::MENUDRAW));
    client->gameEngine_.run();

    return 0;
}
