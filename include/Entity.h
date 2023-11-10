#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Map.h"

typedef std::vector<std::vector<int>> iGrid;

class Entity {
public:

    Entity(int id, int fromRoom, int toRoom);

    void createPathMap(const Map &map);
    void step(float dt);

    const iGrid& getPathMap() const { return _pathMap; }
    const glm::vec2& getPos() const { return _pos; }

private:

    int _id;
    int _fromRoom;
    int _toRoom;
    glm::ivec2 _to;

    iGrid _pathMap;

    glm::vec2 _pos;

};