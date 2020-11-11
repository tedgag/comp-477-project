//
// Created by Édouard on 2020-11-10.
//

#include "Grid.h"
#include <iostream>
Grid::Grid(glm::vec3 dimensions, float cellSize) {
    this->dimensions = dimensions;
    this->cellSize = cellSize;
    this->cellCount = dimensions.x * dimensions.y * dimensions.z;
    this->hashTable.resize(cellCount);
}
glm::vec3 Grid::getCellPos(glm::vec3 position){
    return glm::floor(position/cellSize);
}

int Grid::getCellHash(glm::vec3 position) {
    if (position.x < 0 || position.x>= dimensions.x ||
        position.y < 0 || position.y>= dimensions.y ||
        position.z < 0 || position.z>= dimensions.z)
        return -1;
    glm::vec3 cellPos = getCellPos(position);

    return (int) (cellPos.x + dimensions.x * (cellPos.y + dimensions.y * cellPos.z));
}
void Grid::buildHashTable(std::vector<Particle *> particles){
    for (auto & p : particles) {
        hashTable[getCellHash(p->position)].push_back(p);
    }
}
std::vector<Particle *> Grid::findNeighbors(Particle * particle, float rad) {
    glm::vec3 cellPos = getCellPos(particle->position);
    std::vector<Particle *> neighbors;
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            for(int k = -1; k <= 1; k++) {

                int hash = getCellHash(cellPos + glm::vec3(i,j,k));
                if (hash != -1) {
                    for (auto &p : hashTable[hash]) {
                        if (glm::distance(p->position, particle->position) <= rad)
                            neighbors.push_back(p);
                    }
                }
            }
        }
    }
    return neighbors;
}