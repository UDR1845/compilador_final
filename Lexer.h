#ifndef LEXER_H
#define LEXER_H

#include <string>
#include "Token.h"
#include <vector>
using namespace std;

class Lexer {
    private:
        string codigo;
        int posicion;
        int linea;
        int columna;
        vector<ErrorLexico> errores;

        bool esFinal();
        char actual();
        char avanzar();
        void ignorarEspacios();
        Token reconocerNumero();
        Token reconocerString();
        Token reconocerIdentificador();
        Token reconocerSimbolo(TipoToken tipoToken);
        bool esPalabraReservada(string lexema);
        void registrarError(string lexema, int lineaError, int columnaError, string mensaje);

    public:
        Lexer(string codigoFuente);
        vector<Token> analizar();
        vector<ErrorLexico> obtenerErrores();
};
#endif