
#include <cinder/Shape2d.h>

#include "Entity.h"

Entity::Entity(int id, int fromRoom, int toRoom) {

    _id = id;
    _fromRoom = fromRoom;
    _toRoom = toRoom;

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
