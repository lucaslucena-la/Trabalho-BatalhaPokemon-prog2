#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "pokemon.h"
#include "ataque.h"

// Função para carregar Pokémons a partir de um arquivo
std::vector<Pokemon> carregarPokemons(const std::string& nomeArquivo);

// Função para carregar Ataques a partir de um arquivo
std::vector<Ataque> carregarAtaques(const std::string& nomeArquivo);

// Função para verificar se um ataque pode ser atribuído ao Pokémon
bool podeAtribuirAtaque(const Pokemon& pokemon, const Ataque& ataque);

// Função para atribuir ataques aleatórios a cada Pokémon
void atribuirAtaquesAosPokemons(std::vector<Pokemon>& pokemons, const std::vector<Ataque>& ataques);

// Função para calcular dano
int calcularCritico();
int calcularAleatorio();
float calcularEficacia(const Ataque& ataque, const Pokemon& defensor);
float calcularSTAB(const Ataque& ataque, const Pokemon& atacante);
int calcularDano(const Pokemon& atacante, const Pokemon& defensor, const Ataque& ataque);

// Função para a CPU escolher um ataque aleatório
int escolherAtaqueCPU(const Pokemon& pokemon);

// Função para sortear três Pokémons aleatórios para o jogador e para a CPU
void sortearPokemons(const std::vector<Pokemon>& pokemons, std::vector<Pokemon>& jogadorPokemons, std::vector<Pokemon>& cpuPokemons);

#endif // UTILS_H
