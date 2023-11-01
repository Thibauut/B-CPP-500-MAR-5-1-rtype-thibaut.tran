/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Editor.cpp
*/

#include "Editor.hpp"

namespace fs = std::filesystem;

void drop(Event::event_data &data);
void drag(Event::event_data &data);
void hold(Event::event_data &data);
void drag_and_drop(Event::event_data &data);
bool is_dragging(Event::event_data &data);
bool is_moving(Event::event_data &data);
void move(Event::event_data &data);

Editor::Editor(sf::RenderWindow *window) : _core() {
    EntityManager manager;
    _core._manager = std::make_shared<EntityManager>(manager);
    _core._manager->createEntity();

    Entity my_win;
    Window win(window);
    std::shared_ptr<Window> win_ptr = std::make_shared<Window>(win);
    my_win.addComponent(win_ptr);
    _core._manager->addEntity(my_win);

    // Entity button_create_map;
    // std::shared_ptr<Position> create_map_pos  = std::make_shared<Position>(CONFIG::CompType::POSITION, 0, 500, 600);
    // std::shared_ptr<HitBoxSquare> rectangle_create_map = std::make_shared<HitBoxSquare>(CONFIG::CompType::HITBOXSQUARE, 64, sf::IntRect(0, 0, 300, 200));
    // std::shared_ptr<Event> event_create_map = std::make_shared<Event>(Event::event_config{is_dragging, action_drag});
    // button_create_map.addComponent(create_map_pos);
    // button_create_map.addComponent(rectangle_create_map);
    // button_create_map.addComponent(event_create_map);
    // _core._manager->addEntity(button_create_map);

    // Entity button_load_map;

    // std::shared_ptr<Position> load_map_pos  = std::make_shared<Position>(CONFIG::CompType::POSITION, 0, 1100, 600);
    // std::shared_ptr<HitBoxSquare> rectangle_load_map = std::make_shared<HitBoxSquare>(CONFIG::CompType::HITBOXSQUARE, 64, sf::IntRect(0, 0, 300, 200));
    // button_load_map.addComponent(load_map_pos);
    // button_load_map.addComponent(rectangle_load_map);
    // _core._manager->addEntity(button_load_map);

    Entity editor(550, 7);
    std::shared_ptr<Position> camera_pos = std::make_shared<Position>(CONFIG::CompType::POSITION, 0, 0, 0);
    std::shared_ptr<Camera> camera_ptr = std::make_shared<Camera>(550);
    std::shared_ptr<HitBoxSquare> rectangle_editor = std::make_shared<HitBoxSquare>(CONFIG::CompType::HITBOXSQUARE, 64, sf::IntRect(0, 0, 1300, 1000));
    std::shared_ptr<Event> eventCameraMoveShared = std::make_shared<Event>(Event::event_config{is_moving, move});
    editor.addComponent(camera_ptr);
    editor.addComponent(camera_pos);
    editor.addComponent(rectangle_editor);
    editor.addComponent(eventCameraMoveShared);
    _core._manager->addEntity(editor);

    loadGUI();
    loadPalette();
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
    //      LEAVE        //
    Entity buttonLeave;
    buttonLeave.init();
    std::shared_ptr<Sprite> spriteButtonLeaveShared = std::make_shared<Sprite>(CONFIG::CompType::SPRITE, 58978);
    std::shared_ptr<Position> positionButtonLeaveShared = std::make_shared<Position>(CONFIG::CompType::POSITION, 0, 500, 500);
    Event::event_config config;
    // config.isActive = ; // Ton activation d'event qui return true / false
    // config.action = ; // Ton event
    std::shared_ptr<Event> eventButtonLeaveShared = std::make_shared<Event>(config);
    sf::IntRect spriteRectButton(0, 0, 300, 100);
    spriteButtonLeaveShared->setSprite(positionButtonLeaveShared->getPositionX(), positionButtonLeaveShared->getPositionY(), "assets/editor/leaveButton.png", sf::Vector2f(1, 1), spriteRectButton, CONFIG::SpriteType::BUTTON);
    spriteButtonLeaveShared->setMaxDimensions(300, 100);
    spriteButtonLeaveShared->initSprite();
    buttonLeave.addComponent(positionButtonLeaveShared);
    buttonLeave.addComponent(spriteButtonLeaveShared);
    // buttonLeave.addComponent(eventButtonLeaveShared);
    //      LOAD        //
    Entity buttonLoad;
    buttonLoad.init();
    std::shared_ptr<Sprite> spriteButtonLoadShared = std::make_shared<Sprite>(CONFIG::CompType::SPRITE, 59998);
    std::shared_ptr<Position> positionButtonLoadShared = std::make_shared<Position>(CONFIG::CompType::POSITION, 59886, 500, 800);
    sf::IntRect spriteRectButton2(0, 0, 300, 100);
    spriteButtonLoadShared->setSprite(positionButtonLoadShared->getPositionX(), positionButtonLoadShared->getPositionY(), "assets/editor/loadButton.png", sf::Vector2f(1, 1), spriteRectButton2, CONFIG::SpriteType::BUTTON);
    spriteButtonLoadShared->setMaxDimensions(300, 100);
    spriteButtonLoadShared->initSprite();
    //      SAVE        //
    Entity buttonSave;
    buttonSave.init();
    std::shared_ptr<Sprite> spriteButtonSaveShared = std::make_shared<Sprite>(CONFIG::CompType::SPRITE, 56668);
    std::shared_ptr<Position> positionButtonSaveShared = std::make_shared<Position>(CONFIG::CompType::POSITION, 0, 500, 1100);
    sf::IntRect spriteRectButton3(0, 0, 300, 100);
    spriteButtonSaveShared->setSprite(positionButtonSaveShared->getPositionX(), positionButtonSaveShared->getPositionY(), "assets/editor/saveButton.png", sf::Vector2f(1, 1), spriteRectButton3, CONFIG::SpriteType::BUTTON);
    spriteButtonSaveShared->setMaxDimensions(300, 100);
    spriteButtonSaveShared->initSprite();



    _core._manager->addEntity(buttonLeave);
    _core._manager->addEntity(buttonLoad);
    _core._manager->addEntity(buttonSave);

}

