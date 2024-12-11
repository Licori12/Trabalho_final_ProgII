#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Estrutura para representar um carro
struct Carro {
    string marca;  // Marca do carro
    string modelo; // Modelo do carro
    int ano;       // Ano de fabricação
    double valor;  // Valor do carro
};

// Lê uma string do usuário com uma mensagem de prompt
string lerString(string mensagem) {
    string valor;
    cout << mensagem;
    getline(cin, valor);
    return valor;
}

// Lê um inteiro positivo do usuário com validação de entrada
int lerInteiroPositivo(string mensagem) {
    int valor;
    while (true) {
        cout << mensagem;
        cin >> valor;
        if (cin.fail() || valor <= 0) { // Verifica se a entrada é inválida
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Insira um numero inteiro positivo.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break; // Sai do loop quando o valor é válido
        }
    }
    return valor;
}

// Lê um número decimal positivo do usuário com validação de entrada
double lerDoublePositivo(string mensagem) {
    double valor;
    while (true) {
        cout << mensagem;
        cin >> valor;
        if (cin.fail() || valor <= 0) { // Verifica se a entrada é inválida
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Insira um numero decimal positivo.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break; // Sai do loop quando o valor é válido
        }
    }
    return valor;
}

// Ordena um vetor de carros usando o algoritmo Bubble Sort
// O parâmetro 'ordenarPorAno' define se a ordenação será feita por ano ou por valor
void bubbleSort(Carro* carros, int n, bool ordenarPorAno = true) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            bool condicao = ordenarPorAno ? (carros[j].ano > carros[j + 1].ano)
                                          : (carros[j].valor > carros[j + 1].valor);
            if (condicao) { // Realiza a troca se necessário
                Carro temp = carros[j];
                carros[j] = carros[j + 1];
                carros[j + 1] = temp;
            }
        }
    }
}

// Busca binária em um vetor de carros ordenado pelo valor
// Retorna o índice do carro encontrado ou -1 se não for encontrado
int buscaBinaria(Carro* carros, int esquerda, int direita, double valorBuscado) {
    if (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;

        if (carros[meio].valor == valorBuscado)
            return meio; // Retorna o índice se o valor for encontrado

        if (carros[meio].valor > valorBuscado)
            return buscaBinaria(carros, esquerda, meio - 1, valorBuscado); // Busca na metade esquerda

        return buscaBinaria(carros, meio + 1, direita, valorBuscado); // Busca na metade direita
    }
    return -1; // Valor não encontrado
}

// Exibe um relatório dos carros cadastrados, ordenados por ano ou valor
void exibirRelatorio(Carro* carros, int n, bool ordenarPorAno) {
    bubbleSort(carros, n, ordenarPorAno); // Ordena os carros antes de exibir
    cout << "\nRelatorio de veiculos cadastrados (ordenado por "
         << (ordenarPorAno ? "ano" : "valor") << "):\n";
    cout << "----------------------------------\n";
    for (int i = 0; i < n; i++) { // Exibe os dados de cada carro
        cout << "Carro " << i + 1 << ": " << carros[i].marca << " "
             << carros[i].modelo << " " << carros[i].ano 
             << " R$ " << carros[i].valor << "\n";
    }
    cout << "----------------------------------\n";
}

// Menu para escolha do tipo de relatório (por ano ou valor)
void menuRelatorio(Carro* carros, int n) {
    int opcaoRelatorio;
    do {
        cout << "\nMenu de Relatorios:\n";
        cout << "1. Relatorio por ano\n";
        cout << "2. Relatorio por valor\n";
        cout << "3. Voltar ao menu principal\n";
        cout << "Escolha uma opcao: ";
        cin >> opcaoRelatorio;

        switch (opcaoRelatorio) {
            case 1:
                exibirRelatorio(carros, n, true); // Exibe relatório por ano
                break;
            case 2:
                exibirRelatorio(carros, n, false); // Exibe relatório por valor
                break;
            case 3:
                cout << "Voltando ao menu principal...\n";
                break;
            default:
                cout << "Opcao invalida. Tente novamente.\n";
        }
    } while (opcaoRelatorio != 3);
}

// Função para cadastrar novos veículos
Carro* cadastrarVeiculos(Carro* carros, int& n) {
    int quantidade;
    cout << "Quantos veiculos deseja cadastrar? ";
    quantidade = lerInteiroPositivo("");

    // Realoca memória para armazenar os novos carros
    Carro* novosCarros = new Carro[n + quantidade];
    for (int i = 0; i < n; i++) {
        novosCarros[i] = carros[i];
    }

    // Lê os dados dos novos carros
    for (int i = 0; i < quantidade; i++) {
        cout << "Cadastro do veiculo " << n + i + 1 << ":\n";
        novosCarros[n + i].marca = lerString("Marca: ");
        novosCarros[n + i].modelo = lerString("Modelo: ");
        novosCarros[n + i].ano = lerInteiroPositivo("Ano: ");
        novosCarros[n + i].valor = lerDoublePositivo("Valor: ");
    }

    n += quantidade; // Atualiza a quantidade total de carros
    delete[] carros; // Libera a memória do vetor antigo
    return novosCarros;
}

// Função principal do programa
int main() {
    int n = 5; // Número inicial de carros cadastrados
    Carro* carros = new Carro[n]{ // Carros pré-cadastrados
        {"Toyota", "Corolla", 2015, 60000.0},
        {"Honda", "Civic", 2020, 80000.0},
        {"Ford", "Fiesta", 2012, 30000.0},
        {"Chevrolet", "Cruze", 2018, 70000.0},
        {"Hyundai", "HB20", 2019, 50000.0}
    };

    int opcaoMenu;
    do {
        // Exibe o menu principal
        cout << "\nMenu Principal:\n";
        cout << "1. Cadastrar veiculos\n";
        cout << "2. Exibir Relatorio\n";
        cout << "3. Buscar veiculo por valor\n";
        cout << "4. Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcaoMenu;

        switch (opcaoMenu) {
            case 1:
                carros = cadastrarVeiculos(carros, n); // Chama a função de cadastro
                break;
            case 2:
                menuRelatorio(carros, n); // Chama o menu de relatórios
                break;
            case 3: {
                double valorBuscado;
                cout << "\nDigite o valor do carro para buscar: ";
                valorBuscado = lerDoublePositivo("");
                int indice = buscaBinaria(carros, 0, n - 1, valorBuscado); // Busca binária
                if (indice != -1) {
                    cout << "\nCarro encontrado:\n"
                         << carros[indice].marca << " " << carros[indice].modelo << " " 
                         << carros[indice].ano << " R$ " << carros[indice].valor << endl;
                } else {
                    cout << "\nCarro nao encontrado.\n";
                }
                break;
            }
            case 4:
                cout << "Encerrando o programa...\n";
                break;
            default:
                cout << "Opcao invalida. Tente novamente.\n";
        }
    } while (opcaoMenu != 4);

    delete[] carros; // Libera a memória ao finalizar o programa
    return 0;
}
