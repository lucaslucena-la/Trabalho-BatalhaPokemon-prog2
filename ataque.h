#ifndef ATAQUE_H
#define ATAQUE_H

#include <string>
#include <iostream>

using namespace std;

class Ataque {
private:
    string nome;
    string categoria;
    int poder;
    float precisao;
    string tipo;

public:
    // Construtor padrão
    Ataque();

    // Construtor personalizado (sem qualificação "Ataque::")
    Ataque(string nome, string categoria, int poder, float precisao, string tipo);

    // Getters e outros métodos...
    string getNome() const;
    string getCategoria() const;
    string getTipo() const;
    int getPoder() const;
    float getPrecisao() const;
};

#endif // ATAQUE_H
