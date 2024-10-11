#include "game.h"
#include "pokemon.h"
#include "utils.h"
#include <random>
#include <iostream>
#include <vector>  // Certifique-se de incluir <vector>
#include <algorithm>  // Adicionar esta linha para incluir remove_if


using namespace std;

// Função para exibir o menu

void exibirMenu() {
    cout << "----- Menu -----" << endl;
    cout << "1. Iniciar Batalha" << endl;
    cout << "2. Ajustar Dificuldade" << endl;
    cout << "3. Visualizar Ranking" << endl;
    cout << "4. Sair" << endl;
    cout << "Escolha uma opção: ";
}

// Função para ajustar a dificuldade do jogo
int ajustarDificuldade() {
    int novaDificuldade;
    cout << "\nEscolha a dificuldade:" << endl;
    cout << "1. Fácil" << endl;
    cout << "2. Médio" << endl;
    cout << "3. Difícil" << endl;
    cout << "Escolha: ";
    cin >> novaDificuldade;

    if (novaDificuldade >= 1 && novaDificuldade <= 3) {
        return novaDificuldade; // Retorna a dificuldade escolhida
    } else {
        cout << "Opção inválida! Dificuldade será mantida." << endl;
        return 1;  // Mantém a dificuldade padrão como Fácil se a escolha for inválida
    }
}

// Função para exibir o ranking
void exibirRanking(int vitorias, int derrotas) {
    cout << "\n----- Ranking -----" << endl;
    cout << "Vitórias: " << vitorias << endl;
    cout << "Derrotas: " << derrotas << endl;
    cout << "-------------------" << endl;

}

// Função para trocar o Pokémon do jogador
Pokemon& trocarPokemonJogador(vector<Pokemon>& jogadorPokemons) {
    while (true) {
        cout << "\nEscolha um Pokémon para continuar a batalha:" << endl;
        bool pokemonDisponivel = false;

        // Exibir lista de Pokémons não derrotados
        for (size_t i = 0; i < jogadorPokemons.size(); ++i) {
            if (!jogadorPokemons[i].estaDerrotado()) {  // Verifica se o Pokémon não foi derrotado
                cout << i + 1 << ". " << jogadorPokemons[i].getNome() << " (HP: " << jogadorPokemons[i].getHP() << ")" << endl;
                pokemonDisponivel = true;
            }
        }

        // Se não houver mais Pokémons disponíveis, a batalha é encerrada
        if (!pokemonDisponivel) {
            cout << "Todos os seus Pokémons foram derrotados!" << endl;
            exit(0);  // Sai do jogo ou finaliza a batalha de outra forma
        }

        int escolha;
        cin >> escolha;
        escolha -= 1;  // Ajusta para o índice do vetor

        // Verifica se o Pokémon escolhido está disponível e não derrotado
        if (escolha >= 0 && static_cast<size_t>(escolha) < jogadorPokemons.size() && !jogadorPokemons[escolha].estaDerrotado()) {
            return jogadorPokemons[escolha];
        } else {
            cout << "Este Pokémon já foi derrotado ou a escolha é inválida! Escolha outro." << endl;
        }
    }
}

Pokemon& trocarPokemonCPU(std::vector<Pokemon>& cpuPokemons) {
    for (size_t i = 0; i < cpuPokemons.size(); ++i) {
        if (!cpuPokemons[i].estaDerrotado()) {
            return cpuPokemons[i];  // Retorna o primeiro Pokémon não derrotado
        }
    }
    // Se todos os Pokémons foram derrotados (não deveria acontecer, mas como fallback):
    throw runtime_error("Todos os Pokémons da CPU foram derrotados!");
}

void exibirPokemons(const vector<Pokemon>& pokemons, const string& dono) {
    cout << "\n----- Pokémons de " << dono << " -----\n";
    for (const auto& p : pokemons) {
        cout << p.getNome() << " - HP: " << p.getHP();
        if (p.estaDerrotado()) {
            cout << " (Derrotado)";
        }
        cout << endl;
    }
    cout << "-------------------------------\n";
}

void exibirHistoricoDeBatalha(const vector<string>& log) {
    cout << "\n----- Histórico de Batalha -----\n";
    for (const auto& entrada : log) {
        cout << entrada << endl;
    }
    cout << "-------------------------------\n";
}

void exibirAtaques(const Pokemon& pokemon) {
    cout << "\nAtaques disponíveis:\n";
    for (int i = 0; i < 4; ++i) {
        Ataque ataque = pokemon.getAtaque(i);
        cout << i + 1 << ". " << ataque.getNome() << " - Tipo: " << ataque.getTipo() << " (Categoria: " << ataque.getCategoria() << ")\n";
    }
}

int escolherAtaqueCPU(const Pokemon& pokemon) {
    // CPU escolhe um ataque aleatório
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 3); // Supondo que cada Pokémon tenha 4 ataques
    return dist(gen);
}

bool todosDerrotados(const vector<Pokemon>& pokemons) {
    for (const auto& p : pokemons) {
        if (!p.estaDerrotado()) {
            return false;  // Se algum Pokémon não foi derrotado, retorna falso
        }
    }
    return true;  // Todos os Pokémons foram derrotados
}

void removerPokemonsDerrotados(std::vector<Pokemon>& pokemons) {
    pokemons.erase(std::remove_if(pokemons.begin(), pokemons.end(),
        [](const Pokemon& p) { return p.estaDerrotado(); }), pokemons.end());
}


