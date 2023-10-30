/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Editor.cpp
*/

#include "Editor.hpp"

Editor::Editor(sf::RenderWindow *window) : _core() {
    EntityManager manager;
    _core._manager = std::make_shared<EntityManager>(manager);
    _core._manager->createEntity();
    Entity my_win;
    Window win(window);
    std::shared_ptr<Window> win_ptr = std::make_shared<Window>(win);
    my_win.addComponent(win_ptr);
    _core._manager->addEntity(my_win);
    loadSprites();
    loadSystems();
    _core.run();
}

Editor::~Editor() {}

// 7, 5, 11, 17

void Editor::loadSprites() {

    std::string assetFolderPath = "/assets/editor";
    int id = 0;
    int id_comp = 0;

    _core.getManager()->createEntity();
    Entity mob1;
    mob1.init();
    std::shared_ptr<Sprite> sprite1Shared = std::make_shared<Sprite>(CONFIG::CompType::SPRITE, 56513);
    Position position1 = Position(CONFIG::CompType::POSITION, 521525, 100, 100);
    sf::IntRect spriteRect1(0, 0, 33, 36);
    sprite1Shared->setSprite(800, 600, "assets/sprites/r-typesheet5.gif", sf::Vector2f(2, 2), spriteRect1, CONFIG::SpriteType::ENEMYSPRITE);
    sprite1Shared->initSprite();
    std::shared_ptr<Position> position1Shared = std::make_shared<Position>(position1);
    mob1.addComponent(position1Shared);
    mob1.addComponent(sprite1Shared);

    Entity mob2;
    mob2.init();
    std::shared_ptr<Sprite> sprite2Shared = std::make_shared<Sprite>(CONFIG::CompType::SPRITE, 58275);
    Position position2 = Position(CONFIG::CompType::POSITION, 0, 300, 100);
    sf::IntRect spriteRect2(0, 0, std::round(33.2), std::round(17.2));
    sprite2Shared->setSprite(position2.getPositionX(), position2.getPositionY(), "assets/editor/r-typesheet7.gif", sf::Vector2f(2, 2), spriteRect2, CONFIG::SpriteType::ENEMYSPRITE);
    sprite2Shared->initSprite();
    std::shared_ptr<Position> position2Shared = std::make_shared<Position>(position2);
    mob2.addComponent(position2Shared);
    mob2.addComponent(sprite2Shared);

    // Entity mob3;
    // mob3.init();
    // Sprite sprite3 = Sprite(CONFIG::CompType::SPRITE, 0);
    // Position position3 = Position(CONFIG::CompType::POSITION, 0, 100, 600);
    // sf::IntRect spriteRect3(0, 0, 33, 34);
    // sprite3.setSprite(position3.getPositionX(), position3.getPositionY(), "assets/editor/r-typesheet11.gif", sf::Vector2f(3, 3), spriteRect3, CONFIG::SpriteType::ENEMYSPRITE);
    // sprite3.setMaxDimensions(100, 100);
    // sprite3.setId(id_comp+=1);
    // sprite3.initSprite();
    // position3.setId(id_comp+=1);
    // std::shared_ptr<Position> position3Shared = std::make_shared<Position>(position3);
    // std::shared_ptr<Sprite> sprite3Shared = std::make_shared<Sprite>(sprite3);
    // mob3.addComponent(position3Shared);
    // mob3.addComponent(sprite3Shared);

    // Entity mob4;
    // mob4.init();
    // Sprite sprite4 = Sprite(CONFIG::CompType::SPRITE, 0);
    // Position position4 = Position(CONFIG::CompType::POSITION, 0, 400, 600);
    // sf::IntRect spriteRect4(0, 0, 65, 66);
    // sprite4.setSprite(position4.getPositionX(), position4.getPositionY(), "assets/editor/r-typesheet17.gif", sf::Vector2f(3, 3), spriteRect4, CONFIG::SpriteType::ENEMYSPRITE);
    // std::cout << "pos x :" << position4.getPositionX() << std::endl;
    // std::cout << "pos y :" << position4.getPositionY() << std::endl;
    // // sprite4.setMaxDimensions(100, 100);
    // sprite4.setId(id_comp+=1);
    // sprite4.initSprite();
    // position4.setId(id_comp+=1);
    // std::shared_ptr<Position> position4Shared = std::make_shared<Position>(position4);
    // std::shared_ptr<Sprite> sprite4Shared = std::make_shared<Sprite>(sprite4);
    // mob4.addComponent(position4Shared);
    // mob4.addComponent(sprite4Shared);

    _core._manager->addEntity(mob1);
    _core._manager->addEntity(mob2);
    // _core._manager->addEntity(mob3);
    // _core._manager->addEntity(mob4);
}

void Editor::loadSystems() {
    _core.addSystem(std::make_shared<SysRenderGlobal>(_core._manager));
    // _core.addSystem(std::make_shared<SysClick>(_core._manager));
}

// int main(int ac, char **av) {

//     //  ENTITYMANAGER   //
//     EntityManager manager;
//     manager.createEntity();


//     //  ENTITY MAP EDITOR   //

//     Entity button;
//     Entity background;

//     Editor editor(manager);
//     return (0);
// }
    // Stocker la window dans une entité avec un component Window

    // Charger les entités nécéssaires (sprites, bouttons, ect.)
    // editor.addEntity();

    // Ajouter les systèmes nécessaires (SysDraw, SysClick, ect.)
    // editor.addSystem(); // <- Ca peut surement aider !