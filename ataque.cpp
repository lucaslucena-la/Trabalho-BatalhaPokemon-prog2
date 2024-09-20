#include "ataque.h"
using namespace std;

// Construtor da classe Ataque
Ataque::Ataque(string nome, string categoria, int poder, float precisao, string tipo)
    : nome(nome), categoria(categoria), poder(poder), precisao(precisao), tipo(tipo) {}

// Getters
string Ataque::getNome() const { return nome; }
string Ataque::getCategoria() const { return categoria; }
int Ataque::getPoder() const { return poder; }
float Ataque::getPrecisao() const { return precisao; }
string Ataque::getTipo() const { return tipo; }
