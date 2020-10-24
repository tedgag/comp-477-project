//
// Created by Édouard Gagné on 2020-10-16.
//

#ifndef COMP477PROJECT_SIMULATION_H
#define COMP477PROJECT_SIMULATION_H

#include "Renderer.h"

class Simulation {
    public:
        Simulation();
        void run();
    private:
        Renderer * renderer;
};


#endif //COMP477PROJECT_SIMULATION_H
