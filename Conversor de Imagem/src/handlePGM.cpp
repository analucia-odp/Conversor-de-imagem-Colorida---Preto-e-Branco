//---------------------------------------------------------------------
// Arquivo	: handlePGM.cpp
// Conteudo	: implementação da TAD handlePGM
// Autor	: Ana Lúcia Oliveira de Paula (analop@ufmg.br)
// Historico	: 2022-09-03 - arquivo criado
//---------------------------------------------------------------------
#include "handlePGM.h"

handlePGM::handlePGM(char *file, int row, int column, Pixels **image)
// Descricao: Construtor que recebe uma matriz no formato PPM e cria/aloca a matriz PGM dinamicamente
// Entrada: file PPM, row, colun, image
{
    file_ = file;
    id_ = "P2";
    row_ = row;
    column_ = column;
    maxValue_ = 49;
    matrix = (int **)malloc(row_ * sizeof(int *));
    for (int i = 0; i < row_; i++)
    {
        matrix[i] = (int *)malloc(column_ * (sizeof(int)));
        erroAssert(matrix[i] != NULL, "Não há memória suficiente para alocação");
        for (int j = 0; j < column_; j++)
        {
            matrix[i][j] = (49 * (0.3 * image[i][j].r + 0.59 * image[i][j].g + 0.11 * image[i][j].b)) / 255.0;
            if (matrix[i][j] > maxValue_)
                matrix[i][j] = maxValue_;
            ESCREVEMEMLOG((long int)(&(matrix[i][j])), sizeof(int), ID_PGM);
        }
    }
}

long int handlePGM::acessaMatriz()
// Descricao: acessa mat para fins de registro de acesso
// Entrada: mat
// Saida: mat
{
    int i, j;
    double aux, s = 0.0;
    for (i = 0; i < row_; i++)
    {
        for (j = 0; j < column_; j++)
        {
            aux = matrix[i][j];
            s += aux;
            LEMEMLOG((long int)(&(matrix[i][j])), sizeof(int), ID_PGM);
        }
    }
    return s; // apenas para evitar que acesso seja eliminado
}

void handlePGM::printImage()
{
    std::ofstream fout(file_);
    erroAssert(fout,"handlePGM - arquivo de saida nao foi aberto corretamente");
    fout << id_ << "\n";
    fout << column_ << " " << row_ << "\n";
    fout << maxValue_ << "\n";
    for (int i = 0; i < row_; i++)
    {
        for (int j = 0; j < column_; j++)
        {

            fout << matrix[i][j] << " ";
            LEMEMLOG((long int)(&(matrix[i][j])), sizeof(int), ID_PGM);
        }

        fout << "\n";
    }
}

handlePGM::~handlePGM()
{
    for (int i = 0; i < row_; i++)
    {
        free(matrix[i]);
    }

    free(matrix);
}