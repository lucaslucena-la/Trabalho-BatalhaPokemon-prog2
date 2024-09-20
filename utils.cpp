#include "utils.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>  // Para sortear ataques aleatórios
#include <cmath>
#include <algorithm> // Para std::find

using namespace std;

// Função para carregar Pokémons a partir de um arquivo
vector<Pokemon> carregarPokemons(const string& nomeArquivo) {
    vector<Pokemon> pokemons;
    ifstream arquivo(nomeArquivo);
    string linha;

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo de Pokémons." << endl;
        return pokemons;
    }

    // Ignorar a primeira linha (cabeçalho)
    getline(arquivo, linha);

    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string nome, tipo1, tipo2;
        int hp = 0, nivel = 0, ataque = 0, defesa = 0, velocidade = 0, ataqueEspecial = 0, defesaEspecial = 0;

        // Ler os dados do arquivo, separando por vírgulas
        getline(ss, nome, ',');
        getline(ss, tipo1, ',');
        getline(ss, tipo2, ',');  // Pode conter "Nenhum" ou estar vazio
        
        if (!(ss >> hp)) {
            cerr << "Erro ao ler o HP de " << nome << endl;
            continue;
        }
        ss.ignore();

        if (!(ss >> nivel)) {
            cerr << "Erro ao ler o Nível de " << nome << endl;
            continue;
        }
        ss.ignore();

        if (!(ss >> ataque)) {
            cerr << "Erro ao ler o Ataque de " << nome << endl;
            continue;
        }
        ss.ignore();

        if (!(ss >> defesa)) {
            cerr << "Erro ao ler a Defesa de " << nome << endl;
            continue;
        }
        ss.ignore();

        if (!(ss >> velocidade)) {
            cerr << "Erro ao ler a Velocidade de " << nome << endl;
            continue;
        }
        ss.ignore();

        if (!(ss >> ataqueEspecial)) {
            cerr << "Erro ao ler o Ataque Especial de " << nome << endl;
            continue;
        }
        ss.ignore();

        if (!(ss >> defesaEspecial)) {
            cerr << "Erro ao ler a Defesa Especial de " << nome << endl;
            continue;
        }

        // Criar o Pokémon e adicioná-lo ao vetor
        Pokemon pokemon(nome, tipo1, tipo2, hp, nivel, ataque, defesa, velocidade, ataqueEspecial, defesaEspecial);
        pokemons.push_back(pokemon);
    }

    arquivo.close();
    return pokemons;
}

// Função para carregar Ataques a partir de um arquivo
vector<Ataque> carregarAtaques(const string& nomeArquivo) {
    vector<Ataque> ataques;
    ifstream arquivo(nomeArquivo);
    string linha;

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo de Ataques." << endl;
        return ataques;
    }

    // Ignorar a primeira linha (cabeçalho)
    getline(arquivo, linha);

    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string nome, categoria, tipo;
        int poder = 0;
        float precisao = 0.0;

        getline(ss, nome, ',');
        getline(ss, categoria, ',');

        if (!(ss >> poder)) {
            cerr << "Erro ao ler o Poder de " << nome << endl;
            continue;
        }
        ss.ignore();

        if (!(ss >> precisao)) {
            cerr << "Erro ao ler a Precisão de " << nome << endl;
            continue;
        }
        ss.ignore();

        getline(ss, tipo);

        // Criar o ataque e adicioná-lo ao vetor
        Ataque ataque(nome, categoria, poder, precisao, tipo);
        ataques.push_back(ataque);
    }

    arquivo.close();
    return ataques;
}

// Função para verificar se um ataque pode ser atribuído ao Pokémon
// Função para verificar se um ataque pode ser atribuído ao Pokémon
bool podeAtribuirAtaque(const Pokemon& pokemon, const Ataque& ataque) {
    // Ataques do tipo "Normal" podem ser atribuídos a qualquer Pokémon
    if (ataque.getTipo() == "Normal") {
        return true;
    }
    // Ataque deve corresponder ao tipo do Pokémon
    return (ataque.getTipo() == pokemon.getTipo1() || ataque.getTipo() == pokemon.getTipo2());
}


// Função para atribuir ataques aleatórios a cada Pokémon
void atribuirAtaquesAosPokemons(vector<Pokemon>& pokemons, const vector<Ataque>& ataques) {
    random_device rd;  // Para gerar números aleatórios
    mt19937 gen(rd()); // Gerador
    uniform_int_distribution<> dist(0, ataques.size() - 1); // Distribuição

    for (auto& pokemon : pokemons) {
        vector<Ataque> ataquesAtribuidos;

        while (ataquesAtribuidos.size() < 4) {  // Cada Pokémon deve ter 4 ataques
            int indice = dist(gen);
            const Ataque& ataque = ataques[indice];

            // Verifica se o ataque é compatível com o Pokémon e se ainda não foi atribuído
            if (podeAtribuirAtaque(pokemon, ataque)) {
                bool ataqueJaAtribuido = false;
                for (const auto& a : ataquesAtribuidos) {
                    if (a.getNome() == ataque.getNome()) {
                        ataqueJaAtribuido = true;
                        break;
                    }
                }
                if (!ataqueJaAtribuido) {
                    pokemon.adicionarAtaque(ataque);
                    ataquesAtribuidos.push_back(ataque);
                }
            }
        }
    }
}

