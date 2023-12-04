/*
  Programa para manipular o arquivo binário arquivoBinario.dat, contendo um menu para
  funções de adição, impressão e edição dos registros"

  Alunos: Paulo Henrique dos Anjos Silveira,
          Paulo Henrique Ribeiro Alves,
          Thiago Ferreira Azevedo

  Universidade Federal de Lavras, 23/10/2023
*/

#include <iostream>
#include <fstream>
#include "funcoes.hpp"

using namespace std;

int main() {

  try {
    abrirArquivo();
  } catch(runtime_error& e) {
    cout << "Arquivo binário não existe" << endl;
    cout << "Gerando arquivo binário a partir do CSV..." << endl;
    gerarArquivo();
  }

  int opcao, qtdRegistros = quantidadeRegistros();

  do {
    menu();
    cin >> opcao;

    switch (opcao) {
      case 1:
        menuImpressao(qtdRegistros);
        break;
      case 2:
        edicao(qtdRegistros);
        break;
      case 3:
        trocarDePosicao(qtdRegistros);
        break;
      case 4:
        insercao(qtdRegistros);
        break;
      case 5:
        mergeSortExterno(nomeArquivo);
        break; 
      default:
        break;
    }
  } while (opcao != 0);

  return 0;
}