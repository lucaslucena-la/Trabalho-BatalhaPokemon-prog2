#include "ataque.h"

// Construtor padrão
Ataque::Ataque() : nome(""), categoria(""), poder(0), precisao(0.0), tipo("") {}

// Construtor personalizado
Ataque::Ataque(string nome, string categoria, int poder, float precisao, string tipo)
    : nome(nome), categoria(categoria), poder(poder), precisao(precisao), tipo(tipo) {}

// Getters
string Ataque::getNome() const { return nome; }
string Ataque::getCategoria() const { return categoria; }
string Ataque::getTipo() const { return tipo; }
int Ataque::getPoder() const { return poder; }
float Ataque::getPrecisao() const { return precisao; }
