#include <iostream>
#include <fstream>
using namespace std;

int main() {
  string nome = "jonas";
  ofstream arquivo(nome);
  arquivo << "jonas gay";

  arquivo.close();

  remove(nome.c_str());

  return 0;
}