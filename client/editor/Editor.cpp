/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Editor.cpp
*/

#include "Editor.hpp"

void action_drag(Event::data_event &data);
bool is_dragging(Event::data_event &data);

Editor::Editor(sf::RenderWindow *window) : _core() {
    EntityManager manager;
    _core._manager = std::make_shared<EntityManager>(manager);
    _core._manager->createEntity();

    Entity my_win;
    Window win(window);
    std::shared_ptr<Window> win_ptr = std::make_shared<Window>(win);
    my_win.addComponent(win_ptr);
    _core._manager->addEntity(my_win);

    Entity button_create_map;
    
    std::shared_ptr<Position> create_map_pos  = std::make_shared<Position>(CONFIG::CompType::POSITION, 0, 500, 600);
    std::shared_ptr<HitBoxSquare> rectangle_create_map = std::make_shared<HitBoxSquare>(CONFIG::CompType::HITBOXSQUARE, 64, sf::IntRect(0, 0, 300, 200));
    std::shared_ptr<Event> event_create_map = std::make_shared<Event>(Event::config_event{is_dragging, action_drag});
    button_create_map.addComponent(create_map_pos);
    button_create_map.addComponent(rectangle_create_map);
    button_create_map.addComponent(event_create_map);
    _core._manager->addEntity(button_create_map);

    Entity button_load_map;

    std::shared_ptr<Position> load_map_pos  = std::make_shared<Position>(CONFIG::CompType::POSITION, 0, 1100, 600);
    std::shared_ptr<HitBoxSquare> rectangle_load_map = std::make_shared<HitBoxSquare>(CONFIG::CompType::HITBOXSQUARE, 64, sf::IntRect(0, 0, 300, 200));
    button_load_map.addComponent(load_map_pos);
    button_load_map.addComponent(rectangle_load_map);
    _core._manager->addEntity(button_load_map);

    Entity editor;
    std::shared_ptr<Position> camera_pos = std::make_shared<Position>(CONFIG::CompType::POSITION, 0, 0, 0);
    std::shared_ptr<Camera> camera_ptr = std::make_shared<Camera>(50);
    std::shared_ptr<HitBoxSquare> rectangle_editor = std::make_shared<HitBoxSquare>(CONFIG::CompType::HITBOXSQUARE, 64, sf::IntRect(0, 0, 1700, 700));
    editor.addComponent(camera_ptr);
    editor.addComponent(camera_pos);
    editor.addComponent(rectangle_editor);
    _core._manager->addEntity(editor);

    loadGUI();
    loadSprites();
    loadSystems();
    _core.run();
}

Editor::~Editor() {}

// 7, 5, 11, 17

void Editor::loadGUI() {
    Entity interface1;
    interface1.init();
    std::shared_ptr<Sprite> spriteInterShared = std::make_shared<Sprite>(CONFIG::CompType::SPRITE, 57854);
    std::shared_ptr<Position> positionInterShared = std::make_shared<Position>(CONFIG::CompType::POSITION, 0, 0, 0);
    sf::IntRect spriteRectInter(0, 0, 1920, 1080);
    spriteInterShared->setSprite(positionInterShared->getPositionX(), positionInterShared->getPositionY(), "assets/editor/gui/gui2.png", sf::Vector2f(1, 1), spriteRectInter, CONFIG::SpriteType::GUI);
    spriteInterShared->setMaxDimensions(1920, 1080);
    spriteInterShared->initSprite();
    interface1.addComponent(positionInterShared);
    interface1.addComponent(spriteInterShared);

    _core._manager->addEntity(interface1);

}

void Editor::loadButtonGUI() {
    //      HOME        //
    Entity buttonHome;
    buttonHome.init();
    std::shared_ptr<Sprite> spriteButtonHomeShared = std::make_shared<Sprite>(CONFIG::CompType::SPRITE, 58978);
    std::shared_ptr<Position> positionButtonHomeShared = std::make_shared<Position>(CONFIG::CompType::POSITION, 0, 500, 500);
    sf::IntRect spriteRectButton(0, 0, 200, 200);
    spriteButtonHomeShared->setSprite(positionButtonHomeShared->getPositionX(), positionButtonHomeShared->getPositionY(), "assets/editor/homeButton.png", sf::Vector2f(1, 1), spriteRectButton, CONFIG::SpriteType::BUTTON);
    spriteButtonHomeShared->setMaxDimensions(200, 200);
    spriteButtonHomeShared->initSprite();
    buttonHome.addComponent(positionButtonHomeShared);
    buttonHome.addComponent(spriteButtonHomeShared);
    //      

    _core._manager->addEntity(buttonHome);

}

