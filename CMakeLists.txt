cmake_minimum_required(VERSION 3.13)
project(UNO C)

set(CMAKE_C_STANDARD 99)

add_executable(UNO main.c new.h new.c card.h card.c cardQueue.h cardStack.h gameplay.h gameplay.c player.h cardQueue.c cardStack.c player.c)