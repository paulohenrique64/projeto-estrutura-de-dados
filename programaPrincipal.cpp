/*
    Programa para manipular um arquivo binario específico que contem muitos registros.
*/

#include <iostream>
#include <fstream>
using namespace std;

const string nomeArquivo = "arquivoBinario.dat";

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
void imprimir(dados aux);
void menu();
void edicao(fstream& arquivo);
void menuImpressao(fstream& arquivo);
void insercao(fstream& arquivo);

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
            case 4:
                insercao(arquivo);
                break;
            default:
                break;
        }
    } while (opcao != 0);

    arquivo.close();
    return 0;
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
    system("clear || cls");
}

void menu() {
    limparTela();
    cout << "=============== Menu ================\n";
    cout << "\n[1] Menu para impressão dos registros";
    cout << "\n[2] Editar um registro em uma posicao específica";
    cout << "\n[4] Inserir um registro em uma posicao específica";
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
        // posiciona o cursor de leitura no inicio do arquivo binario
        arquivo.seekg(0, arquivo.beg);

        while (arquivo.read((char*)(&aux), sizeof(dados))) {
            imprimir(aux);
        }
    } else {
        int indiceInicio, indiceFinal, indiceAtual;

        limparTela();
        cout << "Informe o indice inicial: ";
        cin >> indiceInicio;

        cout << "Informe o indice final: ";
        cin >> indiceFinal;
        indiceAtual = indiceInicio;
        cout << "\n";

        // posiciona o cursor de leitura no indice inicial escolhido pelo usuario
        arquivo.seekg(indiceInicio * sizeof(dados));

        while (arquivo.read((char*)(&aux), sizeof(dados))) {
            if (indiceAtual >= indiceInicio and indiceAtual <= indiceFinal)  {
                imprimir(aux);
            }

            indiceAtual++;
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

    // posiciona o cursor de escrita na posição do registro a ser editado
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

void insercao(fstream& arquivo) {
    dados aux;
    string buffer;
    int posicao;

    cout << "Digite a posicao do registro que voce deseja editar: ";
    cin >> posicao;

    cout << "Digite os dados do seu novo registro\n";
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

    //movendo o cursor para a posicao desejada
    arquivo.seekg(posicao * sizeof(dados));
    //le o resto do arquivo
    streampos tamanhoArquivo = arquivo.tellg();
    arquivo.seekg(0, ios::end);
    tamanhoArquivo = arquivo.tellg() - tamanhoArquivo;
    char* arquivoRestante = new char[tamanhoArquivo];
    arquivo.read(arquivoRestante, tamanhoArquivo);

    //voltando para a posicao atualizada e escrevendo o proximo elemento
    arquivo.seekp(posicao * sizeof(dados));
    arquivo.write((char*)(&aux), sizeof(dados));
    //escrevendo novamente com deslocamento de 1
    arquivo.write(arquivoRestante, tamanhoArquivo);

    delete [] arquivoRestante;
    arquivo.clear();

    cout << "Elemento adicionado com sucesso!" << endl;

    cout << "\nDigite qualquer coisa para voltar ao menu: ";
    cin.ignore();
    getline(cin, buffer);
}