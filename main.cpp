#include <iostream>
#include <vector>
#include "pokemon.h"
#include "ataque.h"
#include "utils.h"
using namespace std;

int main() {
    // Carregar Pokémons do arquivo
    vector<Pokemon> pokemons = carregarPokemons("pokemons.txt");

    // Carregar Ataques do arquivo
    vector<Ataque> ataques = carregarAtaques("ataques.txt");

    // Atribuir ataques aos Pokémons
    atribuirAtaquesAosPokemons(pokemons, ataques);

    // Sortear três Pokémons para o jogador e três para a CPU
    vector<Pokemon> jogadorPokemons;
    vector<Pokemon> cpuPokemons;
    sortearPokemons(pokemons, jogadorPokemons, cpuPokemons);

    // Exibir Pokémons sorteados para o jogador
    cout << "Seus Pokémons sorteados:" << endl;
    for (auto& p : jogadorPokemons) {
        p.exibirPokemon();
        cout << "------------------------" << endl;
    }

    // Exibir Pokémons sorteados para a CPU
    cout << "Pokémons da CPU:" << endl;
    for (auto& p : cpuPokemons) {
        p.exibirPokemon();
        cout << "------------------------" << endl;
    }

    // Iniciar a batalha com o primeiro Pokémon do jogador e o primeiro da CPU
    Pokemon& jogadorPokemon = jogadorPokemons[0];  // Primeiro Pokémon do jogador
    Pokemon& cpuPokemon = cpuPokemons[0];  // Primeiro Pokémon da CPU

    cout << "A batalha começou entre " << jogadorPokemon.getNome() << " e " << cpuPokemon.getNome() << "!" << endl;

    // Loop da batalha
    while (!jogadorPokemon.estaDerrotado() && !cpuPokemon.estaDerrotado()) {
        // Exibir os ataques do Pokémon do jogador
        cout << jogadorPokemon.getNome() << " - HP: " << jogadorPokemon.getHP() << endl;
        cout << "Escolha um ataque:" << endl;
        for (int i = 0; i < 4; i++) {
            cout << i + 1 << ". " << jogadorPokemon.getAtaque(i).getNome() << endl;
        }

        // Jogador escolhe um ataque
        int escolhaJogador;
        cout << "Escolha o número do ataque: ";
        cin >> escolhaJogador;
        escolhaJogador -= 1;  // Ajustar para o índice (0 a 3)

        // CPU escolhe um ataque aleatório
        int escolhaCPU = escolherAtaqueCPU(cpuPokemon);

        // Jogador ataca primeiro
        Ataque ataqueJogador = jogadorPokemon.getAtaque(escolhaJogador);
        cout << jogadorPokemon.getNome() << " usou " << ataqueJogador.getNome() << "!" << endl;
        int danoJogador = calcularDano(jogadorPokemon, cpuPokemon, ataqueJogador);
        cout << "Causou " << danoJogador << " de dano!" << endl;
        cpuPokemon.receberDano(danoJogador);
        cout << cpuPokemon.getNome() << " agora tem " << cpuPokemon.getHP() << " de HP!" << endl;

        // Verificar se o Pokémon da CPU foi derrotado
        if (cpuPokemon.estaDerrotado()) {
            cout << cpuPokemon.getNome() << " foi derrotado! Você venceu!" << endl;
            break;
        }

        // CPU ataca
        Ataque ataqueCPU = cpuPokemon.getAtaque(escolhaCPU);
        cout << cpuPokemon.getNome() << " usou " << ataqueCPU.getNome() << "!" << endl;
        int danoCPU = calcularDano(cpuPokemon, jogadorPokemon, ataqueCPU);
        cout << "Causou " << danoCPU << " de dano!" << endl;
        jogadorPokemon.receberDano(danoCPU);
        cout << jogadorPokemon.getNome() << " agora tem " << jogadorPokemon.getHP() << " de HP!" << endl;

        // Verificar se o Pokémon do jogador foi derrotado
        if (jogadorPokemon.estaDerrotado()) {
            cout << jogadorPokemon.getNome() << " foi derrotado! Você perdeu!" << endl;
            break;
        }

        cout << "-----------------------------------" << endl;
    }

    return 0;
}
