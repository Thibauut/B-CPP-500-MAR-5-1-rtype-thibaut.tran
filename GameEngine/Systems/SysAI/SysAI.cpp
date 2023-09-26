/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** SysAI.cpp
*/

#include "SysAI.hpp"

template <class T>
GameEngine::SysAI<T>::SysAI(std::list<std::shared_ptr<Entity>> &entityList)
    : EntityManager_(entityList)
{
}