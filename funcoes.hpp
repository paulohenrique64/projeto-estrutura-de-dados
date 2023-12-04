#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdio>
using namespace std;

// Estrutura de dados para armazenar informações de um registro
struct dados {
  char measure[4];
  double quantile;
  char area[44];
  char sex[8];
  int age;
  char geography[48];
  char ethnic[10];
  double value;
};

// Estrutura que representa um arquivo e seu buffer
struct arquivo {
  ifstream arq;
  int pos, MAX;
  dados *buffer;
};

// Constantes para nomes de arquivos e tamanho máximo
const string nomeArquivoCsv = "Subnational-period-life-tables-2017-2019-CSV.csv";
const string nomeArquivo = "arquivoBinario.dat";
const int N = 35000;

void limparTela(); // Função para limpar a tela do console
void menu(); // Função para exibir o menu principal
void voltarAoMenu(); // Função para pausar e voltar ao menu após uma operação
void imprimir(dados aux); // Função para imprimir os detalhes de um registro
int quantidadeRegistros(); // Função para contar a quantidade total de registros no arquivo
double removerPorcentagem(string numero); // Função para remover o símbolo de porcentagem de uma string e converter para double
int converterIdade(string palavra); // Função para converter uma string que representa a idade para um inteiro
void gerarArquivo(); // Função para gerar um arquivo binário a partir de um arquivo CSV
fstream abrirArquivo(); // Função para abrir um arquivo binário para leitura e escrita

void edicao(int &qtdRegistros); // Função para realizar a edição de um registro
void trocarDePosicao(int &qtdRegistros); // Função para trocar a posição de dois registros
void menuImpressao(int &qtdRegistros); // Função para exibir opções de impressão de registros
void insercao(int &qtdRegistros); // Função para inserir um novo registro em uma posição específica

void mergeSortExterno(string nome); // Função para realizar a ordenação externa do arquivo
int criaArquivosOrdenados(string nome); // Função para criar arquivos ordenados menores a partir de um arquivo maior
double removerPorcentagem(string numero); // Função para remover o símbolo de porcentagem de uma string e converter para double
void salvaArquivo(string nome, dados *vetor, int tamanho); // Função para salvar um vetor de registros ordenados em um arquivo
void ordena(dados *valor, int inicio, int meio, int fim); // Função para realizar a ordenação interna (merge sort)
void ordenacao(dados *valor, int inicio, int fim); // Função para coordenar a ordenação interna dos registros
void merge(string nome, int numArqs, int k); // Função para realizar a mesclagem de arquivos ordenados
void preencheBuffer(arquivo &arq, int k); // Função para preencher o buffer de um arquivo durante a ordenação externa
int procuraMaior(arquivo *arq, int numArqs, int k, dados &menor); // Função para procurar o maior valor em um conjunto de arquivos durante a ordenação externa