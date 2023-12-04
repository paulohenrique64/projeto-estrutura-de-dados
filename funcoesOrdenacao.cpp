#include "funcoes.hpp"

/* recebe o nome do arquivo CSV e o ordena */
void mergeSortExterno(string nome) {
  string novo;
  int numArqs = criaArquivosOrdenados(nome);
  int k = N / (numArqs + 1);

  remove(nome.c_str());

  merge(nome, numArqs, k);

  for (int i = 0; i < numArqs; i++) {
    novo = "Temp" + to_string(i + 1) + ".dat";
    remove(novo.c_str());
  }
}

/* divide o arquivo maior em varios arquivos menores e 
ordena estes arquivos menores */
int criaArquivosOrdenados(string nome) {
  string novo;
  dados aux;
  dados *vetor = new dados[N];
  int cont = 0, total = 0;
  ifstream arq(nome, ios::binary);

  while (arq.read((char *)(&aux), sizeof(dados))) {
    vetor[total] = aux;
    total++;

    if (total == N) {
      cont++;
      novo = "Temp" + to_string(cont) + ".dat";
      cout << novo << endl;
      ordenacao(vetor, 0, total - 1);
      salvaArquivo(novo, vetor, total);
      total = 0;
    }
  }

  if (total > 0) {
    cont++;
    novo = "Temp" + to_string(cont) + ".dat";
    cout << novo << endl;
    ordenacao(vetor, 0, total - 1);
    salvaArquivo(novo, vetor, total);
    total = 0;
  }

  delete[] vetor;
  arq.close();
  return cont;
}

void ordena(dados *valor, int inicio, int meio, int fim) {
  int i = inicio, j = meio + 1;
  int tamanho = fim - inicio + 1;
  dados *aux = new dados[tamanho];

  for (int k = 0; k < tamanho; k++) {
    
    // i e j ainda nao acabaram
    if ((i <= meio) and (j <= fim)) {

      if (valor[i].age > valor[j].age) {
        aux[k] = valor[i];
        i++;
      } else if (valor[j].age > valor[i].age) {
        aux[k] = valor[j];
        j++;
      } else {
        if (valor[i].value > valor[j].value) {
          aux[k] = valor[i];
          i++;
        } else {
          aux[k] = valor[j];
          j++;
        }
      }

    } else if (i > meio) {
      aux[k] = valor[j];
      j++;
    } else {
      aux[k] = valor[i];
      i++;
    }
  }

  for (int k = 0; k < tamanho; k++) {
    valor[inicio + k] = aux[k];
  }

  delete[] aux;
}

// ordenar por identificador (merge sort)
void ordenacao(dados *valor, int inicio, int fim) {
  if (inicio < fim) {
    int meio = (inicio + fim) / 2;
    ordenacao(valor, inicio, meio);
    ordenacao(valor, meio + 1, fim);
    ordena(valor, inicio, meio, fim);
  }
}

/* função para salvar o vetor ordenado em um arquivo */
void salvaArquivo(string nome, dados *vetor, int tamanho) {
  ofstream arq(nome, ios::app | ios::binary);
  for (int i = 0; i < tamanho; i++) {
    arq.write((char *)(&vetor[i]), sizeof(dados));
  }
  arq.close();
}

void merge(string nome, int numArqs, int k) {
  string novo;  
  dados *buffer = new dados[k], menor;
  int qtdBuffer = 0;

  arquivo *arq = new arquivo[numArqs];

  for (int i = 0; i < numArqs; i++)  {
    novo = "Temp" + to_string(i + 1) + ".dat";
    arq[i].arq.open(novo, ios::binary);
    arq[i].MAX = 0;
    arq[i].pos = 0;
    arq[i].buffer = new dados[k];
    preencheBuffer(arq[i], k);
  }

  while (procuraMaior(arq, numArqs, k, menor) == 1) {
    buffer[qtdBuffer] = menor;
    qtdBuffer++;
    if (qtdBuffer == k) {
      salvaArquivo(nome, buffer, k);
      qtdBuffer = 0;
    }
  }

  if (qtdBuffer != 0) {
    salvaArquivo(nome, buffer, qtdBuffer);
  }

  for (int i = 0; i < numArqs; i++) {
    delete[] arq[i].buffer;
  }

  delete[] arq;
  delete[] buffer;
}

int procuraMaior(arquivo *arq, int numArqs, int k, dados &menor) {
  int idx = -1;

  for (int i = 0; i < numArqs; i++) {
    if (arq[i].pos < arq[i].MAX) {
      if (idx == -1) {
        idx = i;
      } else {
        if (arq[i].buffer[arq[i].pos].age > arq[idx].buffer[arq[idx].pos].age) {
          idx = i;
        } else if (arq[i].buffer[arq[i].pos].age == arq[idx].buffer[arq[idx].pos].age) {
          if (arq[i].buffer[arq[i].pos].value > arq[idx].buffer[arq[idx].pos].value) {
            idx = i;
          }
        }
      }
    }
  }

  if (idx != -1) {
    menor = arq[idx].buffer[arq[idx].pos];
    arq[idx].pos++;
    if (arq[idx].pos == arq[idx].MAX) 
      preencheBuffer(arq[idx], k);
    return 1;
  } else {
    return 0;
  }
}

void preencheBuffer(arquivo &arq, int k) {  
  dados aux;

  if (!arq.arq.is_open()) 
    return;

  arq.pos = 0;
  arq.MAX = 0;

  for (int i = 0; i < k; i++) {
    if (arq.arq.read((char *)(&aux), sizeof(dados))) {
      arq.buffer[arq.MAX] = aux;
      arq.MAX++;
    } else {
      arq.arq.close();
      i = k;
    }
  }
}
