#include "game.h"      // Inclui o cabeçalho do jogo

using namespace std;

unordered_map<string, Tipo> tipoMap = {
    {"Normal", NORMAL}, {"Fogo", FOGO}, {"Agua", AGUA}, {"Eletrico", ELETRICO},
    {"Grama", GRAMA}, {"Gelo", GELO}, {"Lutador", LUTADOR}, {"Venenoso", VENENOSO},
    {"Terrestre", TERRESTRE}, {"Voador", VOADOR}, {"Psiquico", PSIQUICO},
    {"Inseto", INSETO}, {"Rocha", ROCHA}, {"Fantasma", FANTASMA},
    {"Dragao", DRAGAO}, {"Metal", METAL}, {"Fada", FADA}
};

float eficacia[17][17] = {
    // Normal, Fogo, Agua, Eletrico, Grama, Gelo, Lutador, Venenoso, Terrestre, Voador, Psiquico, Inseto, Rocha, Fantasma, Dragao, Metal, Fada
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0.5, 0, 1, 0.5, 1},  // Normal
    {1, 0.5, 0.5, 1, 2, 2, 1, 1, 1, 1, 1, 2, 0.5, 1, 0.5, 2, 1},  // Fogo
    {1, 2, 0.5, 1, 0.5, 1, 1, 1, 2, 1, 1, 1, 2, 1, 0.5, 1, 1},  // Agua
    {1, 1, 2, 0.5, 0.5, 1, 1, 1, 0, 2, 1, 1, 1, 1, 0.5, 1, 1},  // Eletrico
    {1, 0.5, 2, 1, 0.5, 1, 1, 0.5, 2, 0.5, 1, 0.5, 2, 1, 0.5, 1, 1},  // Grama
    {1, 0.5, 0.5, 1, 2, 0.5, 1, 1, 2, 2, 1, 1, 1, 1, 2, 1, 1},  // Gelo
    {2, 1, 1, 1, 1, 2, 1, 0.5, 1, 0.5, 0.5, 0.5, 2, 0, 1, 2, 0.5},  // Lutador
    {1, 1, 1, 1, 2, 1, 1, 0.5, 0.5, 1, 1, 1, 0.5, 0.5, 1, 0, 2},  // Venenoso
    {1, 2, 1, 2, 0.5, 1, 1, 2, 1, 0, 1, 0.5, 2, 1, 1, 2, 1},  // Terrestre
    {1, 1, 1, 0.5, 2, 1, 2, 1, 1, 1, 1, 2, 0.5, 1, 1, 0.5, 1},  // Voador
    {1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 0.5, 1, 1, 1, 1, 0.5, 1},  // Psiquico
    {1, 0.5, 1, 1, 2, 1, 0.5, 0.5, 1, 0.5, 2, 1, 1, 0.5, 1, 0.5, 0.5},  // Inseto
    {1, 2, 1, 1, 1, 2, 1, 1, 0.5, 2, 1, 2, 1, 1, 1, 0.5, 1},  // Rocha
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1},  // Fantasma
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0.5, 0},  // Dragao
    {1, 0.5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 0.5, 0.5},  // Metal
    {1, 0.5, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1}  // Fada
};


/***************************** FUNÇÕES DE EXIBIÇÃO *****************************/

// Exibe o menu principal do jogo
void exibirMenu() {
    cout << "----- Menu -----" << endl;
    cout << "1. Iniciar Batalha" << endl;
    cout << "2. Ajustar Dificuldade" << endl;
    cout << "3. Visualizar Ranking" << endl;
    cout << "4. Sair" << endl;  // Nova opção para reiniciar o ranking
    cout << "Escolha uma opção: ";
}

// Exibe o ranking do jogador, com o número de vitórias e derrotas
void exibirRanking(int vitorias, int derrotas) {
    cout << "\n----- Ranking -----" << endl;
    cout << "Vitórias: " << vitorias << endl;
    cout << "Derrotas: " << derrotas << endl;
    cout << "-------------------" << endl;
}

// Exibe o histórico de batalha, mostrando todas as ações anteriores
void exibirHistoricoDeBatalha(const vector<string>& log) {
    cout << "\n----- Histórico de Batalha -----\n";
    // Percorre o vetor de log e exibe cada entrada
    for (const auto& entrada : log) {
        cout << entrada << endl << endl;  // Mostra cada ação
    }
    cout << "-------------------------------\n";
}

