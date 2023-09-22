/*
** EPITECH PROJECT, 2023
** Client
** File description:
** ThreadHandler.hpp
*/

#pragma once
    #include <iostream>
    #include <thread>

    class ThreadHandler {
        public:
            ThreadHandler();
            void start();
            void stop();
            virtual void run() = 0;
            virtual bool getRunning() = 0;
        protected:
            bool running_;
        private:
            std::thread thread_;
    };