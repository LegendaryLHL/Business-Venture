#pragma once

#include <vector>

#include "../core/Shader.hpp"
#include "../core/Asset.hpp"

class Entity {
public:
    Entity(glm::vec3 position = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f), Asset::Texture texture = Asset::Texture::BUILDING, Asset::Vertex = Asset::Vertex::CUBE);
    virtual ~Entity() = default;

    static std::vector<Entity*> entities;

    virtual void draw(Shader &shader);
    virtual void update(float deltaTime);
    virtual void remove();

    const glm::vec3& getPosition() const { return position; }
    
    bool isBuilding = false;

protected:
    glm::vec3 position;
    glm::vec3 scale;

    Asset::Texture texture;
    Asset::Vertex vertex;

    Entity* checkCollision();
};
