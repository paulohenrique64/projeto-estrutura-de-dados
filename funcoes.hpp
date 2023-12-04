#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdio>
using namespace std;

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

struct arquivo {
  ifstream arq;
  int pos, MAX;
  dados *buffer;
};

const string nomeArquivoCsv = "Subnational-period-life-tables-2017-2019-CSV.csv";
const string nomeArquivo = "arquivoBinario.dat";
const int N = 20000;

void limparTela();
void menu();
void voltarAoMenu();
void imprimir(dados aux);
int quantidadeRegistros();
double removerPorcentagem(string numero); 
int converterIdade(string palavra);
void gerarArquivo();
fstream abrirArquivo();

void edicao(int &qtdRegistros);
void trocarDePosicao(int &qtdRegistros);
void menuImpressao(int &qtdRegistros);
void insercao(int &qtdRegistros);

void mergeSortExterno(string nome);
int criaArquivosOrdenados(string nome);
double removerPorcentagem(string numero);
void salvaArquivo(string nome, dados *vetor, int tamanho);
void ordena(dados *valor, int inicio, int meio, int fim);
void ordenacao(dados *valor, int inicio, int fim);
void merge(string nome, int numArqs, int k);
void preencheBuffer(arquivo &arq, int k);
int procuraMaior(arquivo *arq, int numArqs, int k, dados &menor);