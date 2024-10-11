#ifndef GAME_H
#define GAME_H

#include <vector>
#include "pokemon.h"

// Função para exibir o menu
void exibirMenu();

// Função para ajustar a dificuldade do jogo
int ajustarDificuldade();

// Função para exibir o ranking
void exibirRanking(int vitorias, int derrotas);

// Função para trocar o Pokémon do jogador
Pokemon& trocarPokemonJogador(std::vector<Pokemon>& jogadorPokemons);

// Função para a CPU trocar de Pokémon
Pokemon& trocarPokemonCPU(std::vector<Pokemon>& cpuPokemons);

void exibirPokemons(const std::vector<Pokemon>& pokemons, const std::string& dono);

void exibirHistoricoDeBatalha(const std::vector<std::string>& log);

void exibirAtaques(const Pokemon& pokemon);

int escolherAtaqueCPU(const Pokemon& pokemon);

bool todosDerrotados(const std::vector<Pokemon>& pokemons);  // Use std::vector

void removerPokemonsDerrotados(std::vector<Pokemon>& pokemons);


#endif // GAME_H
