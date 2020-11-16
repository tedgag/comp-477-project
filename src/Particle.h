//
// Created by Édouard on 2020-11-10.
//

#ifndef COMP477PROJECT_PARTICLE_H
#define COMP477PROJECT_PARTICLE_H
#include "helpers/IncludeHeader.h"
#include <vector>
#endif //COMP477PROJECT_PARTICLE_H
struct Particle {
    glm::vec3 position;
    std::vector<glm::vec3> neighbors;
};