//
// Created by Édouard on 2020-11-10.
//

#include "Grid.h"
#include <iostream>
Grid::Grid(glm::vec3 dimensions, float cellSize) {
    this->dimensions = dimensions;
    this->cellSize = cellSize;
    cellCount = dimensions.x/cellSize * dimensions.y/cellSize * dimensions.z/cellSize;
    cells.resize(cellCount);
}
glm::vec3 Grid::getCellPos(glm::vec3 pos) const{
    return glm::floor(pos/cellSize);
}

int Grid::getCellHash(glm::vec3 cellPos) const {

    if((cellPos.x < 0)||(cellPos.x >= dimensions.x/cellSize)||
        (cellPos.y < 0)||(cellPos.y >= dimensions.y/cellSize)||
        (cellPos.z < 0)||(cellPos.z >= dimensions.z/cellSize)) {
        return -1;
    }

    int hash = (int) (cellPos.x + dimensions.x * (cellPos.y + dimensions.y * cellPos.z));

    return hash;
}
void Grid::findNeighbors(std::vector<glm::vec3> &positions, float rad, std::vector<std::vector<int>> &neighbors) {

    #pragma omp parallel for
    for(int n = 0; n < neighbors.size(); n++) {
        neighbors[n].clear();
    }
    #pragma omp parallel for
    for(int c = 0; c < cells.size(); c++) {
        cells[c].clear();
    }

    for (int p = 0; p < positions.size(); p++) {
        cells[getCellHash(getCellPos(positions[p]))].push_back(p);
    }
    #pragma omp parallel for
    for(int p = 0; p < positions.size(); p++) {
        glm::vec3 cellPos = getCellPos(positions[p]);

        for (int k = -1; k <= 1; k++) {
            for (int j = -1; j <= 1; j++) {
                for (int i = -1; i <= 1; i++) {
                    int hash = getCellHash(cellPos + glm::vec3((float) i, (float) j, (float) k) / cellSize);
                    if (hash != -1) {
                        for (auto &n : cells[hash]) {
                            float dist = glm::distance(positions[n], positions[p]);
                            if (dist <= rad && dist > 0)
                                neighbors[p].push_back(n);
                        }
                    }
                }
            }
        }
    }
}

std::vector<glm::vec3> Grid::getCellInstances() {
    std::vector<glm::vec3> cells;
    for (int i = 0; i < (int)dimensions.x; i++) {
        for (int j = 0; j < (int)dimensions.y; j++) {
            for (int k = 0; k < (int)dimensions.z; k++) {
                cells.push_back(glm::vec3(i+0.5,j+0.5,k+0.5));
            }
        }
    }
    return cells;
}
