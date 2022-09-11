#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

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
        environment.moveEntityToRandomAdjacentLocation(retrievedEntity.getId());
    }
}

int main() {
    int environmentSize = 16;
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