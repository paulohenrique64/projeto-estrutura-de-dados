#include "funcoes.hpp"

fstream abrirArquivo() {
  fstream arquivo(nomeArquivo, ios::in | ios::out | ios::binary);

  if (!arquivo.is_open()) {
    throw runtime_error("Não foi possíve abrir o arquivo");
  }
  
  return arquivo;
}

void imprimir(dados aux) {
  cout << "  Measure: " << aux.measure << endl
       << " Quantile: " << aux.quantile << "%" << endl
       << "     Area: " << aux.area << endl
       << "      Sex: " << aux.sex << endl
       << "      Age: " << aux.age << endl
       << "Geography: " << aux.geography << endl
       << "   Ethnic: " << aux.ethnic << endl
       << "    Value: " << aux.value << endl;
  cout << "===========================================================" << endl;
}

void limparTela() {
  system("clear || cls");
}

void menu() {
  limparTela();
  cout << "=============== Menu ================\n";
  cout << "\n[1] Menu para impressão dos registros";
  cout << "\n[2] Editar um registro em uma posicao específica";
  cout << "\n[3] Trocar registros de posicao";
  cout << "\n[4] Inserir um registro em uma posicao específica";
  cout << "\n[5] Ordenar";
  cout << "\n[0] Sair";
  cout << "\n\nDigite uma OPÇÃO e pressione ENTER: ";
}

void voltarAoMenu() {
  string buffer;
  cout << "\nDigite qualquer coisa para voltar ao menu: ";
  cin.ignore();
  getline(cin, buffer);
}

int quantidadeRegistros() {
  fstream arquivo = abrirArquivo();  
  arquivo.seekg(0, ios_base::end);
  return arquivo.tellg() / sizeof(dados);
}

void menuImpressao(int &qtdRegistros) {
  dados aux;
  string buffer;
  int opcao;
  fstream arquivo = abrirArquivo();  

  limparTela();
  cout << "=============== Impressão ================\n";
  cout << "\n[1] Imprimir tudo";
  cout << "\n[0] Imprimir entre determinados indices";
  cout << "\n\nDigite uma OPÇÃO e pressione ENTER: ";
  cin >> opcao;

  if (opcao) {
    // posiciona o cursor de leitura no inicio do arquivo binario
    arquivo.seekg(0, arquivo.beg);

    while (arquivo.read((char *)(&aux), sizeof(dados))) {
      imprimir(aux);
    }
  }
  else {
    int indiceInicio, indiceFinal, indiceAtual;

    limparTela();

    cout << "Quantidade de registros disponíveis: " << qtdRegistros << "\n\n";
    cout << "Informe o indice inicial: ";
    cin >> indiceInicio;

    while (indiceInicio < 0 or indiceInicio > qtdRegistros) {
      cout << "Erro, digite uma posição válida: ";
      cin >> indiceInicio;
    }

    cout << "Informe o indice final: ";
    cin >> indiceFinal;
    indiceAtual = indiceInicio;
    cout << "\n";

    while (indiceFinal < indiceInicio or indiceFinal > qtdRegistros) {
      cout << "Erro, digite uma posição válida: ";
      cin >> indiceFinal;
    }

    // posiciona o cursor de leitura no indice inicial escolhido pelo usuario
    arquivo.seekg(indiceInicio * sizeof(dados));

    while (arquivo.read((char *)(&aux), sizeof(dados))) {
      if (indiceAtual >= indiceInicio and indiceAtual <= indiceFinal) {
        imprimir(aux);
      }

      indiceAtual++;
    }
  }

  voltarAoMenu();
  arquivo.clear();
  arquivo.close();
}