// Exibe os ataques disponíveis para o Pokémon em batalha
void exibirAtaques(const Pokemon& pokemon) {
    cout << "\nAtaques disponíveis:\n";
    // Itera pelos quatro ataques disponíveis do Pokémon e os exibe
    for (int i = 0; i < 4; ++i) {
        Ataque ataque = pokemon.getAtaque(i);  // Pega o ataque pelo índice
        cout << i + 1 << ". " << ataque.getNome() << " - Tipo: " << ataque.getTipo() 
             << " (Categoria: " << ataque.getCategoria() << ")\n";
    }
}

/********************************************************************************/

/***************************** FUNÇÕES PARA TROCAR POKEMONS CPU E JOGADOR *****************************/

// Permite que o jogador troque de Pokémon durante a batalha
// Retorna a referência ao Pokémon escolhido
Pokemon& trocarPokemonJogador(vector<Pokemon>& jogadorPokemons, int& pokemonAtual) {
    while (true) {
        cout << "\nEscolha um Pokémon para continuar a batalha:" << endl;

        // Exibe os Pokémons que ainda estão disponíveis (não derrotados e não o atual)
        for (size_t i = 0; i < jogadorPokemons.size(); ++i) {
            if (!jogadorPokemons[i].estaDerrotado()) {
                // Exibe apenas Pokémons não derrotados e que não são o Pokémon atual
                cout << i + 1 << ". " << jogadorPokemons[i].getNome()
                     << " (HP: " << jogadorPokemons[i].getHP() << ")" << endl;
            }
        }

        // Exibe o status atualizado do Pokémon atual
        cout << "Pokémon atual: " << jogadorPokemons[pokemonAtual].getNome() 
             << " (HP: " << jogadorPokemons[pokemonAtual].getHP() << ")" << endl;

        int escolha;
        cin >> escolha;
        escolha -= 1;

        // Verifica se a escolha é válida
        if (escolha >= 0 && static_cast<size_t>(escolha) < jogadorPokemons.size() 
            && !jogadorPokemons[escolha].estaDerrotado()) {
            
            // Exibe uma mensagem de troca e atualiza pokemonAtual
            cout << "Trocando Pokémon " << jogadorPokemons[pokemonAtual].getNome() 
                 << " por " << jogadorPokemons[escolha].getNome() << endl;

            pokemonAtual = escolha;  // Atualiza o índice do Pokémon atual
            return jogadorPokemons[escolha];
        } else {
            cout << "Este Pokémon já foi derrotado, é o atual, ou a escolha é inválida! Escolha outro." << endl;
        }
    }
}



// Função que permite à CPU trocar de Pokémon
// A CPU sempre escolhe o primeiro Pokémon não derrotado
Pokemon& trocarPokemonCPU(vector<Pokemon>& cpuPokemons) {
    // Percorre a lista de Pokémons da CPU e retorna o primeiro não derrotado
    for (size_t i = 0; i < cpuPokemons.size(); ++i) {
        if (!cpuPokemons[i].estaDerrotado()) {
            return cpuPokemons[i];  // Retorna o primeiro Pokémon não derrotado
        }
    }
    // Se todos os Pokémons foram derrotados, lança um erro
    throw runtime_error("Todos os Pokémons da CPU foram derrotados!");
}

/**********************************************************************************************************/


/***************************** FUNÇÕES PARA ATUALIZAR VITORIAS E DERROTAS *****************************/

// Verifica se todos os Pokémons de um jogador estão derrotados
bool todosDerrotados(const vector<Pokemon>& pokemons) {
    // Percorre todos os Pokémons e verifica se algum ainda não foi derrotado
    for (const auto& p : pokemons) {
        if (!p.estaDerrotado()) {
            return false;  // Retorna falso se ainda houver algum Pokémon disponível
        }
    }
    return true;  // Retorna verdadeiro se todos estiverem derrotados
}

