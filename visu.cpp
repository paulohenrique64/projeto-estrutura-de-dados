#include <iostream>
#include <fstream>
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

int main() {
  ifstream arquivo("arquivoBinario.dat", ios::binary);

  dados aux;
  int cont = 0;

  while (arquivo.read((char *)(&aux), sizeof(dados))) {
    // cout << cont + 1 << "- " << aux.measure << " " << aux.age << " " << aux.area << " " << aux.ethnic << " " << aux.geography << " " << aux.value << endl;
    cont++;
  }

  cout << cont;
}