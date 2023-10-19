#include <iostream>
#include <fstream>
using namespace std;

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

void limparTela();
void menuImpressao(fstream& arquivo);
void imprimir(dados aux);
void menu();
void edicao(fstream& arquivo);

const string nomeArquivo = "arquivoBinario.dat";

int main() {
    fstream arquivo(nomeArquivo, ios::in | ios::out | ios::binary);
    int opcao;
    
    if (not arquivo.is_open()) {
        cerr << "Não foi possível abrir o arquivo!" << endl;
        exit(EXIT_FAILURE);
    }

    do {
        menu();
        cin >> opcao;

        switch (opcao) {
            case 1:
                menuImpressao(arquivo);
                break;
            case 2:
                edicao(arquivo);
                break;
            default:
                break;
        }

    } while (opcao != 0);

    arquivo.close();
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

void limparTela() {
    system("cls | clear");
}

void menu() {
    limparTela();
    cout << "=============== Programa ================\n";
    cout << "\n[1] Imprimir";
    cout << "\n[2] Editar um registro em uma posicao específica";
    cout << "\n[0] Sair";
    cout << "\n\nDigite uma OPÇÃO e pressione ENTER: ";
}

void menuImpressao(fstream& arquivo) {
    dados aux;
    string buffer;
    int opcao;

    limparTela();
    cout << "=============== Impressão ================\n";
    cout << "\n[1] Imprimir tudo";
    cout << "\n[0] Imprimir entre determinados indices";
    cout << "\n\nDigite uma OPÇÃO e pressione ENTER: ";
    cin >> opcao;

    if (opcao) {
        while (arquivo.read((char*)(&aux), sizeof(dados))) {
            imprimir(aux);
        }
    } else {
        int indiceInicio, indiceFinal, cont = 0;

        limparTela();
        cout << "Informe o indice inicial: ";
        cin >> indiceInicio;

        cout << "Informe o indice final: ";
        cin >> indiceFinal;
        cout << "\n";

        arquivo.seekg(indiceInicio * sizeof(dados));
        while (arquivo.read((char*)(&aux), sizeof(dados))) {
            cont++;

            if (cont >= indiceInicio and cont <= indiceFinal)  {
                imprimir(aux);
            }
        }
    }


    cout << "\nDigite qualquer coisa para voltar ao menu: ";
    cin.ignore();
    getline(cin, buffer);
    arquivo.clear();
}

void edicao(fstream& arquivo) {
    string buffer;
    int posicao;
    dados aux;

    limparTela();

    cout << "Digite a posicao do registro que voce deseja editar: ";
    cin >> posicao;

    arquivo.seekp(posicao * sizeof(dados));

    cout << "measure: ";
    cin >> aux.measure;

    cout << "quantile: ";
    cin >> aux.quantile;

    cout << "area: ";
    cin >> aux.area;

    cout << "sex: ";
    cin >> aux.sex;

    cout << "age: ";
    cin >> aux.age;

    cout << "geography: ";
    cin >> aux.geography;

    cout << "ethnic: ";
    cin >> aux.ethnic;

    cout << "value: ";
    cin >> aux.value;

    arquivo.write((char*)(&aux), sizeof(dados));


    cout << "\nDigite qualquer coisa para voltar ao menu: ";
    cin.ignore();
    getline(cin, buffer);
    arquivo.clear();
}