// Remove os Pokémons derrotados da lista
void removerPokemonsDerrotados(vector<Pokemon>& pokemons) {
    // Usa a função remove_if para remover os Pokémons derrotados
    pokemons.erase(remove_if(pokemons.begin(), pokemons.end(),
        [](const Pokemon& p) { return p.estaDerrotado(); }), pokemons.end());
}

// Atualiza as vitórias do jogador com base na dificuldade e salva a atualização no vetor de jogadores
void atualizarVitoriaJogador(Jogador& jogadorAtual, int dificuldade, vector<Jogador>& jogadores) {
    // Incrementa as vitórias com base na dificuldade
    if (dificuldade == 1) {
        jogadorAtual.adicionarVitoria(1);  // Fácil
    } else if (dificuldade == 2) {
        jogadorAtual.adicionarVitoria(2);  // Médio
    } else if (dificuldade == 3) {
        jogadorAtual.adicionarVitoria(3);  // Difícil
    }

    // Atualiza o jogador no vetor de jogadores
    for (auto& jogador : jogadores) {
        if (jogador.getNome() == jogadorAtual.getNome()) {
            jogador = jogadorAtual;  // Atualiza o jogador no vetor
            break;
        }
    }
}

// Atualiza as derrotas do jogador e salva a atualização no vetor de jogadores
void atualizarDerrotaJogador(Jogador& jogadorAtual, vector<Jogador>& jogadores) {
    jogadorAtual.adicionarDerrota();  // Adiciona uma derrota

    // Atualiza o jogador no vetor de jogadores
    for (auto& jogador : jogadores) {
        if (jogador.getNome() == jogadorAtual.getNome()) {
            jogador = jogadorAtual;  // Atualiza o jogador no vetor
            break;
        }
    }
}

/**********************************************************************************************************/

/***************************** FUNÇÕES PARA CARREGAR POKEMONS E ATAQUES DE UM ARQUIVO *****************************/

// Função para carregar os Pokémons a partir de um arquivo
vector<Pokemon> carregarPokemons(const string& nomeArquivo) {
    vector<Pokemon> pokemons;  // Vetor para armazenar os Pokémons
    ifstream arquivo(nomeArquivo);  // Abre o arquivo de Pokémons
    string linha;

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo de Pokémons." << endl;
        return pokemons;  // Retorna um vetor vazio em caso de erro
    }

    // Ignora a primeira linha (cabeçalho do arquivo)
    getline(arquivo, linha);

    // Lê linha por linha e processa os dados dos Pokémons
    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string nome, tipo1, tipo2;
        int hp = 0, nivel = 0, ataque = 0, defesa = 0, velocidade = 0, ataqueEspecial = 0, defesaEspecial = 0;

        // Extrai os dados separados por vírgula
        getline(ss, nome, ',');
        getline(ss, tipo1, ',');
        getline(ss, tipo2, ',');  // Pode conter "Nenhum" ou estar vazio

        // Lê os atributos numéricos, verificando se a leitura foi bem-sucedida
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

        // Cria um Pokémon e adiciona ao vetor
        Pokemon pokemon(nome, tipo1, tipo2, hp, nivel, ataque, defesa, velocidade, ataqueEspecial, defesaEspecial);
        pokemons.push_back(pokemon);
    }

    arquivo.close();  // Fecha o arquivo
    return pokemons;  // Retorna o vetor de Pokémons
}

// Função para carregar ataques a partir de um arquivo
vector<Ataque> carregarAtaques(const string& nomeArquivo) {
    vector<Ataque> ataques;  // Vetor para armazenar os ataques
    ifstream arquivo(nomeArquivo);  // Abre o arquivo de ataques
    string linha;

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo de Ataques." << endl;
        return ataques;  // Retorna um vetor vazio em caso de erro
    }

    // Ignora a primeira linha (cabeçalho do arquivo)
    getline(arquivo, linha);

    // Lê linha por linha e processa os dados dos ataques
    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string nome, categoria, tipo;
        int poder = 0;
        float precisao = 0.0;

        // Extrai os dados separados por vírgula
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

        // Cria um ataque e adiciona ao vetor
        Ataque ataque(nome, categoria, poder, precisao, tipo);
        ataques.push_back(ataque);
    }

    arquivo.close();  // Fecha o arquivo
    return ataques;  // Retorna o vetor de ataques
}

