//
// Created by Édouard on 2020-11-10.
//

#include "Grid.h"
#include <iostream>
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
    if (hash >= cellCount) {
        std::cout << to_string(boundaries/cellSize) << std::endl;
        std::cout << to_string(cellPos) << std::endl;
        //std::cout << hash << std::endl;
        //std::cout << cellCount << std::endl;
    }
    return hash;
}
void Grid::findNeighbors(std::vector<Particle *> &particles, float rad) {

    #pragma omp parallel for
    for(int c = 0; c < cells.size(); c++) {
        cells[c].clear();
    }

    for (int p = 0; p < particles.size(); p++) {
        cells[getCellHash(getCellPos(particles[p]->position))].push_back(p);
    }

    #pragma omp parallel for
    for(int m = 0; m < particles.size(); m++) {
        auto * p = particles[m];
        glm::vec3 cellPos = getCellPos(p->position);
        p->neighbors.clear();
        p->ghosts.clear();

        for (int k = -1; k <= 1; k++) {
            for (int j = -1; j <= 1; j++) {
                for (int i = -1; i <= 1; i++) {

                    int hash = getCellHash(cellPos + glm::vec3((float) i, (float) j, (float) k));
                    if (hash != -1) {
                        for (auto & n : cells[hash]) {
                            auto * neighbor = particles[n];
                            float dist = glm::distance(p->position, neighbor->position);
                            if (dist <= rad && m != n)
                                p->neighbors.push_back(neighbor);
                        }
                    }
                }
            }
        }

        float boundaryDist = 0.5f * rad;
        if(p->position.y < boundaryDist) {
            for(auto * bp: boundaryParticles) {
                auto bpPos = bp->position;
                auto gPos = cellPos*cellSize - glm::vec3(bpPos.x, boundaryDist + bpPos.z, bpPos.y);

                float dist = glm::distance(p->position, gPos );
                if(dist <= rad) {
                    p->ghosts.push_back(p->position - gPos);
                }

            }
        }
        if(p->position.x < boundaryDist || p->position.x > (boundaries.x-boundaryDist)) {
            for(auto * bp: boundaryParticles) {
                auto bpPos = bp->position;
                auto gPos = p->position[0] < boundaryDist ?
                            cellPos * cellSize - glm::vec3((boundaryDist + bpPos[2]), bpPos[0], bpPos[1]):
                            cellPos * cellSize + glm::vec3(cellSize + (boundaryDist + bpPos[2]), bpPos[0], bpPos[1]);

                float dist = glm::distance(p->position, gPos );
                if(dist <= rad) {
                    p->ghosts.push_back(p->position - gPos);
                }
            }
        }
        if(p->position[2] < boundaryDist || p->position[2] > (boundaries.z-boundaryDist)) {
            for(auto * bp: boundaryParticles) {
                auto bpPos = bp->position;
                auto gPos = p->position[2] < boundaryDist ?
                            cellPos * cellSize - glm::vec3(bpPos[0], bpPos[1],  (bpPos[2] + boundaryDist)):
                            cellPos * cellSize + glm::vec3(bpPos[0], bpPos[1], cellSize + (boundaryDist + bpPos[2]));
                float dist = glm::distance(p->position, gPos );
                if(dist <= rad) {
                    p->ghosts.push_back(p->position - gPos);
                }
            }
        }

    }

}

std::vector<glm::vec3> Grid::getCellInstances() {
    std::vector<glm::vec3> cells;
    for (int i = 0; i < (int)(boundaries.x/cellSize); i++) {
        for (int j = 0; j < (int)(boundaries.y/cellSize); j++) {
            for (int k = 0; k < (int)(boundaries.z/cellSize); k++) {
                cells.push_back(glm::vec3(i,j,k)*cellSize + cellSize/2);
            }
        }
    }
    return cells;
}
void Grid::collisionHandling(std::vector<Particle *> &particles) {
#pragma omp parallel for
    for (int i =0 ; i<particles.size(); i++) {
        auto * p = particles[i];
        for (int j=0; j< 3 ; j++) {
            if (p->position[j] < 0.0f) {
                p->velocity[j] *= boundDamping;
                p->position[j] += - p->position[j] * 1.5;
            }
            if (p->position[j] >= boundaries[j] ) {
                p->velocity[j] *= boundDamping;
                p->position[j] -= (p->position[j] - boundaries[j]) * 1.5;
            }
        }
    }
}
void Grid::generateBoundaryParticles() {
    int N = 13;
    float spacing = 3.0f*cellSize/(float)N;
    glm::vec2 corner = glm::vec2(-cellSize + spacing*0.5f - cellSize/2);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distr(-particleRadius, particleRadius);

    for(int l1 = 0; l1 < N; ++l1) {
        for(int l2 = 0; l2 < N; ++l2) {
            glm::vec2 pos2D = corner + glm::vec2(l1, l2)*spacing;
            auto * p = new Particle();
            p->position = glm::vec3 (pos2D[0] + distr(gen)*0.2f,pos2D[1] + distr(gen)*0.2f, distr(gen) * 0.1f);
            boundaryParticles.push_back(p);
        }
    }
}

void Grid::updateBoundaries(glm::vec3 newBoundaries, glm::vec3 newDimensions) {

    this->boundaries = newBoundaries;
    this->dimensions = newDimensions;
    cellCount = dimensions.x * dimensions.y * dimensions.z;
    cells.resize(cellCount + 1);
}
