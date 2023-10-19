/*
    Conversor de um arquivo CSV específico para o formato binário (.dat).
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

const string nomeArquivoCsv = "Subnational-period-life-tables-2017-2019-CSV.csv";

struct dados {
    char measure[2];   
    double quantile;   
    char area[42];     
    char sex[6];       
    char age[17];      
    char geography[46];
    char ethnic[8];    
    double value;      
};

void imprimir(dados aux); // imprime todos os dados de uma struct do tipo dados
double removerPorcentagem(string numero); // remove porcentagem no final de qualquer numero em formato string

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
        strcpy(aux.age, palavras[4].c_str());
        strcpy(aux.geography, palavras[5].c_str());
        strcpy(aux.ethnic, palavras[6].c_str());
        aux.value = stod(palavras[7]);

        // escrever struct lida no arquivo binario
        arquivoBinario.write(reinterpret_cast<const char*>(&aux), sizeof(dados));

        qtdStructsLidas++;
    }

    cout << "Arquivo binario (.dat) gerado com sucesso!" << endl;
    cout << "Quantidade de structs lidas do arquivo CSV: " << qtdStructsLidas << endl;

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