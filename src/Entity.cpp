#include "Entity.h"

Entity::Entity(int id, int fromRoom, int toRoom) {

    _id = id;
    _fromRoom = fromRoom;
    _toRoom = toRoom;

}

void Entity::createPathMap(const Map &map) {
    
}
