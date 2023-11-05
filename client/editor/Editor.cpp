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
bool is_clicked(Event::event_data &data);
void save(Event::event_data &data);
void load(Event::event_data &data);
void leave(Event::event_data &data);
void select_element(Event::event_data &data);
bool is_selected(Event::event_data &data);
void move_element(Event::event_data &data);
bool is_selected_and_pressed(Event::event_data &data);

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
    loadButtonGUI();
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
    Event::event_config config1;
    config1.isActive = is_clicked; // Ton activation d'event qui return true / false
    config1.action = leave; // Ton event
    std::shared_ptr<Event> eventClick1 = std::make_shared<Event>(config1);
    std::shared_ptr<HitBoxSquare> rectangle_load1 = std::make_shared<HitBoxSquare>(CONFIG::CompType::HITBOXSQUARE, 64, sf::IntRect(0, 0, 300, 100));
    std::shared_ptr<Sprite> spriteButtonLeaveShared = std::make_shared<Sprite>(CONFIG::CompType::SPRITE, 58978);
    std::shared_ptr<Position> positionButtonLeaveShared = std::make_shared<Position>(CONFIG::CompType::POSITION, 0, 1750, 100);
    sf::IntRect spriteRectButton(0, 0, 300, 100);
    spriteButtonLeaveShared->setSprite(positionButtonLeaveShared->getPositionX(), positionButtonLeaveShared->getPositionY(), "assets/editor/gui/leaveButton.png", sf::Vector2f(0.45, 0.45), spriteRectButton, CONFIG::SpriteType::BUTTON);
    spriteButtonLeaveShared->setMaxDimensions(150, 50);
    spriteButtonLeaveShared->initSprite();
    buttonLeave.addComponent(positionButtonLeaveShared);
    buttonLeave.addComponent(spriteButtonLeaveShared);
    buttonLeave.addComponent(eventClick1);
    buttonLeave.addComponent(rectangle_load1);
    //      LOAD        //
    Entity buttonLoad;
    buttonLoad.init();
    Event::event_config config2;
    config2.isActive = is_clicked;
    config2.action = save; //
    std::shared_ptr<Event> eventClick2 = std::make_shared<Event>(config2);
    std::shared_ptr<HitBoxSquare> rectangle_load2 = std::make_shared<HitBoxSquare>(CONFIG::CompType::HITBOXSQUARE, 64, sf::IntRect(0, 0, 300, 100));
    std::shared_ptr<Sprite> spriteButtonLoadShared = std::make_shared<Sprite>(CONFIG::CompType::SPRITE, 59998);
    std::shared_ptr<Position> positionButtonLoadShared = std::make_shared<Position>(CONFIG::CompType::POSITION, 59886, 1610, 100);
    sf::IntRect spriteRectButton2(0, 0, 300, 100);
    spriteButtonLoadShared->setSprite(positionButtonLoadShared->getPositionX(), positionButtonLoadShared->getPositionY(), "assets/editor/gui/loadButton.png", sf::Vector2f(0.45, 0.45), spriteRectButton2, CONFIG::SpriteType::BUTTON);
    spriteButtonLoadShared->setMaxDimensions(150, 50);
    spriteButtonLoadShared->initSprite();
    buttonLoad.addComponent(positionButtonLoadShared);
    buttonLoad.addComponent(spriteButtonLoadShared);
    buttonLoad.addComponent(eventClick2);
    buttonLoad.addComponent(rectangle_load2);
    //      SAVE        //
    Entity buttonSave;
    buttonSave.init();
    Event::event_config config3;
    config3.isActive = is_clicked;
    config3.action = save;
    std::shared_ptr<Event> eventClick3 = std::make_shared<Event>(config3);
    std::shared_ptr<HitBoxSquare> rectangle_load3 = std::make_shared<HitBoxSquare>(CONFIG::CompType::HITBOXSQUARE, 64, sf::IntRect(0, 0, 300, 100));
    std::shared_ptr<Sprite> spriteButtonSaveShared = std::make_shared<Sprite>(CONFIG::CompType::SPRITE, 56668);
    std::shared_ptr<Position> positionButtonSaveShared = std::make_shared<Position>(CONFIG::CompType::POSITION, 0, 1470, 100);
    sf::IntRect spriteRectButton3(0, 0, 300, 100);
    spriteButtonSaveShared->setSprite(positionButtonSaveShared->getPositionX(), positionButtonSaveShared->getPositionY(), "assets/editor/gui/saveButton.png", sf::Vector2f(0.45, 0.45), spriteRectButton3, CONFIG::SpriteType::BUTTON);
    spriteButtonSaveShared->setMaxDimensions(300, 100);
    spriteButtonSaveShared->initSprite();
    buttonSave.addComponent(positionButtonSaveShared);
    buttonSave.addComponent(spriteButtonSaveShared);
    buttonSave.addComponent(eventClick3);
    buttonSave.addComponent(rectangle_load3);

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
            count_y += 1;
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
        sf::Vector2f scale = sf::Vector2f(4, 4);
        if (spriteRect1.width > 40) {
            scale.x = 2;
            scale.y = 2;
        }
        sprite1Shared->setSprite(x, y, entity_json["sprite"], scale, spriteRect1, CONFIG::SpriteType::ENEMYSPRITE);
        sprite1Shared->initSprite();
        std::shared_ptr<Position> position1Shared = std::make_shared<Position>(position1);
        std::shared_ptr<Draggable> draggable1Shared = std::make_shared<Draggable>(CONFIG::CompType::DRAGGABLE);
        std::string path(entry.path().c_str());
        std::shared_ptr<Path> pathJson = std::make_shared<Path>(path);
        Event::event_config config_event;
        config_event.isActive = is_dragging;
        config_event.action = drag_and_drop;
        std::shared_ptr<Event> eventShared = std::make_shared<Event>(config_event);
        mob.addComponent(position1Shared);
        mob.addComponent(sprite1Shared);
        mob.addComponent(draggable1Shared);
        mob.addComponent(eventShared);
        mob.addComponent(pathJson);
        _core._manager->addEntity(mob);
    }
}

