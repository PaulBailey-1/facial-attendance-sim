#pragma once

#include "Map.h"

class Entity {
public:

    Entity(int id, int fromRoom, int toRoom);

    void createPathMap(const Map &map);

private:

    int _id;
    int _fromRoom;
    int _toRoom;

};