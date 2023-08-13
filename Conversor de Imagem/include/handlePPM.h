//---------------------------------------------------------------------
// Arquivo	: handlePPM.h
// Conteudo	: TAD para armazenar e manipular imagens no formato PPM (Colorida) 
// Autor	: Ana Lúcia Oliveira de Paula (analop@ufmg.br)
// Historico	: 2022-09-03 - arquivo criado
//---------------------------------------------------------------------
#ifndef HANDLEPPM_H
#define HANDLEPPM_H

#include <iostream>
#include <fstream>
#include <string.h>
#include "memlog.h"
#include "msgassert.h"

#define ID_PPM 0

//Estrutura de dados para armazenar os pixels das cores (r,g,b) da imagem PPM
struct Pixels
{
    int r;
    int g;
    int b;
};

class handlePPM
{
    private: 
        char* file_;
        std::string id_;
        int row_ ;
        int column_ ;
        int maxValue_ ;
        Pixels** matrix;

   public: 
        handlePPM(char* file);
        ~handlePPM();

        long int acessaMatriz();
        void convertToPGM(char* file);
};

#endif