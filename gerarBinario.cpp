/*
  Programa para converter o arquivo Subnational..CSV.csv para o formato binário (.dat)"

  Alunos: Paulo Henrique dos Anjos Silveira,
  Paulo Henrique Ribeiro Alves e Thiago Ferreira Azevedo

  Universidade Federal de Lavras, 23/10/2023
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

const string nomeArquivoCsv = "Subnational-period-life-tables-2017-2019-CSV.csv";

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

void imprimir(dados aux); // imprime todos os dados de uma struct do tipo dados
double removerPorcentagem(string numero); // remove porcentagem no final de qualquer numero em formato string
int converterIdade(string palavra);

int main() {
  ifstream arquivoCsv(nomeArquivoCsv);
  ofstream arquivoBinario("arquivoBinario.dat", ios::binary);
  string cabecalho, linha, palavras[8];
  stringstream buffer;
  dados aux;
  int qtdStructsLidas = 0;

  // cabecalho
  getline(arquivoCsv, cabecalho);

  while (getline(arquivoCsv, linha)) {
      buffer << linha;
      
      getline(buffer, palavras[0], ',');
      getline(buffer, palavras[1], ',');
      getline(buffer, palavras[2], ',');
      getline(buffer, palavras[3], ',');
      getline(buffer, palavras[4], ',');
      getline(buffer, palavras[5], ',');
      getline(buffer, palavras[6], ',');
      getline(buffer, palavras[7]);

      buffer.clear();

      strcpy(aux.measure, palavras[0].c_str());
      aux.quantile = removerPorcentagem(palavras[1]);
      strcpy(aux.area, palavras[2].c_str());
      strcpy(aux.sex, palavras[3].c_str());

      aux.age = converterIdade(palavras[4]);

      strcpy(aux.geography, palavras[5].c_str());
      strcpy(aux.ethnic, palavras[6].c_str());
      aux.value = stod(palavras[7]);

      // escrever struct lida no arquivo binario
      arquivoBinario.write(reinterpret_cast<char*>(&aux), sizeof(dados));

      qtdStructsLidas++;
    }

  cout << "Arquivo binario (.dat) gerado com sucesso!" << endl;
  cout << "Quantidade de registros lidos do arquivo CSV: " << qtdStructsLidas << endl;

  arquivoCsv.close();
  arquivoBinario.close();

  return 0;
}

double removerPorcentagem(string numero) {
  int tamString = int(numero.size());
  string numeroFormatado;

  for (int i = 0; i < tamString - 1; i++) {
    numeroFormatado[i] = numero[i];
  }     

  return stod(numeroFormatado);
}

void imprimir(dados aux) {
  cout << aux.measure << " " 
    << aux.quantile << " " 
    << aux.area << " " 
    << aux.sex << " " 
    << aux.age << " " 
    << aux.geography << " " 
    << aux.ethnic << " "
    << aux.value << endl;
}

int converterIdade(string palavra) {
  stringstream buffer(palavra);
  int tamPalavra = int(palavra.length()), idade = 0;

  if (tamPalavra <= 8) {
    buffer >> idade;
  } else {
    int idade1, idade2;
    char traco;
    buffer >> idade1 >> traco >> idade2;
    idade = (idade1 + idade2) / 2;
  }

  return idade;
}