#include "Lexer.h"

Lexer::Lexer(string _codigo){
    codigo = _codigo;
    posicion = 0;
    linea = 1;
    columna = 1;
}

bool Lexer::esFinal(){ return posicion >= codigo.length(); }

char Lexer::actual(){ return codigo[posicion]; }

char Lexer::avanzar(){
    char caracter = codigo[posicion];
    posicion++;
    if(caracter == '\n'){
        linea++;
        columna = 1;
    }
    else{
        columna++;
    }
    return caracter;
}

void Lexer::ignorarEspacios(){
    while(!esFinal() && isspace(actual())){
        avanzar();
    }
}

Token Lexer::reconocerNumero(){
    string lexema = "";
    int lineaInicio = linea;
    int columnaInicio = columna;
    bool tienePunto = false;
    while(!esFinal()){
        if(isdigit(actual())){
            lexema += avanzar();
        }
        else if(actual() == '.'){
            tienePunto = true;
            lexema += avanzar();
        }
        else{
            break;
        }
    }
    return { tienePunto ? TipoToken::LITERAL_FLOAT : TipoToken::LITERAL_INT, lexema, lineaInicio, columnaInicio };
}

Token Lexer::reconocerString() {
    int lineaInicio = linea;
    int columnaInicio = columna;
    string lexema = "";
    lexema += avanzar(); // Comilla inicial
    while (!esFinal() && actual() != '"') {
        if (actual() == '\n') {
            registrarError(lexema, lineaInicio, columnaInicio, "String sin cerrar");
            return {TipoToken::DESCONOCIDO, lexema, lineaInicio, columnaInicio};
        }
        lexema += avanzar();
    }
    if (esFinal()) { 
        registrarError(lexema, lineaInicio, columnaInicio, "String sin cerrar");
        return {TipoToken::DESCONOCIDO, lexema, lineaInicio, columnaInicio};
    }
    lexema += avanzar(); // Comilla final
    return {TipoToken::LITERAL_STRING, lexema, lineaInicio, columnaInicio};
}

Token Lexer::reconocerIdentificador(){
    string lexema = "";
    int lineaInicio = linea;
    int columnaInicio = columna;
    lexema += avanzar();
    while(!esFinal() && (isalnum(actual()) || actual() == '_')){
        lexema += avanzar();
    }
    return { esPalabraReservada(lexema) ? TipoToken::PALABRA_RESERVADA : TipoToken::IDENTIFICADOR, lexema, lineaInicio, columnaInicio };
}

Token Lexer::reconocerSimbolo(TipoToken tipo){
    string lexema = "";
    int lineaInicio = linea;
    int columnaInicio = columna;
    lexema += avanzar();
    return { tipo, lexema, lineaInicio, columnaInicio };
}

bool Lexer::esPalabraReservada(string lexema){
    return lexema == "int" || lexema == "float" || lexema == "string" || lexema == "if" || lexema == "else";    
}

void Lexer::registrarError(string lexema, int lineaError, int columnaError, string mensaje){
    errores.push_back({ lexema, lineaError, columnaError, mensaje });
}

vector<Token> Lexer::analizar(){
    vector<Token> tokens;
    while(!esFinal()){
        ignorarEspacios();
        if(esFinal()){ break; }
        char c = actual();
        // Literal string
        if (c == '"') { tokens.push_back(reconocerString()); }
        //Identificador de numeros
        else if(isdigit(c)){ tokens.push_back(reconocerNumero()); }
        //Identificador o palabra reservada
        else if(isalpha(c) || c == '_'){ tokens.push_back(reconocerIdentificador()); }
        //Operadores aritméticos
        else if(c == '+' || c == '-' || c == '*' || c == '/'){ tokens.push_back(reconocerSimbolo(TipoToken::OPERADOR)); }
        //Asignación
        else if(c == '='){ tokens.push_back(reconocerSimbolo(TipoToken::ASIGNACION)); }
        //Delimitador
        else if(c == ';' || c == '(' || c == ')'){ tokens.push_back(reconocerSimbolo(TipoToken::DELIMITADOR)); }

        //Caracter desconocido - ERROR LÉXICO
        else{
            int lineaError = linea;
            int columnaError = columna;
            string mensaje = "Caracter no reconocido";
            string lexema = "";
            lexema += avanzar();
            registrarError(lexema, lineaError, columnaError, mensaje);
            tokens.push_back({ TipoToken::DESCONOCIDO, lexema, lineaError, columnaError });
        }
    }
    return tokens;
}

vector<ErrorLexico> Lexer::obtenerErrores(){
    return errores;
}