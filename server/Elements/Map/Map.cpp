/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Map.cpp
*/

#include "Map.hpp"

RType::Map::Map(const std::string &path) : _path(path)
{
}

RType::Map::~Map()
{
}

void RType::Map::loadMap(std::shared_ptr<EntityManager> manager)
{
    std::ifstream input_file(_path);
    nlohmann::json map_data;
    input_file >> map_data;
    input_file.close();
    for (nlohmann::json &entity : map_data["enemies"]) {
        loadMob(manager, entity);
    }
}

void RType::Map::loadMob(std::shared_ptr<EntityManager> manager, nlohmann::json &entity)
{
    int id = 98752;
    int id_comp = 6547452;
    float speed = 0.005 / (float) entity["speed"];
    Health health = Health(CONFIG::CompType::HEALTH, id_comp, (int) entity["health"]);
    AI ai = AI(CONFIG::CompType::AI, (CONFIG::AiType) entity["type"], id_comp, speed);
    Sprite sprite = Sprite(CONFIG::CompType::SPRITE, id_comp);
    sf::IntRect rect(entity["rectangle"]["left"], entity["rectangle"]["top"], entity["rectangle"]["width"], entity["rectangle"]["height"]);
    for (nlohmann::json &component : entity["positions"]) {
        manager->createEntity();
        Entity new_entity = Entity(id, 2);
        health.setId(id_comp);
        std::shared_ptr<Health> healthShared = std::make_shared<Health>(health);
        new_entity.addComponent(healthShared);
        id_comp += 1;
        ai.setId(id_comp);
        std::shared_ptr<AI> aiShared = std::make_shared<AI>(ai);
        new_entity.addComponent(aiShared);
        id_comp += 1;
        Position position = Position(CONFIG::CompType::POSITION, id_comp, (int) component["x"], (int) component["y"]);
        std::shared_ptr<Position> positionShared = std::make_shared<Position>(position);
        new_entity.addComponent(positionShared);
        id_comp += 1;
        sprite.setId(id_comp);
        sprite.setSprite(position.getPositionX(), position.getPositionY(), entity["sprite"], sf::Vector2f(3, 3), rect);
        std::shared_ptr<Sprite> spriteShared = std::make_shared<Sprite>(sprite);
        new_entity.addComponent(spriteShared);
        id_comp += 1;
        HitBoxSquare hitBoxSquare = HitBoxSquare(CONFIG::CompType::HITBOXSQUARE, id_comp, rect);
        hitBoxSquare.setId(id_comp);
        std::shared_ptr<HitBoxSquare> hitBoxSquareShared = std::make_shared<HitBoxSquare>(hitBoxSquare);
        new_entity.addComponent(hitBoxSquareShared);
        manager->addEntity(new_entity);
        id_comp += 1, id += 1;
    }
}