void Editor::loadSystems() {
    _core.addSystem(std::make_shared<SysRenderGlobal>(_core._manager));
    _core.addSystem(std::make_shared<SysPollEvent>(_core._manager, _core.isRunning()));
    _core.addSystem(std::make_shared<SysCameraEditor>(_core._manager));
}

void leave(Event::event_data &data) {
    data.is_running->setRunning(false);
}

bool is_dragging(Event::event_data &data) {
    std::shared_ptr<Draggable> draggable = data.entity->getComponentByType<Draggable>(CONFIG::CompType::DRAGGABLE);
    std::shared_ptr<Sprite> sprite = data.entity->getComponentByType<Sprite>(CONFIG::CompType::SPRITE);
    if (draggable != nullptr && sprite != nullptr) {
        if (draggable->isBeingDragged())
            return true;
        if (data.event->type == sf::Event::MouseButtonPressed) {
            if (sprite->getSprite().getGlobalBounds().contains(data.mouse) && !draggable->isBeingDragged())
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
    std::shared_ptr<Path> path = std::make_shared<Path>(data.entity->getComponentByType<Path>(CONFIG::CompType::PATH)->getPath());
    std::shared_ptr<Sprite> spriteShared = std::make_shared<Sprite>(sp);
    spriteShared->setSprite(sprite->getSprite());
    spriteShared->setScale(4);
    spriteShared->setRect(sprite->getRect());
    entity_dragged.addComponent(spriteShared);
    entity_dragged.addComponent(path);
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
    std::shared_ptr<RectangleShape> rectangle_c = editor->getComponentByType<RectangleShape>(CONFIG::CompType::RECTANGLESHAPE);

    sf::IntRect hitbox = hitbox_c->getRectangle();
    sf::Vector2i mouse_pos = sf::Mouse::getPosition();
    if (hitbox.contains(mouse_pos)) {
        std::shared_ptr<Entity> entity = data.entity_manager->getEntity(draggable->getEntityDragged());
        Entity new_entity;
        new_entity.init();
        Sprite sp(CONFIG::CompType::SPRITE, 59912);
        std::shared_ptr<Sprite> sprite = entity->getComponentByType<Sprite>(CONFIG::CompType::SPRITE);
        std::shared_ptr<Sprite> spriteShared = std::make_shared<Sprite>(sp);
        std::shared_ptr<Path> path = std::make_shared<Path>(entity->getComponentByType<Path>(CONFIG::CompType::PATH)->getPath());
        spriteShared->setSprite(sprite->getSprite());
        Event::event_config select_element_config;
        select_element_config.action = select_element;
        select_element_config.isActive = is_selected;
        Event::event_config move_element_config;
        move_element_config.action = move_element;
        move_element_config.isActive = is_selected_and_pressed;
        std::shared_ptr<Event> event_move = std::make_shared<Event>(move_element_config);
        std::shared_ptr<Event> event_select = std::make_shared<Event>(select_element_config);
        int editor_x = editor->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionX();
        sf::IntRect rect = sprite->getRect();
        editor_x = (data.mouse.x - ((rect.width * 4) / 2)) + editor_x;
        int editor_y = (data.mouse.y - ((rect.height * 4) / 2));
        spriteShared->setIntRect(sprite->getRect());
        std::shared_ptr<Position> positionShared = std::make_shared<Position>(CONFIG::CompType::POSITION, 231865, editor_x, editor_y);
        std::shared_ptr<String> isSelectedShared = std::make_shared<String>("null");
        std::shared_ptr<RectangleShape> rectangleShared = std::make_shared<RectangleShape>();
        new_entity.addComponent(spriteShared);
        new_entity.addComponent(positionShared);
        new_entity.addComponent(path);
        new_entity.addComponent(event_move);
        new_entity.addComponent(event_select);
        new_entity.addComponent(isSelectedShared);
        new_entity.addComponent(rectangleShared);
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

void move(Event::event_data &data)
{
    std::shared_ptr<Position> position = data.entity->getComponentByType<Position>(CONFIG::CompType::POSITION);
    if (data.event->key.code == sf::Keyboard::Left)
        position->setPositionX(position->getPositionX() - 10);
    if (data.event->key.code == sf::Keyboard::Right)
        position->setPositionX(position->getPositionX() + 10);
}

bool is_clicked(Event::event_data &data)
{
    std::shared_ptr<HitBoxSquare> hitbox = data.entity->getComponentByType<HitBoxSquare>(CONFIG::CompType::HITBOXSQUARE);
    std::shared_ptr<Position> position = data.entity->getComponentByType<Position>(CONFIG::CompType::POSITION);
    std::shared_ptr<Sprite> sprite = data.entity->getComponentByType<Sprite>(CONFIG::CompType::SPRITE);
    std::shared_ptr<Bool> bool_ = data.entity->getComponentByType<Bool>(CONFIG::CompType::BOOL);
    if (hitbox != nullptr) {
        if (data.event->type == sf::Event::MouseButtonPressed) {
            sf::IntRect rect = hitbox->getRectangle();
            rect.left = position->getPositionX();
            rect.top = position->getPositionY();
            if (sprite->getSprite().getGlobalBounds().contains(data.mouse))
                return true;
        }
    }
    return false;
}

void save(Event::event_data &data)
{
    std::cout << "SAVE !" << std::endl;
    nlohmann::json map_json;
    map_json["name"] = "Test de Map";
    map_json["size"] = 3000;
    map_json["enemies"];
    std::vector<Entity> entities = data.entity_manager->getEntityById(550)->getComponentByType<Camera>(CONFIG::CompType::CAMERA)->getEntities();
    for (Entity entity : entities) {
        std::shared_ptr<Sprite> sprite = entity.getComponentByType<Sprite>(CONFIG::CompType::SPRITE);
        std::shared_ptr<Position> position = entity.getComponentByType<Position>(CONFIG::CompType::POSITION);
        std::shared_ptr<Path> path = entity.getComponentByType<Path>(CONFIG::CompType::PATH);
        std::ifstream input_file(path->getPath());
        nlohmann::json entity_json;
        input_file >> entity_json;
        input_file.close();
        entity_json["positions"].push_back({
            {"x", position->getPositionX()},
            {"y", position->getPositionY()}
        });
        map_json["enemies"].push_back(entity_json);
    }
    std::ofstream file("assets/maps/map.json");
    file << map_json.dump(4);
    file.close();
}

void load(Event::event_data &data)
{
    std::cout << "LOAD !" << std::endl;
    std::string selectedFile;
    try {
        // selectedFile = std::filesystem::absolute(sf::String(sf::FileDialog::getOpenFileName()));
        std::cout << "Selected file: " << selectedFile << std::endl;
    } catch (std::exception& e) {
        std::cerr << "File dialog error: " << e.what() << std::endl;
    }
}

void select_element(Event::event_data &data) {
    std::shared_ptr<RectangleShape> rectangle = data.entity->getComponentByType<RectangleShape>(CONFIG::CompType::RECTANGLESHAPE);

    for (auto &entity : data.entity_manager->getEntities()) {
        std::shared_ptr<Camera> camera = entity->getComponentByType<Camera>(CONFIG::CompType::CAMERA);
        std::shared_ptr<Position> position = entity->getComponentByType<Position>(CONFIG::CompType::POSITION);
        if (camera) {
            std::shared_ptr<Position> mob_position = data.entity->getComponentByType<Position>(CONFIG::CompType::POSITION);
            int x_cam = mob_position->getPositionX() - position->getPositionX();
            rectangle->setRectangleShape(data.entity, x_cam);
        }
    }
}

bool is_selected(Event::event_data &data) {
    std::shared_ptr<Sprite> sprite = data.entity->getComponentByType<Sprite>(CONFIG::CompType::SPRITE);
    std::shared_ptr<Position> pos = data.entity->getComponentByType<Position>(CONFIG::CompType::POSITION);
    std::shared_ptr<RectangleShape> rectangle = data.entity->getComponentByType<RectangleShape>(CONFIG::CompType::RECTANGLESHAPE);
     sf::Vector2f mousePosF(static_cast<float>(data.mouse.x), static_cast<float>(data.mouse.y));
    if (sprite->getSprite().getGlobalBounds().contains(mousePosF)) {
        if (data.entity->getComponentByType<String>(CONFIG::CompType::STRING)->getString() == "null" && data.event->type == sf::Event::MouseButtonPressed) {
            data.entity->getComponentByType<String>(CONFIG::CompType::STRING)->setValue("clicked");
            return false;
        }
        if (data.entity->getComponentByType<String>(CONFIG::CompType::STRING)->getString() == "clicked" && data.event->type == sf::Event::MouseButtonReleased) {
            data.entity->getComponentByType<String>(CONFIG::CompType::STRING)->setValue("selected");
            return true;
        }
    } else {
        if (data.entity->getComponentByType<String>(CONFIG::CompType::STRING)->getString() == "selected" && data.event->type == sf::Event::MouseButtonPressed) {
            data.entity->getComponentByType<String>(CONFIG::CompType::STRING)->setValue("null");
            rectangle->setRectangleShape(data.entity, -1000);
            return false;
        }
    }
    return false;
}

void move_element(Event::event_data &data) {
    std::shared_ptr<Sprite> sprite = data.entity->getComponentByType<Sprite>(CONFIG::CompType::SPRITE);
    std::shared_ptr<RectangleShape> rectangle = data.entity->getComponentByType<RectangleShape>(CONFIG::CompType::RECTANGLESHAPE);
    sf::IntRect rect = sprite->getRect();
    for (auto &entity : data.entity_manager->getEntities()) {
        std::shared_ptr<Camera> camera = entity->getComponentByType<Camera>(CONFIG::CompType::CAMERA);
        std::shared_ptr<Position> position2 = entity->getComponentByType<Position>(CONFIG::CompType::POSITION);
        if (camera) {
            std::shared_ptr<Position> mob_position = data.entity->getComponentByType<Position>(CONFIG::CompType::POSITION);
            int x_cam = mob_position->getPositionX() - position2->getPositionX();
            rectangle->setRectangleShape(data.entity, x_cam);
            mob_position->setPositionX((((int) data.mouse.x) - ((rect.width * 4) / 2)) + position2->getPositionX());
            mob_position->setPositionY(((int) data.mouse.y) - ((rect.height * 4) / 2));
        }
    }
}

bool is_selected_and_pressed(Event::event_data &data) {
    std::shared_ptr<Sprite> sprite = data.entity->getComponentByType<Sprite>(CONFIG::CompType::SPRITE);
    if (sprite->getSprite().getGlobalBounds().contains(data.mouse)) {
        if (data.entity->getComponentByType<String>(CONFIG::CompType::STRING)->getString() == "selected" && data.event->type == sf::Event::MouseButtonPressed) {
            data.entity->getComponentByType<String>(CONFIG::CompType::STRING)->setValue("pressed");
            return true;
        }
    }
    if (data.entity->getComponentByType<String>(CONFIG::CompType::STRING)->getString() == "pressed" && data.event->type == sf::Event::MouseButtonReleased) {
        data.entity->getComponentByType<String>(CONFIG::CompType::STRING)->setValue("selected");
        return false;
    }
    if (data.entity->getComponentByType<String>(CONFIG::CompType::STRING)->getString() == "pressed") {
        return true;
    }
    return false;
}