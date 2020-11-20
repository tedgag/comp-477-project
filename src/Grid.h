//
// Created by Édouard on 2020-11-10.
//

#ifndef COMP477PROJECT_GRID_H
#define COMP477PROJECT_GRID_H
#include "Particle.h"
#include <vector>
class Grid {
private:
    glm::vec3 dimensions;
    float cellSize;
    float cellCount;
    float particleRadius;
    std::vector<std::vector<int>> cells;
    const float boundDamping = -0.5f;
    const float displacement = 0.25f;
    glm::vec3 getCellPos(glm::vec3 position) const;
    int getCellHash(glm::vec3 position) const;
    std::vector<Particle *> boundaryParticles;
    void generateBoundaryParticles();
public:
    Grid(glm::vec3 dimensions, float cellSize, float particleRadius);
    void findNeighbors(std::vector<Particle *> &particles, float rad);
    std::vector<glm::vec3> getCellInstances();
    void collisionHandling(std::vector<Particle *> &particles);

};

#endif //COMP477PROJECT_GRID_H
