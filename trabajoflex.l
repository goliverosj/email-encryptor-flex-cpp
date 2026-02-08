%option noyywrap

%{
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Archivos y variables externas
ifstream inputFile;
ofstream outputFile, emailFile, desencriptadosFile;
int emailCount = 0;

// Función de encriptación
string encriptar(const string& texto, int desplazamiento) {
    string resultado = texto;
    for (char& c : resultado) {
        c += desplazamiento;  // Desplaza cada carácter
    }
    return resultado;
}

// Función de desencriptación
string desencriptar(const string& texto, int desplazamiento) {
    string resultado = texto;
    for (char& c : resultado) {
        c -= desplazamiento;  // Desplaza en sentido contrario
    }
    return resultado;
}
%}

%%

[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,} { 
    emailCount++; 
    string correoEncriptado = encriptar(yytext, 3);  // Encripta el correo
    emailFile << correoEncriptado << endl;  // Guarda el correo encriptado
    outputFile << "[correo oculto]";  // Reemplaza el correo en el archivo de salida
}

. { outputFile << yytext; }

%%
