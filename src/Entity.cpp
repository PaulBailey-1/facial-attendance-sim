
#include <cinder/Shape2d.h>

#include "Entity.h"

Entity::Entity(int id, boost::span<const UCHAR> facialFeatures, std::vector<int> schedule) {

    _id = id;

    if (facialFeatures.size_bytes() != 4 * 128) {
        throw std::runtime_error("Can't initilize entity. Invalid facial feature buffer.\n");
    }
    memcpy(_facialFeatures.data(), facialFeatures.data(), facialFeatures.size_bytes());

    if (schedule.size() < 2) {
        throw std::runtime_error("Can't initilize entity. Invalid schedule.\n");
    }
    _fromRoom = schedule[0];
    _toRoom = schedule[1];

}

void Entity::createPathMap(const Map &map) {
    
    std::vector<int> col(map.size.y + 1, -2);
    _pathMap = iGrid(map.size.x + 1, col);

    for (int x = 0; x < _pathMap.size(); x++) {
        for (int y = 0; y < _pathMap[x].size(); y++) {
            for (const ci::Shape2d& inBound : map.inBounds) {
                if (inBound.contains(glm::vec2(x, y))) {
                    _pathMap[x][y] = -1;
                    break;
                }
            }
            for (const ci::Shape2d& outBound : map.outBounds) {
                if (outBound.contains(glm::vec2(x, y))) {
                    _pathMap[x][y] = -2;
                    break;
                }
            }
        }
    }

    _pos = { map.doors[_fromRoom].pos.x, map.doors[_fromRoom].pos.y };
    _to = { round(map.doors[_toRoom].pos.x),  round(map.doors[_toRoom].pos.y) };
    _pathMap[_to.x][_to.y] = 0;

    while (1) {
        auto pathMapCopy = _pathMap;
        int unset = 0;
        for (int x = 0; x < _pathMap.size(); x++) {
            for (int y = 0; y < _pathMap[x].size(); y++) {
                if (_pathMap[x][y] == -1) {
                    unset++;
                    for (int i = -1; i < 2; i++) {
                        for (int j = -1; j < 2; j++) {
                            if (!(i == 0 && j == 0) && 
                                    x + i >= 0 && x + i < _pathMap.size() && 
                                    y + j >= 0 && y + j < _pathMap[x].size() &&
                                    _pathMap[x+i][y+j] >= 0) {
                                pathMapCopy[x][y] = _pathMap[x+i][y+j] + 1;
                            }
                        }
                    }
                }
            }
        }
        _pathMap = pathMapCopy;
        if (unset == 0) break;
    }
}

void Entity::step(float dt) {

    glm::ivec2 ipos = { round(_pos.x), round(_pos.y) };

    int current = _pathMap[ipos.x][ipos.y];
    if (current == 0) return;
    if (current == -2) { 
        current = 1e3;
    }

    int li = 0, lj = 0;
    float step = 0.0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (
                    !(i == 0 && j == 0) &&
                    ipos.x + i >= 0 && ipos.x + i < _pathMap.size() &&
                    ipos.y + j >= 0 && ipos.y + j < _pathMap[ipos.x].size() &&
                    _pathMap[ipos.x + i][ipos.y + j] != -2 &&
                    current - _pathMap[ipos.x + i][ipos.y + j] > step) {
                li = i;
                lj = j;
                int a = 0;
                step = current - _pathMap[ipos.x + i][ipos.y + j];
                if (i * j == 0) {
                    step += 0.1;
                }
            }
        }
    }
    if (li == 0 && lj == 0) return;

    glm::vec2 dir = glm::normalize(glm::vec2(glm::ivec2(ipos.x + li, ipos.y + lj) - ipos));
    _pos += dir * dt;

}
