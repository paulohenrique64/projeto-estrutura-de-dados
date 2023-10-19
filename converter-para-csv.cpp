#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

const string nomeArquivo = "Subnational-period-life-tables-2017-2019-CSV.csv";

struct dados {
    char measure[200];
    char quantile[200];
    char area[200];
    char sex[200];
    char age[200];
    char geography[200];
    char ethnic[200];
    int value;
};

void imprimir(dados aux);

int main() {
    ifstream arquivoCsv(nomeArquivo);
    ofstream arquivoBinario("arquivoBinario.dat", ios::binary);
    string cabecalho, linha, palavras[8];
    stringstream buffer;
    dados aux;

    // cabecalho
    getline(arquivoCsv, cabecalho);

    int cont = 0;
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
        strcpy(aux.quantile, palavras[1].c_str());
        strcpy(aux.area, palavras[2].c_str());
        strcpy(aux.sex, palavras[3].c_str());
        strcpy(aux.age, palavras[4].c_str());
        strcpy(aux.geography, palavras[5].c_str());
        strcpy(aux.ethnic, palavras[6].c_str());
        aux.value = stoi(palavras[7]);

        //imprimir(aux);
        arquivoBinario.write(reinterpret_cast<const char*>(&aux), sizeof(dados));

        cont++;
    }

    arquivoCsv.close();
    arquivoBinario.close();
    
    cout << cont << endl;

    return 0;
}

void imprimir(dados aux) {
    cout << aux.measure << " " 
        << aux.quantile << " " 
        << aux.area << " " 
        << aux.sex << " " 
        << aux.age << " " 
        << aux.geography << " " 
        << aux.ethnic 
        << aux.value << endl;
}