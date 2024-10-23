#ifndef GAME_H
#define GAME_H

#include <vector>
#include "pokemon.h"
#include "jogador.h"
#include <string>
#include "ataque.h"
#include <algorithm> 
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>  // Para sortear ataques aleatórios
#include <cmath>

using namespace std;

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

int escolherAtaqueAleatorioCPU(const Pokemon& pokemon);

bool todosDerrotados(const vector<Pokemon>& pokemons);  // Use vector

void removerPokemonsDerrotados(vector<Pokemon>& pokemons);

void atualizarVitoriaJogador(Jogador& jogadorAtual, int dificuldade, vector<Jogador>& jogadores);

void atualizarDerrotaJogador(Jogador& jogadorAtual, vector<Jogador>& jogadores);

// Função para carregar Pokémons a partir de um arquivo
vector<Pokemon> carregarPokemons(const string& nomeArquivo);

// Função para carregar Ataques a partir de um arquivo
vector<Ataque> carregarAtaques(const string& nomeArquivo);

// Função para verificar se um ataque pode ser atribuído ao Pokémon
bool podeAtribuirAtaque(const Pokemon& pokemon, const Ataque& ataque);

// Função para atribuir ataques aleatórios a cada Pokémon
void atribuirAtaquesAosPokemons(vector<Pokemon>& pokemons, const vector<Ataque>& ataques);

// Função para calcular dano
int calcularCritico();
int calcularAleatorio();
float calcularEficacia(const Ataque& ataque, const Pokemon& defensor);
float calcularSTAB(const Ataque& ataque, const Pokemon& atacante);
int calcularDano(const Pokemon& atacante, const Pokemon& defensor, const Ataque& ataque);

// Função para a CPU escolher um ataque aleatório
int escolherAtaqueCPU(const Pokemon& cpuPokemon, const Pokemon& jogadorPokemon, int dificuldade);

// Função para sortear três Pokémons aleatórios para o jogador e para a CPU
void sortearPokemons(const vector<Pokemon>& pokemons, vector<Pokemon>& jogadorPokemons, vector<Pokemon>& cpuPokemons, int dificuldade);


#endif // GAME_H
