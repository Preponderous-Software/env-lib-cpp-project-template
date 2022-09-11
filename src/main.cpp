#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <assert.h>

#include <string>
#include <iostream>

#include "../env-lib-cpp/src/header/entity.h"
#include "../env-lib-cpp/src/header/environment.h"
#include "../env-lib-cpp/src/header/location.h"
#include "../env-lib-cpp/src/header/grid.h"

using namespace envlibcpp;

std::vector<Entity> generateEntities(int numEntities) {
    std::vector<Entity> entities;
    for (int i = 0; i < numEntities; i++) {
        Entity entity(i, "test");
        entities.push_back(entity);
    }
    return entities;
}

void initiateEntityMovement(std::vector<Entity>& entities, Environment& environment) {
    for (Entity& entity : entities) {
        Entity& retrievedEntity = environment.getEntity(entity.getId());
        std::string initialLocationId = retrievedEntity.getLocationId();
        assert(initialLocationId != "N/S");
        
        bool success = environment.moveEntityToRandomAdjacentLocation(retrievedEntity.getId());
        std::string currentLocationId = retrievedEntity.getLocationId();

        if (success) {
            // assert that the entity's location is adjacent to the previous location
            Location& initialLocation = environment.getGrid()->getLocation(initialLocationId);
            Location& currentLocation = environment.getGrid()->getLocation(currentLocationId);
            assert((initialLocation.getX() == currentLocation.getX() && initialLocation.getY() - 1 == currentLocation.getY()) ||
                    (initialLocation.getX() == currentLocation.getX() + 1 && initialLocation.getY() == currentLocation.getY()) ||
                    (initialLocation.getX() == currentLocation.getX() && initialLocation.getY() + 1 == currentLocation.getY()) ||
                    (initialLocation.getX() == currentLocation.getX() - 1 && initialLocation.getY() == currentLocation.getY()));
        }
        else {
            // assert that the entity's location has not changed
            assert(currentLocationId == initialLocationId);
        }
    }
}

int main() {
    int environmentSize = 8;
    Environment environment(0, "Earth", environmentSize);
    std::vector<Entity> entities = generateEntities(environmentSize);
    for (Entity& entity : entities) {
        environment.addEntity(entity);
    }
    bool running = true;
    while (running) {
        initiateEntityMovement(entities, environment);
        environment.printConsoleRepresentation();
        sleep(1);
    }
    return 0;
}