/**********************************************************************************************************/

/*********************** FUNÇÕES PARA CAULCAR DANO, ATAQUE E ATRIBUIR ATAQUES  ************************/

// Função para gerar um valor crítico (1 ou 2)
int calcularCritico() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 16);  // 1/16 de chance de ser um golpe crítico
    return (dist(gen) == 1) ? 2 : 1;  // Se o número gerado for 1, o ataque é considerado crítico e retorna o valor 2.

}

// Gera um valor aleatório entre 217 e 255, que é um fator de dano
int calcularAleatorio() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(217, 255);  // Gera um valor aleatório entre 217 e 255
    return dist(gen);  // Retorna o valor aleatório
}

// Calcula a eficácia do ataque contra o Pokémon defensor
// Função que calcula a eficácia de um ataque baseado no tipo do ataque e do defensor
// Retorna valores: 2.0 (super eficaz), 0.5 (pouco eficaz), 1.0 (normalmente eficaz), 0.0 (sem efeito)
// Função para calcular a eficácia do ataque
float calcularEficacia(const string& tipoAtaque, const string& tipoDefesa) {
    Tipo ataque = tipoMap[tipoAtaque];  // Converte o tipo de ataque para o enum
    Tipo defesa = tipoMap[tipoDefesa];  // Converte o tipo de defesa para o enum
    return eficacia[ataque][defesa];    // Retorna o valor da matriz de eficácia
}

// Calcula o bônus de STAB (Same Type Attack Bonus)
float calcularSTAB(const Ataque& ataque, const Pokemon& atacante) {
    // Se o tipo do ataque for igual ao tipo do Pokémon, aplica o bônus
    if (ataque.getTipo() == atacante.getTipo1() || ataque.getTipo() == atacante.getTipo2()) {
        return 1.5;  // Bônus de STAB aplicado
    }else{
        return 1.0;  // Sem bônus de STAB
    }
}

bool calcularPrecisao(float precisao) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(0.0, 1.0);
    
    return dist(gen) <= precisao;
}


int calcularDano(const Pokemon& atacante, const Pokemon& defensor, const Ataque& ataque) {
    float nivel = atacante.getNivel();  // Nível do atacante
    float poder = ataque.getPoder();  // Poder do ataque
    float ataqueStat = (ataque.getCategoria() == "Fisico") ? atacante.getAtaque() : atacante.getAtaqueEspecial();  // Atributo de ataque
    float defesaStat = (ataque.getCategoria() == "Fisico") ? defensor.getDefesa() : defensor.getDefesaEspecial();  // Atributo de defesa

    float critico = calcularCritico();  // Calcula se o ataque é crítico
    float STAB = calcularSTAB(ataque, atacante);  // Calcula o bônus de STAB
    float eficacia = calcularEficacia(ataque.getTipo(), defensor.getTipo1());  // Calcula a eficácia do ataque]
    if (!defensor.getTipo2().empty()) {
        eficacia *= calcularEficacia(ataque.getTipo(), defensor.getTipo2());  // Multiplica pela eficácia contra o segundo tipo
    }
    int aleatorio = calcularAleatorio();  // Gera o fator aleatório de dano

    // Cálculo base do dano
    float danoBase = (((2 * nivel * poder * ataqueStat / defesaStat) / 50) + 2);
    float danoFinal = (((danoBase * critico * STAB * eficacia * aleatorio) / 255));

    return danoFinal;  // Retorna o dano final calculado
}

// Verifica se o ataque pode ser atribuído ao Pokémon
bool podeAtribuirAtaque(const Pokemon& pokemon, const Ataque& ataque) {
    // Ataques do tipo "Normal" podem ser atribuídos a qualquer Pokémon
    if (ataque.getTipo() == "Normal") {
        return true;
    }
    // Verifica se o tipo do ataque corresponde ao tipo do Pokémon
    return (ataque.getTipo() == pokemon.getTipo1() || ataque.getTipo() == pokemon.getTipo2());
}

