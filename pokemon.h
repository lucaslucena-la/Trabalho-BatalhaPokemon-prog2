#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include <vector>
#include "ataque.h"

class Pokemon {
private:
    std::string nome;
    std::string tipo1;
    std::string tipo2;
    int hp;
    int nivel;
    int ataque;
    int defesa;
    int velocidade;
    int ataqueEspecial;
    int defesaEspecial;
    std::vector<Ataque> ataques; // Vetor que vai armazenar os ataques do Pokémon

public:
    // Construtor
    Pokemon(std::string nome, std::string tipo1, std::string tipo2, int hp, int nivel, int ataque, int defesa, int velocidade, int ataqueEspecial, int defesaEspecial);

    // Getters
    std::string getNome() const;
    std::string getTipo1() const;
    std::string getTipo2() const;
    int getHP() const;
    int getNivel() const;
    int getAtaque() const;
    int getDefesa() const;
    int getVelocidade() const;
    int getAtaqueEspecial() const;
    int getDefesaEspecial() const;
    
    // Método para atribuir ataques ao Pokémon
    void adicionarAtaque(Ataque ataque);

    // Método para pegar um ataque por índice
    Ataque getAtaque(int index) const;

    // Exibir detalhes do Pokémon
    void exibirPokemon() const;

    // Função para escolher um ataque e calcular o dano
    int calcularDano(Ataque ataque, Pokemon& oponente);

    // Reduzir HP após receber dano
    void receberDano(int dano);

    // Verifica se o Pokémon está derrotado
    bool estaDerrotado() const;
};

#endif // POKEMON_H
