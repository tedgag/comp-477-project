//
// Created by Édouard on 2020-11-10.
//

#ifndef COMP477PROJECT_GRID_H
#define COMP477PROJECT_GRID_H
#include "Particle.h"
#include <vector>
#include <memory>

class Grid {
private:
    glm::vec3 boundaries;
    glm::ivec3 dimensions;
    float cellSize;
    int cellCount;
    float particleRadius;
    std::vector<std::vector<int>> cells;
    const float boundDamping = -0.5f;
    const float displacement = 0.25f;
    glm::vec3 getCellPos(glm::vec3 position);
    int getCellHash(glm::vec3 position);
    std::vector<std::shared_ptr<Particle>> boundaryParticles;
    void generateBoundaryParticles();
public:
    Grid(float cellSize, float particleRadius);
    void findNeighbors(std::vector<std::shared_ptr<Particle>> &particles, float rad);
    std::vector<glm::vec3> getCellInstances();
    void collisionHandling(std::vector<std::shared_ptr<Particle>> &particles);
    void resizeGrid(glm::vec3 boundaries);

};

#endif //COMP477PROJECT_GRID_H