// Função para atribuir ataques aleatórios aos Pokémons
void atribuirAtaquesAosPokemons(vector<Pokemon>& pokemons, const vector<Ataque>& ataques) {
    random_device rd;  // Gera uma semente aleatória
    mt19937 gen(rd());  // Inicializa o gerador Mersenne Twister
    uniform_int_distribution<> dist(0, ataques.size() - 1);  // Cria uma distribuição uniforme para sortear ataques

    for (auto& pokemon : pokemons) {
        vector<Ataque> ataquesAtribuidos;  // Vetor temporário para armazenar os ataques atribuídos

        while (ataquesAtribuidos.size() < 4) {  // Cada Pokémon deve ter exatamente 4 ataques
            int indice = dist(gen);  // Sorteia um índice aleatório de ataque
            const Ataque& ataque = ataques[indice];  // Seleciona o ataque sorteado

            // Verifica se o ataque é compatível com o Pokémon e ainda não foi atribuído
            if (podeAtribuirAtaque(pokemon, ataque)) {
                bool ataqueJaAtribuido = false;

                // Verifica se o ataque já foi atribuído ao Pokémon
                for (const auto& a : ataquesAtribuidos) {
                    if (a.getNome() == ataque.getNome()) {
                        ataqueJaAtribuido = true;
                        break;
                    }
                }

                // Se o ataque ainda não foi atribuído, adiciona ao Pokémon
                if (!ataqueJaAtribuido) {
                    pokemon.adicionarAtaque(ataque);  // Atribui o ataque ao Pokémon
                    ataquesAtribuidos.push_back(ataque);  // Armazena o ataque no vetor
                }
            }
        }
    }
}

// Função para a CPU escolher um ataque aleatório
int escolherAtaqueAleatorioCPU(const Pokemon& pokemon) {
    random_device rd;  // Dispositivo de geração de números aleatórios
    mt19937 gen(rd());  // Gerador Mersenne Twister
    uniform_int_distribution<> dist(0, 3);  // Distribuição uniforme entre 0 e 3 (índices de ataque)
    return dist(gen);  // Retorna um ataque aleatório
}

// Função para a CPU escolher o ataque mais eficaz (usado em dificuldades maiores)
int escolherAtaqueCPU(const Pokemon& cpuPokemon, const Pokemon& jogadorPokemon, int dificuldade) {
    if (dificuldade == 1) {
        // Escolhe o ataque que causa o menor dano no modo fácil
        int piorAtaque = 0;
        float piorDano = calcularDano(cpuPokemon, jogadorPokemon, cpuPokemon.getAtaque(0));  // Inicializa com o primeiro ataque

        for (int i = 0; i < 4; ++i) {
            Ataque ataque = cpuPokemon.getAtaque(i);
            float danoEstimado = calcularDano(cpuPokemon, jogadorPokemon, ataque);
            
            // Verifica se o dano atual é menor que o piorDano
            if (danoEstimado < piorDano) {
                piorDano = danoEstimado;
                piorAtaque = i;
            }
        }
        return piorAtaque;
    }  else if (dificuldade == 2) {
        // Escolhe um ataque aleatório no modo médio
        int ataqueAleatorio = escolherAtaqueAleatorioCPU(cpuPokemon);
        return ataqueAleatorio;
    } else {
        // Escolhe o ataque que causa o maior dano no modo difícil
        int melhorAtaque = 0;
        float melhorDano = 0;
        for (int i = 0; i < 4; ++i) {
            Ataque ataque = cpuPokemon.getAtaque(i);
            float danoEstimado = calcularDano(cpuPokemon, jogadorPokemon, ataque);

            
            if (danoEstimado > melhorDano) {
                melhorDano = danoEstimado;
                melhorAtaque = i;
            }
        }
        return melhorAtaque;
    }
}

/**********************************************************************************************************/

/*********************** FUNÇÕES PARA SORTEAR POKEMONS, E AJUSTE DE DIFICULDADE ************************/

