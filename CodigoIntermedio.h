#ifndef CODIGOINTERMEDIO_H
#define CODIGOINTERMEDIO_H

#include "Token.h"
#include <vector>
#include <string>

using namespace std;

class CodigoIntermedio {
    public:
        vector<string> generar(vector<Token> tokens);
};

#endif