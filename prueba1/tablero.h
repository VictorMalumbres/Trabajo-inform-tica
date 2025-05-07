#pragma once
#include "Pieza.h"  
#include "Torre.h"  
#include "Reina.h"  
#include "Rey.h"    
#include "Peon.h"   
#include <vector>

class Tablero {
private:
    std::vector<Pieza*> piezas;  // Vector para almacenar las piezas

public:
    Tablero(); 
    void inicializa();  
    void dibuja();  
};