void Editor::loadSprites() {

    std::string assetFolderPath = "/assets/editor";
    int id = 0;
    int id_comp = 0;

    Entity mob1;
    mob1.init();
    std::shared_ptr<Sprite> sprite1Shared = std::make_shared<Sprite>(CONFIG::CompType::SPRITE, 56513);
    Position position1 = Position(CONFIG::CompType::POSITION, 521525, 1550, 650);
    sf::IntRect spriteRect1(0, 0, 33, 36);
    sprite1Shared->setSprite(1550, 650, "assets/sprites/r-typesheet5.gif", sf::Vector2f(4, 4), spriteRect1, CONFIG::SpriteType::ENEMYSPRITE);
    sprite1Shared->initSprite();
    std::shared_ptr<Position> position1Shared = std::make_shared<Position>(position1);
    std::shared_ptr<Draggable> draggable1Shared = std::make_shared<Draggable>(CONFIG::CompType::DRAGGABLE);
    Event::config_event config_event;
    config_event.isActivate = is_dragging;
    config_event.action = action_drag;
    std::shared_ptr<Event> eventShared = std::make_shared<Event>(config_event);
    mob1.addComponent(position1Shared);
    mob1.addComponent(sprite1Shared);
    mob1.addComponent(draggable1Shared);
    mob1.addComponent(eventShared);

    Entity mob2;
    mob2.init();
    std::shared_ptr<Sprite> sprite2Shared = std::make_shared<Sprite>(CONFIG::CompType::SPRITE, 58275);
    Position position2 = Position(CONFIG::CompType::POSITION, 0, 1750, 650);
    sf::IntRect spriteRect2(0, 0, std::round(33.2), std::round(17.2));
    sprite2Shared->setSprite(position2.getPositionX(), position2.getPositionY(), "assets/editor/r-typesheet7.gif", sf::Vector2f(4, 4), spriteRect2, CONFIG::SpriteType::ENEMYSPRITE);
    sprite2Shared->initSprite();
    Event::config_event config_event2;
    config_event2.isActivate = is_dragging;
    config_event2.action = action_drag;
    std::shared_ptr<Event> eventShared2 = std::make_shared<Event>(config_event2);
    std::shared_ptr<Position> position2Shared = std::make_shared<Position>(position2);
    std::shared_ptr<Draggable> draggable2Shared = std::make_shared<Draggable>(CONFIG::CompType::DRAGGABLE);
    mob2.addComponent(position2Shared);
    mob2.addComponent(sprite2Shared);
    mob2.addComponent(draggable2Shared);
    mob2.addComponent(eventShared2);

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
    _core.addSystem(std::make_shared<SysDrag>(_core._manager));
    _core.addSystem(std::make_shared<SysPollEvent>(_core._manager));
    // _core.addSystem(std::make_shared<SysClick>(_core._manager));
}

bool is_dragging(Event::data_event &data) {
        std::shared_ptr<Draggable> draggable = data.entity->getComponentByType<Draggable>(CONFIG::CompType::DRAGGABLE);
        std::shared_ptr<Sprite> sprite = data.entity->getComponentByType<Sprite>(CONFIG::CompType::SPRITE);
    if (draggable != nullptr && sprite != nullptr) {
        if (data.event->type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mousePosF(static_cast<float>(data.mouse.x), static_cast<float>(data.mouse.y));
            if (sprite->getSprite().getGlobalBounds().contains(mousePosF) && !draggable->isBeingDragged())
                return true;
        }
        if (data.event->type == sf::Event::MouseButtonReleased && draggable->isBeingDragged())
            return true;
    }
    return false;
}

void action_drag(Event::data_event &data) {
    std::shared_ptr<Draggable> draggable = data.entity->getComponentByType<Draggable>(CONFIG::CompType::DRAGGABLE);
    std::shared_ptr<Sprite> sprite = data.entity->getComponentByType<Sprite>(CONFIG::CompType::SPRITE);
    if (data.event->type == sf::Event::MouseButtonPressed) {
        Entity entity_dragged(50, 30);
        entity_dragged.init();
        Sprite sp(CONFIG::CompType::SPRITE, 59878);
        std::shared_ptr<Sprite> spriteShared = std::make_shared<Sprite>(sp);
        spriteShared->setSprite(sprite->getSprite());
        entity_dragged.addComponent(spriteShared);
        data.entityManager->addEntity(entity_dragged);
        draggable->startDragging();
        draggable->setEntityDragged(data.entityManager->getEntityById(50)->getUuid());
    }
    if (data.event->type == sf::Event::MouseButtonReleased) {
    // if (event.mouseButton.button == sf::Mouse::Left) {
        if (!draggable->isBeingDragged())
            return;
        draggable->stopDragging();
        data.entityManager->deleteEntity(draggable->getEntityDragged());
        draggable->setEntityDragged("");
    }
    // }
}