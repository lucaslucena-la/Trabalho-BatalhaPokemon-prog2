#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "pokemon.h"
#include "ataque.h"
#include "jogador.h"

struct Ranking {
    int vitoriasFacil;
    int vitoriasMedio;
    int vitoriasDificil;
    int derrotas;
    int pontuacao;
};

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
int escolherAtaqueCPU(const Pokemon& pokemon);

// Função para sortear três Pokémons aleatórios para o jogador e para a CPU
void sortearPokemons(const vector<Pokemon>& pokemons, vector<Pokemon>& jogadorPokemons, vector<Pokemon>& cpuPokemons, int dificuldade);


#endif // UTILS_H
