#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "Token.h"

using namespace std;

class Parser {
    private:
        vector<Token> tokens;
        int posicion;
        bool esFinal();
        Token actual();
        bool coincidir(TipoToken tipo);
        bool tipo();
        bool valor();
        bool declaracion();
        bool factor();
        bool termino();
        bool expresion();

    public:
        Parser(vector<Token> tokens);
        bool analizar();
        void error(string esperado);
};

#endif