/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** global.hpp
*/

#pragma once

#include <atomic>
#include <memory>
#include <vector>

enum Action {
    UP,
    RIGHT,
    LEFT,
    DOWN,
    SHOOT
};

std::vector<Action *> actions;
Action *action;