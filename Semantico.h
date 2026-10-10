#ifndef SEMANTICO_H
#define SEMANTICO_H

#include "Token.h"
#include <map>
#include <vector>

using namespace std;

class Semantico {
    private:
        map<string, string> tablaSimbolos;

    public:
        bool analizar(vector<Token> tokens);
        void mostrarTabla();
};

#endif