// Sorteia três Pokémons para o jogador e três para a CPU
void sortearPokemons(const vector<Pokemon>& todosPokemons, vector<Pokemon>& jogadorPokemons, vector<Pokemon>& cpuPokemons, int dificuldade) {
    random_device rd;
    mt19937 gen(rd());  // Gera um número aleatório
    uniform_int_distribution<> dist(0, todosPokemons.size() - 1);  // Distribuição de índices aleatórios para os Pokémons

    vector<int> indicesUsados;  // Armazena os índices já sorteados para evitar repetições

    // Sorteia três Pokémons para o jogador
    while (jogadorPokemons.size() < 3) {
        int indice = dist(gen);
        if (find(indicesUsados.begin(), indicesUsados.end(), indice) == indicesUsados.end()) {
            jogadorPokemons.push_back(todosPokemons[indice]);  // Adiciona o Pokémon sorteado ao jogador
            indicesUsados.push_back(indice);  // Marca o índice como usado
        }
    }

    // Calcula o nível mínimo e máximo dos Pokémons do jogador
    int nivelMinimoJogador = jogadorPokemons[0].getNivel();
    int nivelMaximoJogador = jogadorPokemons[0].getNivel();

    for (const auto& pokemon : jogadorPokemons) {
        if (pokemon.getNivel() < nivelMinimoJogador) {
            nivelMinimoJogador = pokemon.getNivel();  // Encontra o Pokémon mais fraco
        }
        if (pokemon.getNivel() > nivelMaximoJogador) {
            nivelMaximoJogador = pokemon.getNivel();  // Encontra o Pokémon mais forte
        }
    }

    vector<Pokemon> pokemonsElegiveis;  // Vetor para armazenar Pokémons elegíveis para a CPU

    // Filtra os Pokémons disponíveis para a CPU com base na dificuldade
    for (size_t i = 0; i < todosPokemons.size(); ++i) {
        if (find(indicesUsados.begin(), indicesUsados.end(), i) == indicesUsados.end()) {
            if (dificuldade == 1) {
                // Para dificuldade "Fácil", a CPU escolhe Pokémons com nível igual ou menor ao do mais fraco do jogador
                if (todosPokemons[i].getNivel() <= nivelMinimoJogador) {
                    pokemonsElegiveis.push_back(todosPokemons[i]);
                }
            } else if (dificuldade == 2) {
                // Para dificuldade "Médio", a CPU escolhe Pokémons com nível igual ou menor ao do mais forte do jogador
                if (todosPokemons[i].getNivel() <= nivelMaximoJogador) {
                    pokemonsElegiveis.push_back(todosPokemons[i]);
                }
            } else if (dificuldade == 3) {
                // Para dificuldade "Difícil", a CPU escolhe Pokémons com nível igual ou maior ao do mais forte do jogador
                if (todosPokemons[i].getNivel() >= nivelMaximoJogador) {
                    pokemonsElegiveis.push_back(todosPokemons[i]);
                }
            }
        }
    }

    // Sorteia três Pokémons para a CPU a partir dos elegíveis
    while (cpuPokemons.size() < 3) {
        if (pokemonsElegiveis.empty()) {
            cerr << "Erro: Não há Pokémons elegíveis suficientes para a CPU!" << endl;
            return;
        }

        uniform_int_distribution<> distElegivel(0, pokemonsElegiveis.size() - 1);
        int indice = distElegivel(gen);  // Sorteia um Pokémon para a CPU
        cpuPokemons.push_back(pokemonsElegiveis[indice]);  // Adiciona o Pokémon ao time da CPU
        pokemonsElegiveis.erase(pokemonsElegiveis.begin() + indice);  // Remove o Pokémon sorteado da lista
    }
}

// Função para ajustar a dificuldade do jogo
// Retorna a nova dificuldade escolhida pelo jogador
int ajustarDificuldade() {
    int novaDificuldade;  // Variável que armazenará a escolha de dificuldade
    cout << "\nEscolha a dificuldade:" << endl;
    cout << "1. Fácil" << endl;
    cout << "2. Médio" << endl;
    cout << "3. Difícil" << endl;
    cout << "Escolha: ";
    cin >> novaDificuldade;  // Lê a escolha do jogador

    // Verifica se a escolha está dentro das opções válidas
    if (novaDificuldade >= 1 && novaDificuldade <= 3) {
        return novaDificuldade;  // Retorna a dificuldade escolhida
    } else {
        // Caso a escolha seja inválida, retorna a dificuldade padrão "Fácil"
        cout << "Opção inválida! Dificuldade padrão será mantida." << endl;
        return 1;  // Dificuldade padrão (fácil)
    }
}

/**********************************************************************************************************/
