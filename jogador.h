#ifndef JOGADOR_H
#define JOGADOR_H

#include <string>
#include <vector>

using namespace std;

class Jogador {
private:
    string nome;
    int vitoriasFacil;
    int vitoriasMedio;
    int vitoriasDificil;
    int derrotas;
    int pontuacao;

public:
    // Construtor
    Jogador(string nome);

    // Getters
    string getNome() const;
    int getVitoriasFacil() const;
    int getVitoriasMedio() const;
    int getVitoriasDificil() const;
    int getDerrotas() const;
    int getPontuacao() const;

    // Setters (adiciona estas funções)
    void setVitoriasFacil(int vitorias);
    void setVitoriasMedio(int vitorias);
    void setVitoriasDificil(int vitorias);
    void setDerrotas(int derrotas);
    void setPontuacao(int pontuacao);

    // Funções para adicionar vitórias e derrotas
    void adicionarVitoria(int dificuldade);
    void adicionarDerrota();

    void exibirJogador() const;

};


// Funções para carregar e salvar jogadores
vector<Jogador> carregarJogadores(const string& arquivo);
void salvarJogadores(const vector<Jogador>& jogadores, const string& arquivo);
Jogador selecionarJogador(vector<Jogador>& jogadores);
void registrarVitoria(Jogador& jogador, int dificuldade, vector<Jogador>& jogadores, const string& arquivo);
void registrarDerrota(Jogador& jogador, vector<Jogador>& jogadores, const string& arquivo);
void atualizarVitoriaJogador(Jogador& jogadorAtual, int dificuldade);

#endif
