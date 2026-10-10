#ifndef TOKEN_H
#define TOKEN_H

#include <string>
using namespace std;

enum class TipoToken {
    LITERAL_INT,
    LITERAL_FLOAT,
    LITERAL_STRING,
    IDENTIFICADOR,
    DESCONOCIDO,

    PALABRA_RESERVADA, //Int Float String
    OPERADOR, // + - * /
    ASIGNACION, // =
    DELIMITADOR // ;
};

struct Token {
    TipoToken tipo;
    string lexema;
    int linea;
    int columna;
};

struct ErrorLexico {
    string lexema;
    int linea;
    int columna;
    string mensaje;
};

#endif