void edicao(int &qtdRegistros) {
  string buffer;
  int posicao;
  dados aux;
  fstream arquivo = abrirArquivo();  

  limparTela();

  cout << "Quantidade de registros disponíveis: " << qtdRegistros << endl;
  cout << "\nDigite a posicao do registro que voce deseja editar: ";
  cin >> posicao;

  while (posicao > qtdRegistros) {
    cout << "Erro, digite uma posição válida: ";
    cin >> posicao;
  }

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

  arquivo.write((char *)(&aux), sizeof(dados));

  voltarAoMenu();
  arquivo.clear();
  arquivo.close();
}

void insercao(int &qtdRegistros) {
  dados novo, aux;
  string buffer;
  int posicao;
  fstream arquivo = abrirArquivo();  

  limparTela();

  cout << "Quantidade de registros disponíveis: " << qtdRegistros << "\n\n";
  cout << "Digite a posicao onde você deseja inserir: ";
  cin >> posicao;

  while (posicao > qtdRegistros) {
    cout << "Erro, digite uma posição válida: ";
    cin >> posicao;
  }

  cout << "Digite os dados do seu novo registro\n";
  cout << "measure: ";
  cin >> novo.measure;

  cout << "quantile: ";
  cin >> novo.quantile;

  cout << "area: ";
  cin >> novo.area;

  cout << "sex: ";
  cin >> novo.sex;

  cout << "age: ";
  cin >> novo.age;

  cout << "geography: ";
  cin >> novo.geography;

  cout << "ethnic: ";
  cin >> novo.ethnic;

  cout << "value: ";
  cin >> novo.value;

  arquivo.seekg(0, arquivo.end);            // Posiciona para leitura no final
  long int tamanho_bytes = arquivo.tellg(); // Conta os bytes
  int tamanho = static_cast<int>(tamanho_bytes / sizeof(dados));

  // Mova do último elemento até a posição desejada
  for (int i = tamanho - 1; i >= posicao; i--) {
    arquivo.seekg(i * sizeof(dados));
    arquivo.read(reinterpret_cast<char *>(&aux), sizeof(dados));
    arquivo.seekp((i + 1) * sizeof(dados));
    arquivo.write(reinterpret_cast<char *>(&aux), sizeof(dados));
  }

  // Mova o cursor para a posição desejada e escreva o novo elemento
  arquivo.seekp(posicao * sizeof(dados));
  arquivo.write(reinterpret_cast<char *>(&novo), sizeof(dados));

  arquivo.clear();

  qtdRegistros++;
  cout << "Elemento adicionado com sucesso!" << endl;
  arquivo.clear();
  arquivo.close();
  voltarAoMenu();
}

void trocarDePosicao(int &qtdRegistros) {
  int posicao1, posicao2;
  dados registro1, registro2;
  string buffer;
  fstream arquivo = abrirArquivo();  

  limparTela();
  cout << "Quantidade de registros disponíveis: " << qtdRegistros << endl;
  cout << "\nDigite as posicoes dos registros que deseja trocar:\n";

  cout << "Primeira posicao:";
  cin >> posicao1;

  while (posicao1 < 0 or posicao1 > qtdRegistros) {
    cout << "Erro, digite uma posição válida: ";
    cin >> posicao1;
  }

  cout << "Segunda posicao:";
  cin >> posicao2;

  while (posicao2 < posicao1 or posicao2 > qtdRegistros) {
    cout << "Erro, digite uma posição válida: ";
    cin >> posicao2;
  }

  arquivo.seekg(posicao1 * sizeof(dados));
  arquivo.read((char *)(&registro1), sizeof(dados));

  arquivo.seekg(posicao2 * sizeof(dados));
  arquivo.read((char *)(&registro2), sizeof(dados));

  arquivo.seekp(posicao1 * sizeof(dados));
  arquivo.write((char *)(&registro2), sizeof(dados));

  arquivo.seekp(posicao2 * sizeof(dados));
  arquivo.write((char *)(&registro1), sizeof(dados));

  cout << "\nTroca efetuada com sucesso!";
  arquivo.clear();
  arquivo.close();
  voltarAoMenu();
}