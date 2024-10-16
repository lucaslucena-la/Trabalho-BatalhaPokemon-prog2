#include "game.h"      // Inclui o cabeçalho do jogo
#include "pokemon.h"   // Inclui o cabeçalho da classe Pokemon
#include "utils.h"     // Inclui utilitários auxiliares
#include <random>      // Inclui a biblioteca para gerar números aleatórios
#include <iostream>    // Biblioteca padrão de entrada/saída
#include <vector>      // Para usar a estrutura de dados vector
#include <algorithm>   // Para usar funções de manipulação de vetores, como remove_if

using namespace std;

// Função para exibir o menu do jogo
void exibirMenu() {
    cout << "----- Menu -----" << endl;
    cout << "1. Iniciar Batalha" << endl;
    cout << "2. Ajustar Dificuldade" << endl;
    cout << "3. Visualizar Ranking" << endl;
    cout << "4. Sair" << endl;
    cout << "Escolha uma opção: ";
}

// Função para ajustar a dificuldade do jogo
// Retorna a nova dificuldade escolhida pelo jogador
int ajustarDificuldade() {
    int novaDificuldade;
    cout << "\nEscolha a dificuldade:" << endl;
    cout << "1. Fácil" << endl;
    cout << "2. Médio" << endl;
    cout << "3. Difícil" << endl;
    cout << "Escolha: ";
    cin >> novaDificuldade;

    // Verifica se a opção escolhida é válida (entre 1 e 3)
    if (novaDificuldade >= 1 && novaDificuldade <= 3) {
        return novaDificuldade; // Retorna a dificuldade escolhida
    } else {
        // Caso a escolha seja inválida, mantém a dificuldade como "Fácil"
        cout << "Opção inválida! Dificuldade será mantida." << endl;
        return 1;  // Dificuldade padrão (fácil)
    }
}

// Função para exibir o ranking (número de vitórias e derrotas)
void exibirRanking(int vitorias, int derrotas) {
    cout << "\n----- Ranking -----" << endl;
    cout << "Vitórias: " << vitorias << endl;
    cout << "Derrotas: " << derrotas << endl;
    cout << "-------------------" << endl;
}

// Função para trocar o Pokémon do jogador
// Permite que o jogador escolha um Pokémon não derrotado
Pokemon& trocarPokemonJogador(vector<Pokemon>& jogadorPokemons) {
    while (true) {
        cout << "\nEscolha um Pokémon para continuar a batalha:" << endl;
        bool pokemonDisponivel = false;  // Variável para verificar se há Pokémons disponíveis

        // Exibe a lista de Pokémons que ainda não foram derrotados
        for (size_t i = 0; i < jogadorPokemons.size(); ++i) {
            if (!jogadorPokemons[i].estaDerrotado()) {  // Verifica se o Pokémon não foi derrotado
                cout << i + 1 << ". " << jogadorPokemons[i].getNome() 
                     << " (HP: " << jogadorPokemons[i].getHP() << ")" << endl;
                pokemonDisponivel = true;  // Marca que há Pokémons disponíveis
            }
        }

        // Se todos os Pokémons foram derrotados, a batalha termina
        if (!pokemonDisponivel) {
            cout << "Todos os seus Pokémons foram derrotados!" << endl;
            exit(0);  // Finaliza o jogo
        }

        int escolha;
        cin >> escolha;
        escolha -= 1;  // Ajusta o índice para a lista de Pokémons (começando de 0)

        // Verifica se o Pokémon escolhido está disponível e não foi derrotado
        if (escolha >= 0 && static_cast<size_t>(escolha) < jogadorPokemons.size() && !jogadorPokemons[escolha].estaDerrotado()) {
            return jogadorPokemons[escolha];  // Retorna o Pokémon escolhido
        } else {
            // Se a escolha for inválida ou o Pokémon já estiver derrotado
            cout << "Este Pokémon já foi derrotado ou a escolha é inválida! Escolha outro." << endl;
        }
    }
}

// Função para a CPU trocar de Pokémon
// A CPU escolhe o primeiro Pokémon não derrotado da lista
Pokemon& trocarPokemonCPU(vector<Pokemon>& cpuPokemons) {
    for (size_t i = 0; i < cpuPokemons.size(); ++i) {
        if (!cpuPokemons[i].estaDerrotado()) {
            return cpuPokemons[i];  // Retorna o primeiro Pokémon não derrotado
        }
    }
    // Se todos os Pokémons da CPU foram derrotados (isso não deve acontecer, mas é uma medida de segurança)
    throw runtime_error("Todos os Pokémons da CPU foram derrotados!");
}


// Função para exibir o histórico de batalha (ações anteriores)
void exibirHistoricoDeBatalha(const vector<string>& log) {
    cout << "\n----- Histórico de Batalha -----\n";
    for (const auto& entrada : log) {
        cout << entrada << endl;  // Exibe cada entrada do histórico
    }
    cout << "-------------------------------\n";
}

// Função para exibir os ataques de um Pokémon
void exibirAtaques(const Pokemon& pokemon) {
    cout << "\nAtaques disponíveis:\n";
    // Exibe os quatro ataques disponíveis para o Pokémon
    for (int i = 0; i < 4; ++i) {
        Ataque ataque = pokemon.getAtaque(i);
        cout << i + 1 << ". " << ataque.getNome() << " - Tipo: " << ataque.getTipo() 
             << " (Categoria: " << ataque.getCategoria() << ")\n";
    }
}

// Função para a CPU escolher um ataque aleatório
// A CPU escolhe aleatoriamente um dos quatro ataques
int escolherAtaqueCPU(const Pokemon& pokemon) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 3);  // Supondo que cada Pokémon tenha 4 ataques
    return dist(gen);  // Retorna um índice aleatório (0 a 3)
}

// Função que verifica se todos os Pokémons de um jogador estão derrotados
bool todosDerrotados(const vector<Pokemon>& pokemons) {
    for (const auto& p : pokemons) {
        if (!p.estaDerrotado()) {
            return false;  // Retorna falso se ainda houver algum Pokémon não derrotado
        }
    }
    return true;  // Retorna verdadeiro se todos os Pokémons foram derrotados
}

// Função que remove os Pokémons derrotados de uma lista
void removerPokemonsDerrotados(vector<Pokemon>& pokemons) {
    pokemons.erase(remove_if(pokemons.begin(), pokemons.end(),
        [](const Pokemon& p) { return p.estaDerrotado(); }), pokemons.end());
}