// Função para gerar um valor crítico (1 ou 2)
int calcularCritico() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 16);
    return (dist(gen) == 1) ? 2 : 1;  // 1/16 de chance de ser crítico
}

// Função para gerar o fator aleatório entre 217 e 255
int calcularAleatorio() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(217, 255);
    return dist(gen);
}

// Função para calcular a eficácia do ataque
float calcularEficacia(const Ataque& ataque, const Pokemon& defensor) {
    // Por simplicidade, vamos assumir que a eficácia pode ser 2x, 0.5x ou 1x
    // Isso deve ser ajustado com base nos tipos do ataque e do Pokémon defensor
    // Exemplo simplificado (a lógica completa precisaria de uma tabela de tipos):
    if (ataque.getTipo() == "Agua" && defensor.getTipo1() == "Fogo") return 2.0;
    if (ataque.getTipo() == "Fogo" && defensor.getTipo1() == "Agua") return 0.5;
    return 1.0;  // Caso não seja super eficaz ou pouco eficaz
}

// Função para calcular o STAB (Same Type Attack Bonus)
float calcularSTAB(const Ataque& ataque, const Pokemon& atacante) {
    if (ataque.getTipo() == atacante.getTipo1() || ataque.getTipo() == atacante.getTipo2()) {
        return 1.5;  // STAB aplicado
    }
    return 1.0;  // Sem STAB
}

// Função para calcular o dano total de um ataque
int calcularDano(const Pokemon& atacante, const Pokemon& defensor, const Ataque& ataque) {
    int nivel = atacante.getNivel();
    int poder = ataque.getPoder();
    int ataqueStat = (ataque.getCategoria() == "Fisico") ? atacante.getAtaque() : atacante.getAtaqueEspecial();
    int defesaStat = (ataque.getCategoria() == "Fisico") ? defensor.getDefesa() : defensor.getDefesaEspecial();

    int critico = calcularCritico();
    float STAB = calcularSTAB(ataque, atacante);
    float eficacia = calcularEficacia(ataque, defensor);
    int aleatorio = calcularAleatorio();

    // Cálculo do dano
    int danoBase = (((2 * nivel * poder * ataqueStat / defesaStat) / 50) + 2);
    int danoFinal = (((danoBase * critico * STAB * eficacia * aleatorio) / 255));

    // Exibir se foi crítico
    if (critico == 2) {
        std::cout << "Foi um golpe crítico!" << std::endl;
    }

    // Exibir se foi super eficaz ou não
    if (eficacia > 1.0) {
        std::cout << "Foi super eficaz!" << std::endl;
    } else if (eficacia < 1.0) {
        std::cout << "Não foi muito eficaz..." << std::endl;
    }

    return danoFinal;
}

// Função para a CPU escolher um ataque aleatório
int escolherAtaqueCPU(const Pokemon& pokemon) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 3);  // Assume que o Pokémon tem 4 ataques
    return dist(gen);  // Retorna um índice aleatório de 0 a 3
}

// Função para sortear três Pokémons aleatórios para o jogador e para a CPU
void sortearPokemons(const std::vector<Pokemon>& pokemons, std::vector<Pokemon>& jogadorPokemons, std::vector<Pokemon>& cpuPokemons) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, pokemons.size() - 1);

    // Vetor para armazenar índices já usados para evitar repetição
    std::vector<int> indicesUsados;

    // Sortear três Pokémons para o jogador
    while (jogadorPokemons.size() < 3) {
        int indice = dist(gen);
        // Verificar se o índice já foi usado
        if (std::find(indicesUsados.begin(), indicesUsados.end(), indice) == indicesUsados.end()) {
            jogadorPokemons.push_back(pokemons[indice]);
            indicesUsados.push_back(indice);  // Marcar índice como usado
        }
    }

    // Sortear três Pokémons para a CPU
    while (cpuPokemons.size() < 3) {
        int indice = dist(gen);
        // Verificar se o índice já foi usado
        if (std::find(indicesUsados.begin(), indicesUsados.end(), indice) == indicesUsados.end()) {
            cpuPokemons.push_back(pokemons[indice]);
            indicesUsados.push_back(indice);  // Marcar índice como usado
        }
    }
}