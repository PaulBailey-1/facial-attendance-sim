#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Map.h"

typedef std::vector<std::vector<int>> iGrid;

class Entity {
public:

    Entity(int id, int fromRoom, int toRoom);

    void createPathMap(const Map &map);

    const iGrid& getPathMap() const { return _pathMap; }

private:

    int _id;
    int _fromRoom;
    int _toRoom;
    glm::ivec2 _to;

    iGrid _pathMap;

};