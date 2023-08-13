//---------------------------------------------------------------------
// Arquivo	: handlePPM.c
// Conteudo	: implementação da TAD handlePPM 
// Autor	: Ana Lúcia Oliveira de Paula (analop@ufmg.br)
// Historico	: 2022-09-03 - arquivo criado
//---------------------------------------------------------------------

#include "handlePPM.h"
#include "handlePGM.h"

handlePPM::handlePPM(char * file)
//Descricao: Construtor que le o arquivo de entrada e aloca/armazena a matriz PPM dinamicamente
//Entrada: file
{
    std::ifstream fin(file);
    erroAssert(fin,"handlePPM - arquivo de entrada nao foi aberto corretamente");

    file_ = file;

    fin >> id_;
    erroAssert(id_ == "P3", "handlePPM - formato de arquivo invalido"); 

    fin >> column_ >> row_;
    erroAssert (column_ > 0 && row_ > 0, "handlePPM - Tamanho da imagem invalido"); 

    fin >> maxValue_;
    erroAssert (maxValue_<=255, "handlePPM - valor máximo do pixel invalido"); 

    matrix = (Pixels**)malloc(row_*sizeof(Pixels*));

    for (int i=0; i<row_; i++)
    {
        matrix[i] = (Pixels*)malloc(column_*(sizeof(Pixels)));
        erroAssert(matrix[i] != NULL, "Não há memória suficiente para alocação");
        {
            for (int j=0; j<column_; j++)
            {
                fin>>matrix[i][j].r;
                fin>>matrix[i][j].g;
                fin>>matrix[i][j].b;

                if (matrix[i][j].r > maxValue_)
                    matrix[i][j].r = maxValue_;
                if (matrix[i][j].g > maxValue_)
                    matrix[i][j].g = maxValue_;
                if (matrix[i][j].b > maxValue_)
                    matrix[i][j].b = maxValue_;

                ESCREVEMEMLOG((long int)(&(matrix[i][j].r)), sizeof(int), ID_PPM);
                ESCREVEMEMLOG((long int)(&(matrix[i][j].g)), sizeof(int), ID_PPM);
                ESCREVEMEMLOG((long int)(&(matrix[i][j].b)), sizeof(int), ID_PPM);
            }
                
        }
    }
}

long int handlePPM::acessaMatriz()
// Descricao: acessa matriz para fins de registro de acesso 
// Entrada: matriz 
// Saida: matriz
{
  int i, j;
  double aux, s=0.0;
  for (i=0; i<row_; i++){
    for(j=0; j<column_; j++){
      aux = matrix[i][j].r + matrix[i][j].g + matrix[i][j].b;
      s+=aux;
      LEMEMLOG((long int)(&(matrix[i][j].r)), sizeof(int), ID_PPM);
      LEMEMLOG((long int)(&(matrix[i][j].g)), sizeof(int), ID_PPM);
      LEMEMLOG((long int)(&(matrix[i][j].b)), sizeof(int), ID_PPM);
    }
  }
  return s; // apenas para evitar que acesso seja eliminado
}

void handlePPM::convertToPGM(char* file)
//Descricao: cria um ponteiro para classe handlePGM, passando a matriz PPM e seus atributos para criação da TAD manipulara e arzenara a imagem PGM
//Entrada: Nome do arquivo de saida
{
    handlePGM* image = new handlePGM(file, row_, column_, matrix);
    
    //define a fase 1 para fins de registro de memoria
    defineFaseMemLog(1); 
        acessaMatriz();
        image->acessaMatriz();
    //Define a fase 2 para avaliar o desempenho do processo de imprimir a imagem PGM em um arquivo
    defineFaseMemLog(2);
        image->printImage();
        delete image;

}
handlePPM::~handlePPM(){
//Descrição: Função e destroi a matriz PPM
    for (int i=0; i<row_; i++)
    {
        free(matrix[i]);
    }

    free(matrix);
}