void Editor::loadSprites() {

}

void Editor::loadPalette() {

    std::string assetFolderPath = "/assets/entities";
    int id = 0;
    int id_comp = 0;
    int x = 1515, y = 440;
    int count = 0, count_y = 0;
    fs::path currentDir = fs::current_path();
    assetFolderPath = currentDir.string() + assetFolderPath;
    for (const auto & entry : fs::directory_iterator(assetFolderPath)) {
        y = 440 + (210 * count_y);
        if ((count % 2) == 0)
            x = 1515;
        else {
            x = 1710;
            y += 1;
        }
        count += 1;
        std::ifstream input_file(entry.path().c_str());
        nlohmann::json entity_json;
        input_file >> entity_json;
        input_file.close();
        Entity mob;
        mob.init();
        std::shared_ptr<Sprite> sprite1Shared = std::make_shared<Sprite>(CONFIG::CompType::SPRITE, 56513);
        Position position1 = Position(CONFIG::CompType::POSITION, 521525, 1550, 650);
        sf::IntRect spriteRect1(entity_json["rectangle"]["left"], entity_json["rectangle"]["top"], entity_json["rectangle"]["width"], entity_json["rectangle"]["height"]);
        sprite1Shared->setSprite(x, y, entity_json["sprite"], sf::Vector2f(4, 4), spriteRect1, CONFIG::SpriteType::ENEMYSPRITE);
        sprite1Shared->initSprite();
        std::shared_ptr<Position> position1Shared = std::make_shared<Position>(position1);
        std::shared_ptr<Draggable> draggable1Shared = std::make_shared<Draggable>(CONFIG::CompType::DRAGGABLE);
        Event::event_config config_event;
        config_event.isActive = is_dragging;
        config_event.action = drag_and_drop;
        std::shared_ptr<Event> eventShared = std::make_shared<Event>(config_event);
        mob.addComponent(position1Shared);
        mob.addComponent(sprite1Shared);
        mob.addComponent(draggable1Shared);
        mob.addComponent(eventShared);
        _core._manager->addEntity(mob);
    }
}

void Editor::loadSystems() {
    _core.addSystem(std::make_shared<SysRenderGlobal>(_core._manager));
    _core.addSystem(std::make_shared<SysPollEvent>(_core._manager));
    _core.addSystem(std::make_shared<SysCameraEditor>(_core._manager));
}

