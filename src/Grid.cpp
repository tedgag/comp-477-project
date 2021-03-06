//
// Created by Édouard on 2020-11-10.
//

#include "Grid.h"
#include <iostream>
#include <memory>
#include <random>

Grid::Grid(float cellSize, float particleRadius) {
    this->cellSize = cellSize;
    this->particleRadius = particleRadius;
    generateBoundaryParticles();
}
glm::vec3 Grid::getCellPos(glm::vec3 pos){
    if (pos.x == boundaries.x) {
        pos.x -= 0.01f;
    }
    if (pos.y == boundaries.y) {
        pos.y -= 0.01f;
    }
    if (pos.z == boundaries.z) {
        pos.z -= 0.01f;
    }
    return glm::floor(pos/cellSize);
}

int Grid::getCellHash(glm::vec3 cellPos) {

    if((cellPos.x < 0)||(cellPos.x >= dimensions.x)||
        (cellPos.y < 0)||(cellPos.y >= dimensions.y)||
        (cellPos.z < 0)||(cellPos.z >= dimensions.z)) {
        return -1;
    }

    int hash = (int) (cellPos.x + dimensions.x * (cellPos.y + dimensions.y * cellPos.z));
    return hash;
}
void Grid::findNeighbors(std::vector<Particle * > &particles, float rad) {

    #pragma omp parallel for
    for(int c = 0; c < cells.size(); c++) {
        cells[c].clear();
    }

    for (int p = 0; p < particles.size(); p++) {
        cells[getCellHash(getCellPos(particles[p]->position))].push_back(p);
    }

    #pragma omp parallel for
    for(int m = 0; m < particles.size(); m++) {
        const auto p = particles[m];
        const glm::vec3 cellPos = getCellPos(p->position);
        p->neighbors.clear();
        p->ghosts.clear();

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                for (int k = -1; k <= 1; k++) {
                    int hash = getCellHash(cellPos + glm::vec3((float) i, (float) j, (float) k));
                    if (hash != -1) {
                        for (auto & n : cells[hash]) {
                            const auto neighbor = particles[n];
                            const float dist = glm::distance(p->position, neighbor->position);
                            if (dist <= rad && m != n)
                                p->neighbors.push_back(neighbor);
                        }
                    }
                }
            }
        }

        // Find ghost neighbors
        float boundaryDist = 0.5f * rad;
        for (int i = 0 ; i< 3; i++) {
            if(p->position[i]< boundaryDist || p->position[i] > (boundaries[i]-boundaryDist)) {
                for(const auto& bp: boundaryParticles) {
                    const auto bpPos = bp->position;
                    glm::vec3 gPos;
                    switch (i) {
                        case 0:
                            gPos = p->position[i] < boundaryDist ?
                                   - glm::vec3((boundaryDist + bpPos[2]), bpPos[0], bpPos[1]) :
                                   glm::vec3(cellSize + (boundaryDist + bpPos[2]), bpPos[0], bpPos[1]);
                            break;
                        case 1:
                            gPos = p->position[i] < boundaryDist ?
                                   - glm::vec3(bpPos[0], boundaryDist + bpPos[2], bpPos[1]) :
                                   glm::vec3(cellSize + (boundaryDist + bpPos[0]), bpPos[2], bpPos[1]);
                            break;
                        case 2:
                            gPos =  p->position[i] < boundaryDist ?
                                    - glm::vec3(bpPos[0], bpPos[1],  (bpPos[2] + boundaryDist)):
                                    + glm::vec3(bpPos[0], bpPos[1], cellSize + (boundaryDist + bpPos[2]));
                    }
                    gPos +=  cellPos * cellSize;
                    const float dist = glm::distance(p->position, gPos);
                    if(dist <= rad) {
                        p->ghosts.push_back(p->position - gPos);
                    }
                }
            }
        }
    }
}

void Grid::collisionHandling(std::vector<Particle * > &particles) {
    #pragma omp parallel for
    for (int i =0 ; i<particles.size(); i++) {
        const auto p = particles[i];
        for (int j=0; j< 3 ; j++) {
            if (p->position[j] < 0.0f) {
                p->velocity[j] *= boundDamping;
                p->position[j] = 0.0f;
            }
            if (p->position[j] > boundaries[j] ) {
                p->velocity[j] *= boundDamping;
                p->position[j] = boundaries[j];
            }
        }
    }
}
void Grid::generateBoundaryParticles() {
    const int side = 13;
    const float dist = 3.0f * cellSize / side;
    const auto corner = glm::vec2(dist * 0.5f -  3.0f * cellSize / 2);

    for(int i = 0; i < side; ++i) {
        for(int j = 0; j < side; ++j) {
            auto p = new Particle();
            p->position = glm::vec3 (corner + glm::vec2(i, j) * dist, 0.0f);
            boundaryParticles.push_back(p);
        }
    }
}

void Grid::resizeGrid(glm::vec3 newBoundaries) {
    this->boundaries = newBoundaries;
    this->dimensions = glm::vec3(glm::ceil(newBoundaries.x / cellSize) ,
            glm::ceil(newBoundaries.y / cellSize) ,
            glm::ceil(newBoundaries.z / cellSize));
    cellCount = dimensions.x * dimensions.y * dimensions.z;
    cells.resize(cellCount + 1);
}
