#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include <vector>
#include "ataque.h"

using namespace std;

class Pokemon {
private:
    string nome;
    string tipo1;
    string tipo2;
    int hp;
    int nivel;
    int ataque;
    int defesa;
    int velocidade;
    int ataqueEspecial;
    int defesaEspecial;
    bool derrotado;  
    vector<Ataque> ataques; 

public:
    // Construtor
    Pokemon(string nome, string tipo1, string tipo2, int hp, int nivel, int ataque, int defesa, int velocidade, int ataqueEspecial, int defesaEspecial);

    // Getters
    string getNome() const;
    string getTipo1() const;
    string getTipo2() const;
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
    
    // Função para escolher um ataque e calcular o dano
    int calcularDano(Ataque ataque, Pokemon& oponente);

    // Reduzir HP após receber dano e atualizar estado de derrota
    void receberDano(int dano);

    // Verifica se o Pokémon está derrotado
    bool estaDerrotado() const;
};

#endif // POKEMON_H
