#ifndef GAME_H
#define GAME_H

#include <vector>
#include "pokemon.h"
#include "jogador.h"

// Função para exibir o menu
void exibirMenu();

// Função para ajustar a dificuldade do jogo
int ajustarDificuldade();

// Função para exibir o ranking
void exibirRanking(int vitorias, int derrotas);

// Função para trocar o Pokémon do jogador
Pokemon& trocarPokemonJogador(vector<Pokemon>& jogadorPokemons);

// Função para a CPU trocar de Pokémon
Pokemon& trocarPokemonCPU(vector<Pokemon>& cpuPokemons);

void exibirHistoricoDeBatalha(const vector<string>& log);

void exibirAtaques(const Pokemon& pokemon);

int escolherAtaqueCPU(const Pokemon& pokemon);

bool todosDerrotados(const vector<Pokemon>& pokemons);  // Use vector

void removerPokemonsDerrotados(vector<Pokemon>& pokemons);

void atualizarVitoriaJogador(Jogador& jogadorAtual, int dificuldade, vector<Jogador>& jogadores);

void atualizarDerrotaJogador(Jogador& jogadorAtual, vector<Jogador>& jogadores);



#endif // GAME_H
