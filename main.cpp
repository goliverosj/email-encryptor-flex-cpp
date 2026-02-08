#include <iostream>
#include <fstream>
#include <cstring>      // Para strcmp
#include "FlexLexer.h"  // Para yyFlexLexer

using namespace std;

// Declaraciones externas usadas en Flex
extern ifstream inputFile;
extern ofstream outputFile, emailFile, desencriptadosFile;
extern int emailCount;

// Declaración externa de la función de encriptación
extern std::string encriptar(const std::string& texto, int desplazamiento);

//Declaración externa de la función de desencriptación
extern std::string desencriptar(const std::string& texto, int desplazamiento);


// Función para desencriptar y guardar correos
void desencriptarArchivo(const string& archivoEntrada, const string& archivoSalida, int desplazamiento) {
    ifstream archivoEncriptado(archivoEntrada);
    desencriptadosFile.open(archivoSalida);

    if (!archivoEncriptado.is_open() || !desencriptadosFile.is_open()) {
        cout << "Error al abrir los archivos." << endl;
        return;
    }

    string correo;
    cout << "Correos desencriptados guardados en " << archivoSalida << endl;

    while (getline(archivoEncriptado, correo)) {
        string correoDesencriptado = desencriptar(correo, desplazamiento);
        desencriptadosFile << correoDesencriptado << endl;  // Guarda el correo desencriptado
    }

    archivoEncriptado.close();
    desencriptadosFile.close();
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "Uso: ./prog <opción> <archivo_entrada>" << endl;
        cout << "Opciones disponibles:" << endl;
        cout << "  0 - Encriptar correos electrónicos del archivo de texto" << endl;
        cout << "  1 - Desencriptar el archivo de correos encriptados" << endl;
        return 1;
    }

    // Manejo de opciones
    if (strcmp(argv[1], "0") == 0) {
        // Modo de encriptación
        inputFile.open(argv[2]);
        if (!inputFile.is_open()) {
            cout << "Error al abrir el archivo de entrada." << endl;
            return 1;
        }

        outputFile.open("salida_modificada.txt");
        emailFile.open("encriptados.txt");

        yyFlexLexer lexer(&inputFile, &outputFile);
        lexer.yylex();  // Inicia el análisis

        cout << "Proceso completo. Correos encontrados: " << emailCount << endl;

        inputFile.close();
        outputFile.close();
        emailFile.close();

    } else if (strcmp(argv[1], "1") == 0) {
        // Modo de desencriptación
        desencriptarArchivo(argv[2], "desencriptados.txt", 3);
    } else {
        cout << "Opción inválida. Use 0 para encriptar o 1 para desencriptar." << endl;
        return 1;
    }

    return 0;
}


