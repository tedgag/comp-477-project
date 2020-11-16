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
    std::vector<std::vector<int>> cells;
    glm::vec3 getCellPos(glm::vec3 position) const;
    int getCellHash(glm::vec3 position) const;
public:
    Grid(glm::vec3 dimensions, float cellSize);
    void findNeighbors(std::vector<glm::vec3> &positions, float rad, std::vector<std::vector<int>> &neighbors);
    std::vector<glm::vec3> getCellInstances();
};

#endif //COMP477PROJECT_GRID_H
