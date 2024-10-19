#include "jogador.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// Construtor
Jogador::Jogador(string nome) : nome(nome), vitoriasFacil(0), vitoriasMedio(0), vitoriasDificil(0), derrotas(0), pontuacao(0) {}

// Getters
string Jogador::getNome() const {
    return nome;
}

int Jogador::getVitoriasFacil() const {
    return vitoriasFacil;
}

int Jogador::getVitoriasMedio() const {
    return vitoriasMedio;
}

int Jogador::getVitoriasDificil() const {
    return vitoriasDificil;
}

int Jogador::getDerrotas() const {
    return derrotas;
}

int Jogador::getPontuacao() const {
    return pontuacao;
}

//setters

// Função para atualizar vitórias no modo fácil
void Jogador::setVitoriasFacil(int vitorias) {
    this->vitoriasFacil = vitorias;
}

// Função para atualizar vitórias no modo médio
void Jogador::setVitoriasMedio(int vitorias) {
    this->vitoriasMedio = vitorias;
}

// Função para atualizar vitórias no modo difícil
void Jogador::setVitoriasDificil(int vitorias) {
    this->vitoriasDificil = vitorias;
}

// Função para atualizar derrotas
void Jogador::setDerrotas(int derrotas) {
    this->derrotas = derrotas;
}

// Função para atualizar pontuação
void Jogador::setPontuacao(int pontuacao) {
    this->pontuacao = pontuacao;
}



// Adiciona uma vitória baseada na dificuldade
void Jogador::adicionarVitoria(int dificuldade) {
    if (dificuldade == 1) {
        vitoriasFacil++;
        pontuacao += 10;
    } else if (dificuldade == 2) {
        vitoriasMedio++;
        pontuacao += 20;
    } else if (dificuldade == 3) {
        vitoriasDificil++;
        pontuacao += 30;
    }
}

// Adiciona uma derrota
void Jogador::adicionarDerrota() {
    derrotas++;
}

// Exibe as informações do jogador
void Jogador::exibirJogador() const {
    cout << "Nome: " << nome << "\nVitórias (Fácil): " << vitoriasFacil 
         << "\nVitórias (Médio): " << vitoriasMedio 
         << "\nVitórias (Difícil): " << vitoriasDificil 
         << "\nDerrotas: " << derrotas 
         << "\nPontuação: " << pontuacao << endl;
}

// Função para carregar jogadores de um arquivo
vector<Jogador> carregarJogadores(const string& arquivo) {
    vector<Jogador> jogadores;
    ifstream inFile(arquivo);
    
    // Verifica se o arquivo foi aberto corretamente
    if (!inFile.is_open()) {
        cerr << "Erro ao abrir o arquivo de jogadores: " << arquivo << endl;
        return jogadores;  // Retorna um vetor vazio
    }

    string nome;
    int vitoriasFacil, vitoriasMedio, vitoriasDificil, derrotas, pontuacao;

    // Loop para ler os jogadores linha por linha
    while (inFile >> nome >> vitoriasFacil >> vitoriasMedio >> vitoriasDificil >> derrotas >> pontuacao) {
        Jogador jogador(nome);
        jogador.setVitoriasFacil(vitoriasFacil);   // Atualiza as vitórias no modo fácil
        jogador.setVitoriasMedio(vitoriasMedio);   // Atualiza as vitórias no modo médio
        jogador.setVitoriasDificil(vitoriasDificil); // Atualiza as vitórias no modo difícil
        jogador.setDerrotas(derrotas);   // Atualiza o número de derrotas
        jogador.setPontuacao(pontuacao); // Atualiza a pontuação
        
        jogadores.push_back(jogador); // Adiciona o jogador ao vetor
    }

    inFile.close();  // Fecha o arquivo após a leitura
    return jogadores; // Retorna o vetor com os jogadores
}

// Função para salvar jogadores no arquivo
void salvarJogadores(const vector<Jogador>& jogadores, const string& arquivo) {
    ofstream outFile(arquivo);
    if (!outFile.is_open()) {
        cerr << "Erro ao abrir o arquivo de jogadores para salvar." << endl;
        return;
    }

    cout << "Salvando jogadores no arquivo...\n";  // Mensagem de debug

    // Percorre todos os jogadores e salva suas informações no arquivo
    for (const auto& jogador : jogadores) {
        cout << "Salvando jogador: " << jogador.getNome() << endl;  // Debug para cada jogador
        outFile << jogador.getNome() << " " 
                << jogador.getVitoriasFacil() << " " 
                << jogador.getVitoriasMedio() << " " 
                << jogador.getVitoriasDificil() << " "
                << jogador.getDerrotas() << " "
                << jogador.getPontuacao() << "\n";
    }

    outFile.close();
    cout << "Jogadores salvos com sucesso." << endl;  // Mensagem de debug
}


// Função para selecionar ou cadastrar um novo jogador
Jogador selecionarJogador(vector<Jogador>& jogadores) {
    cout << "----- Lista de Jogadores -----" << endl;
    for (size_t i = 0; i < jogadores.size(); ++i) {
        cout << i + 1 << ". " << jogadores[i].getNome() << " - Pontuação: " << jogadores[i].getPontuacao() << endl;
    }
    cout << jogadores.size() + 1 << ". Cadastrar novo jogador" << endl;

    int opcao;
    cout << "Escolha uma opção: ";
    cin >> opcao;

    // Se o jogador já existe, retorna o jogador existente sem alterar dados
    if (opcao >= 1 && static_cast<size_t>(opcao) <= jogadores.size()) {
        return jogadores[opcao - 1];  // Retorna o jogador existente sem sobrescrever
    } else if (opcao == static_cast<int>(jogadores.size()) + 1) {
        // Cadastrar novo jogador
        cout << "Digite o nome do novo jogador: ";
        string nome;
        cin >> nome;
        Jogador novoJogador(nome);  // Cria um novo jogador
        jogadores.push_back(novoJogador);  // Adiciona o novo jogador à lista
        return novoJogador;
    } else {
        cout << "Opção inválida!" << endl;
        return selecionarJogador(jogadores);  // Tenta novamente
    }
}

// Função para registrar uma vitória do jogador
void registrarVitoria(Jogador& jogador, int dificuldade, vector<Jogador>& jogadores, const string& arquivo) {
    // Atualiza o número de vitórias com base na dificuldade
    if (dificuldade == 1) {
        jogador.adicionarVitoria(1);  // Vitória no modo fácil
    } else if (dificuldade == 2) {
        jogador.adicionarVitoria(2);  // Vitória no modo médio
    } else if (dificuldade == 3) {
        jogador.adicionarVitoria(3);  // Vitória no modo difícil
    }
    // Atualiza o arquivo de jogadores
    salvarJogadores(jogadores, arquivo);
}

// Função para registrar uma derrota do jogador
void registrarDerrota(Jogador& jogador, vector<Jogador>& jogadores, const string& arquivo) {
    // Atualiza o número de derrotas
    jogador.adicionarDerrota();
    // Atualiza o arquivo de jogadores
    salvarJogadores(jogadores, arquivo);
}