bool is_dragging(Event::event_data &data) {
    std::shared_ptr<Draggable> draggable = data.entity->getComponentByType<Draggable>(CONFIG::CompType::DRAGGABLE);
    std::shared_ptr<Sprite> sprite = data.entity->getComponentByType<Sprite>(CONFIG::CompType::SPRITE);
    if (draggable != nullptr && sprite != nullptr) {
        if (draggable->isBeingDragged())
            return true;
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

void drag_and_drop(Event::event_data &data) {
    std::shared_ptr<Draggable> draggable = data.entity->getComponentByType<Draggable>(CONFIG::CompType::DRAGGABLE);
    std::shared_ptr<Sprite> sprite = data.entity->getComponentByType<Sprite>(CONFIG::CompType::SPRITE);
    if (data.event->type == sf::Event::MouseButtonReleased && draggable->isBeingDragged())
        drop(data);
    if (draggable->isBeingDragged()) {
        hold(data);
        return;
    }
    if (data.event->type == sf::Event::MouseButtonPressed)
        drag(data);
}

void drag(Event::event_data &data) {
    std::shared_ptr<Draggable> draggable = data.entity->getComponentByType<Draggable>(CONFIG::CompType::DRAGGABLE);
    std::shared_ptr<Sprite> sprite = data.entity->getComponentByType<Sprite>(CONFIG::CompType::SPRITE);
    Entity entity_dragged(50, 30);
    entity_dragged.init();
    Sprite sp(CONFIG::CompType::SPRITE, 59878);
    std::shared_ptr<Sprite> spriteShared = std::make_shared<Sprite>(sp);
    spriteShared->setSprite(sprite->getSprite());
    entity_dragged.addComponent(spriteShared);
    data.entity_manager->addEntity(entity_dragged);
    draggable->startDragging();
    draggable->setEntityDragged(data.entity_manager->getEntityById(50)->getUuid());
}

void hold(Event::event_data &data) {
    std::shared_ptr<Draggable> draggable = data.entity->getComponentByType<Draggable>(CONFIG::CompType::DRAGGABLE);
    std::shared_ptr<Sprite> sprite = data.entity->getComponentByType<Sprite>(CONFIG::CompType::SPRITE);
    std::shared_ptr<Entity> entity = data.entity_manager->getEntity(draggable->getEntityDragged());
    std::shared_ptr<Sprite> sprite_dragged = entity->getComponentByType<Sprite>(CONFIG::CompType::SPRITE);
    sf::IntRect rect = sprite->getRect();
    sprite_dragged->setPositionSprite(sf::Vector2f(data.mouse.x - ((rect.width * 4) / 2), data.mouse.y - ((rect.height * 4) / 2)));
}

void drop(Event::event_data &data) {
    std::shared_ptr<Draggable> draggable = data.entity->getComponentByType<Draggable>(CONFIG::CompType::DRAGGABLE);

    std::shared_ptr<Entity> editor = data.entity_manager->getEntityById(550);
    std::shared_ptr<Camera> camera = editor->getComponentByType<Camera>(CONFIG::CompType::CAMERA);
    std::shared_ptr<HitBoxSquare> hitbox_c = editor->getComponentByType<HitBoxSquare>(CONFIG::CompType::HITBOXSQUARE);

    sf::IntRect hitbox = hitbox_c->getRectangle();
    if (hitbox.contains(data.mouse)) {
        std::shared_ptr<Entity> entity = data.entity_manager->getEntity(draggable->getEntityDragged());
        Entity new_entity;
        new_entity.init();
        Sprite sp(CONFIG::CompType::SPRITE, 59912);
        std::shared_ptr<Sprite> sprite = entity->getComponentByType<Sprite>(CONFIG::CompType::SPRITE);
        std::shared_ptr<Sprite> spriteShared = std::make_shared<Sprite>(sp);
        spriteShared->setSprite(sprite->getSprite());
        int editor_x = editor->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionX();
        editor_x = data.mouse.x + editor_x;
        std::shared_ptr<Position> positionShared = std::make_shared<Position>(CONFIG::CompType::POSITION, 231865, editor_x, data.mouse.y);
        new_entity.addComponent(spriteShared);
        new_entity.addComponent(positionShared);
        camera->push(new_entity);
    }
    data.entity_manager->deleteEntity(draggable->getEntityDragged());
    draggable->stopDragging();
    draggable->setEntityDragged("");
}

bool is_moving(Event::event_data &data) {
    if (data.event->type == sf::Event::KeyPressed) {
        if (data.event->key.code == sf::Keyboard::Left)
            return true;
        if (data.event->key.code == sf::Keyboard::Right)
            return true;
    }
    return false;
}

void move(Event::event_data &data) {
    std::shared_ptr<Position> position = data.entity->getComponentByType<Position>(CONFIG::CompType::POSITION);
    if (data.event->key.code == sf::Keyboard::Left)
        position->setPositionX(position->getPositionX() - 10);
    if (data.event->key.code == sf::Keyboard::Right)
        position->setPositionX(position->getPositionX() + 10);
}