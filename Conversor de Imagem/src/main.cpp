//---------------------------------------------------------------------
// Arquivo	: main.cpp
// Conteudo	: programa para transformação de imagens .ppm em imagens .pgm
// Autor	: Ana Lúcia Oliveira de Paula (analop@ufmg.br)
// Historico	: 2022-09-03 - arquivo criado
//---------------------------------------------------------------------

#include <unistd.h>
#include <string.h>
#include <iostream>
#include "memlog.h"
#include "handlePPM.h"
#include "msgassert.h"

typedef struct option
// estrutura de dados para armazenar os valores dos argumentos do programa
{
    char* input;
    char* output;
    char* log;
    int regmem;
}option;

int main (int argc, char** argv)
{
    extern char * optarg;
    int args;
    option op;

    //inicialização da variavel de armazenamento dos argumentos
    op.input = nullptr;
    op.output = nullptr;
    op.log = nullptr;
    op.regmem = 0;

    while ((args = getopt(argc, argv, "li:o:p:")) != -1)
    {
        switch (args)
        {
        case 'i':
             op.input = optarg;
            break;
        case 'o':
            op.output = optarg;
            break;
        case 'p':
            op.log = optarg;
            erroAssert(op.log != nullptr, "main - nome de arquivo de registro deve ser definido");
            break;
        case 'l':
            op.regmem = 1;
            break;    
        default:
            std::cout << "Argumento invalido\n";
            exit(1); 
        }
    }

    //tratamento de exceção para imagens de entrada que nao contem o formato .ppm
    try{

        if (op.input[strlen(op.input) - 4] != '.' || op.input[strlen(op.input) - 3] != 'p' 
        || op.input[strlen(op.input) - 2] != 'p' || op.input[strlen(op.input) - 1] != 'm')
            throw op.input;
    }
    catch (char* e)
    {
        std::cout << e << " Nome do arquivo de entrada invalido\n";
        exit(1);
    }

    //tratamento de exceção para imagens de saida que nao contem o formato .pgm
    try{

        if (op.output[strlen(op.output) - 4] != '.' || op.output[strlen(op.output) - 3] != 'p' 
        || op.output[strlen(op.output) - 2] != 'g' || op.output[strlen(op.output) - 1] != 'm')
            throw op.output;
    }
    catch (char* e)
    {
        std::cout << e << " Nome do arquivo de saida invalido\n";
        exit(1);
    }

    // iniciar registro de acesso
    iniciaMemLog(op.log);

    // ativar ou nao o registro de acesso
    if (op.regmem)
        ativaMemLog();
    else
        desativaMemLog();

    //define a fase 0 do mem log como a fase de alocação das matrizes
    defineFaseMemLog(0);
        handlePPM* image = new handlePPM(op.input);
        image->convertToPGM(op.output);
    delete image;

    
    return finalizaMemLog();
}