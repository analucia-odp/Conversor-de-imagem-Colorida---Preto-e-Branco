//---------------------------------------------------------------------
// Arquivo	: handlePGM.h
// Conteudo	: TAD para armazenar e manipular imagens no formato PGM (Tons de Cinza) 
// Autor	: Ana Lúcia Oliveira de Paula (analop@ufmg.br)
// Historico	: 2022-09-03 - arquivo criado
//---------------------------------------------------------------------
#ifndef HANDLEPGM_H
#define HANDLEPGM_H

//Manipulação de imagens PGM (TONS DE CINZA)
#include <iostream>
#include <fstream>
#include <string>
#include <handlePPM.h>

#include "memlog.h"
#include "msgassert.h"

#define ID_PGM 1

class handlePGM
{
    private: 
        char* file_;
        std::string id_; 
        int row_;
        int column_;
        int maxValue_;
        int ** matrix;
   public: 
    handlePGM(char* file, int row, int column, Pixels **image);

    ~handlePGM();

    void printImage();
    long int acessaMatriz();
};

#endif