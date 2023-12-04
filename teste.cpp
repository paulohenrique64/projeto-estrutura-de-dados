#include <iostream>
using namespace std;

#include "ordenacao.cpp"

int main() {
  string nomeAquivo = "arquivoBinario.dat";

  mergeSortExterno(nomeAquivo);

  return 0;
}