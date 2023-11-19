#pragma once

#include <vector>
#include <array>

#include <glm/glm.hpp>
#include <boost/core/span.hpp>

#include "Map.h"

typedef std::vector<std::vector<int>> iGrid;
typedef unsigned char UCHAR;

class Entity {
public:

    Entity(int id, boost::span<const UCHAR> facialFeatures, std::vector<int> schedule);

    void createPathMap(const Map &map);
    void step(float dt);

    const iGrid& getPathMap() const { return _pathMap; }
    const glm::vec2& getPos() const { return _pos; }
    int getId() const { return _id; }
    const boost::span<UCHAR> getFacialFeatures() const { return boost::span<UCHAR>(reinterpret_cast<UCHAR*>(const_cast<float*>(_facialFeatures.data())), _facialFeatures.size() * sizeof(float)); }

private:
    
    int _id;
    int _fromRoom;
    int _toRoom;
    glm::ivec2 _to;

    iGrid _pathMap;

    glm::vec2 _pos;

    std::array<float, 128> _facialFeatures;

};