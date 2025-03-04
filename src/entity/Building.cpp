#include "Building.hpp"
#include "../core/Game.hpp"

std::set<Building*, Building::BuildingComparator> Building::buildingBst;

Building::Building(glm::vec3 position) : Entity(position, glm::vec3(1.0f), Asset::Texture::BUILDING, Asset::Vertex::CUBE){
    isBuilding = true;
}

void Building::update(float deltaTime){
    if(Game::isLost){
        speed = 10.0f;
        if(position.y < 1.0f){
            if(position.x > 0){
                position.x += speed * deltaTime; 
            }
            else{
                position.x -= speed * deltaTime; 
            }
        }
        else{
            position += glm::vec3(0.0f, -speed + 1.0f, 0.0f) * deltaTime;
        }
        return;
    }

    if(Game::isWon){
        speed = 30.0f;
        position += glm::vec3(0.0f, speed, 0.0f) * deltaTime;
    }

    if(checkCollision()){
        if (isFalling) {
            auto it = buildingBst.find(this);
            if (it != buildingBst.end()) {
                buildingBst.erase(it);
            }
            buildingBst.insert(this);
            isFalling = false;
        }
    }
    else{
        position += glm::vec3(0.0f, -speed, 0.0f) * deltaTime;
        isFalling = true;
    }
}

void Building::remove(){
    Entity::remove();
    auto it = buildingBst.find(this);
    if (it != buildingBst.end()) {
        buildingBst.erase(it);
    }
}


int Building::countTop(){
    float height;
    int count = 0;

    auto buildingBstIt = Building::buildingBst.rbegin(); 

    if(buildingBstIt == Building::buildingBst.rend()){
        return 0;
    }
    else{
        Building* firstBuilding = *buildingBstIt;
        height = firstBuilding->position.y;
        count++;
        buildingBstIt++;
    }

    while (buildingBstIt != Building::buildingBst.rend()){
        Building* building = *buildingBstIt;
        if(!building->isFalling){
            if(fabs(building->position.y - height) < 0.3f){
                count++;
            }
            else{
                break;
            }
        }
        buildingBstIt++;
    }

    return count;

}
