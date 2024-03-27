//
// Created by kamert on 19-03-2024.
//

#ifndef PROJETODA_MENU_H
#define PROJETODA_MENU_H

#include "System.h"

class Menu{
public:

    void start(System system);
    void normalFlowMenu(System system, Graph *graph);
    void avoidFlowMenu(System system, Graph *graph);
};
#endif //PROJETODA_MENU_H
