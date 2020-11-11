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
    std::vector<std::vector<Particle *>> hashTable;
    glm::vec3 getCellPos(glm::vec3 position);
    int getCellHash(glm::vec3 position);
public:
    Grid(glm::vec3 dimensions, float cellSize);
    void buildHashTable(std::vector<Particle *> particles);
    std::vector<Particle *> findNeighbors(Particle * p, float rad);
};

#endif //COMP477PROJECT_GRID_H
