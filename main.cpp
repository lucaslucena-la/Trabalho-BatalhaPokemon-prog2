#include <iostream>
#include <vector>
#include <string>
#include "pokemon.h"
#include "ataque.h"
#include "game.h"
#include "jogador.h"

using namespace std;

int main() {
    int opcao;  // Variável para armazenar a opção escolhida pelo jogador no menu

    // Carregamento do arquivo de jogadores
    vector<Jogador> jogadores = carregarJogadores("jogadores.txt");  
    // Chama a função carregarJogadores que lê o arquivo 'jogadores.txt' e inicializa o vetor de jogadores

    Jogador jogadorAtual = selecionarJogador(jogadores);  
    // Chama a função para selecionar um jogador existente ou cadastrar um novo, retornando o jogador selecionado

    salvarJogadores(jogadores, "jogadores.txt");  
    // Salva os jogadores no arquivo 'jogadores.txt' após qualquer possível modificação (como o cadastro de um novo jogador)

    vector<string> logDeBatalha;  
    // Vetor que será usado para armazenar o histórico da batalha (como uma lista de ações e eventos)

    int dificuldade = 1;  // Dificuldade padrão do jogo é "Fácil" (1)
    cout << "A dificuldade atual é: " << dificuldade << endl;  
    // Exibe a dificuldade atual (padrão inicial é "Fácil")

    // Loop do menu - Continua executando até o jogador escolher sair
    while (true) {
        exibirMenu();  // Exibe o menu com as opções (Iniciar Batalha, Ajustar Dificuldade, Visualizar Ranking, Sair)
        cin >> opcao;  // Recebe a opção escolhida pelo jogador

        // 1. Iniciar Batalha
        if (opcao == 1) {
            // Carregar Pokémons do arquivo
            vector<Pokemon> pokemons = carregarPokemons("pokemons.txt");  
            // Lê os dados dos Pokémons do arquivo 'pokemons.txt' e os armazena no vetor 'pokemons'
            
            vector<Ataque> ataques = carregarAtaques("ataques.txt");  
            // Lê os dados dos ataques do arquivo 'ataques.txt' e os armazena no vetor 'ataques'

            // Sortear Pokémons para o jogador e a CPU
            vector<Pokemon> jogadorPokemons, cpuPokemons;  
            // Vetores para armazenar os Pokémons sorteados para o jogador e a CPU
            
            sortearPokemons(pokemons, jogadorPokemons, cpuPokemons, dificuldade);  
            // Função que sorteia 3 Pokémons para o jogador e 3 para a CPU, com base na dificuldade escolhida

            // Exibir Pokémons sorteados para o jogador e a CPU
            cout << "\nSeus Pokémons sorteados:\n";  
            // Exibe os Pokémons sorteados para o jogador
            for (size_t i = 0; i < jogadorPokemons.size(); ++i) {
                cout << i + 1 << ". " << jogadorPokemons[i].getNome()
                    << " (HP: " << jogadorPokemons[i].getHP()
                    << ", Nível: " << jogadorPokemons[i].getNivel()
                    << ", Tipo 1: " << jogadorPokemons[i].getTipo1()
                    << ", Tipo 2: " << (jogadorPokemons[i].getTipo2().empty() ? "Nenhum" : jogadorPokemons[i].getTipo2())
                    << ")\n";
            }

            cout << "\nPokémons sorteados da CPU:\n";  
            // Exibe os Pokémons sorteados para a CPU
            for (const auto& p : cpuPokemons) {
                cout << "- " << p.getNome()
                    << " (HP: " << p.getHP()
                    << ", Nível: " << p.getNivel()
                    << ", Tipo 1: " << p.getTipo1()
                    << ", Tipo 2: " << (p.getTipo2().empty() ? "Nenhum" : p.getTipo2())
                    << ")\n";
            }

            // Jogador escolhe qual Pokémon usar primeiro
            int escolhaInicial;  
            // Variável para armazenar a escolha inicial do jogador
            
            cout << "\nEscolha seu Pokémon inicial (1, 2 ou 3): ";  
            cin >> escolhaInicial;  // Lê a escolha do jogador
            
            escolhaInicial -= 1;  // Ajusta o índice para começar de 0
            Pokemon& jogadorPokemon = jogadorPokemons[escolhaInicial];  
            // Seleciona o Pokémon correspondente à escolha do jogador
            
            Pokemon& cpuPokemon = cpuPokemons[0];  // A CPU sempre começa com o primeiro Pokémon sorteado

            // Atribuir ataques aos Pokémons
            atribuirAtaquesAosPokemons(jogadorPokemons, ataques);  
            // Atribui ataques aleatórios compatíveis para cada Pokémon do jogador
            
            atribuirAtaquesAosPokemons(cpuPokemons, ataques);  
            // Atribui ataques aleatórios compatíveis para cada Pokémon da CPU

            // Loop da batalha
            while (true) {
                // Verificar se todos os Pokémons do jogador ou da CPU foram derrotados
                removerPokemonsDerrotados(jogadorPokemons);  
                // Remove Pokémons derrotados do vetor do jogador
                
                removerPokemonsDerrotados(cpuPokemons);  
                // Remove Pokémons derrotados do vetor da CPU

                // Atualizar a vitória ou derrota do jogador e salvar no arquivo
                if (jogadorPokemons.empty()) {
                    // Se todos os Pokémons do jogador forem derrotados
                    cout << "\nTodos os seus Pokémons foram derrotados! Você perdeu!" << endl;
                    atualizarDerrotaJogador(jogadorAtual, jogadores);  
                    // Chama a função que atualiza a derrota do jogador no arquivo
                    
                    salvarJogadores(jogadores, "jogadores.txt");  
                    // Salva os jogadores atualizados no arquivo
                    
                    break;  // Sai do loop da batalha
                }

                if (cpuPokemons.empty()) {
                    // Se todos os Pokémons da CPU forem derrotados
                    cout << "\nTodos os Pokémons da CPU foram derrotados! Você venceu!" << endl;
                    atualizarVitoriaJogador(jogadorAtual, dificuldade, jogadores);  
                    // Chama a função que atualiza a vitória e a pontuação do jogador
                    
                    salvarJogadores(jogadores, "jogadores.txt");  
                    // Salva os jogadores atualizados no arquivo
                    
                    break;  // Sai do loop da batalha
                }

                // Exibir informações dos Pokémons em batalha
                cout << "\n----- Status dos Pokémons -----\n";
                cout << "Jogador: " << jogadorPokemon.getNome() << " - HP: " << jogadorPokemon.getHP() << endl;
                cout << "CPU: " << cpuPokemon.getNome() << " - HP: " << cpuPokemon.getHP() << endl;
                cout << "-------------------------------\n";

                // Ações do jogador
                cout << "\nEscolha uma ação:\n";
                cout << "1. Atacar\n2. Trocar Pokémon\n3. Exibir Histórico de Batalha\n";
                int acaoJogador;  // Variável para armazenar a ação escolhida pelo jogador
                cin >> acaoJogador;

                if (acaoJogador == 1) {
                    // Exibir ataques e permitir escolha
                    exibirAtaques(jogadorPokemon);  
                    // Exibe a lista de ataques do Pokémon

                    int escolhaAtaque;  // Variável para armazenar o ataque escolhido
                    cin >> escolhaAtaque;
                    escolhaAtaque -= 1;  // Ajuste do índice para o ataque

                    // Jogador ataca
                    Ataque ataqueJogador = jogadorPokemon.getAtaque(escolhaAtaque);  
                    // Seleciona o ataque escolhido pelo jogador
                    
                    int danoJogador = calcularDano(jogadorPokemon, cpuPokemon, ataqueJogador);  
                    // Calcula o dano causado pelo ataque
                    
                    cpuPokemon.receberDano(danoJogador);  
                    // CPU recebe o dano calculado

                    // Exibir o dano causado e o HP do oponente
                    cout << jogadorPokemon.getNome() << " usou " << ataqueJogador.getNome() << " e causou " << danoJogador << " de dano!" << endl;
                    cout << cpuPokemon.getNome() << " agora tem " << cpuPokemon.getHP() << " de HP!" << endl;

                    // Verificar se o Pokémon da CPU foi derrotado
                    if (cpuPokemon.estaDerrotado()) {
                        // Se o Pokémon da CPU foi derrotado
                        cout << cpuPokemon.getNome() << " foi derrotado!" << endl;
                        try {
                            removerPokemonsDerrotados(cpuPokemons);  
                            // Remove o Pokémon derrotado da CPU

                            // CPU troca para o próximo Pokémon não derrotado
                            cpuPokemon = trocarPokemonCPU(cpuPokemons);  
                            cout << "CPU escolheu " << cpuPokemon.getNome() << " para continuar a batalha!" << endl;
                        } catch (const runtime_error& e) {
                            // Se todos os Pokémons da CPU forem derrotados
                            cout << "Todos os Pokémons da CPU foram derrotados! Você venceu!" << endl;
                            atualizarVitoriaJogador(jogadorAtual, dificuldade, jogadores);  
                            salvarJogadores(jogadores, "jogadores.txt");  
                            break;  // Termina a batalha
                        }
                    }
                } else if (acaoJogador == 2) {
                    // Jogador troca Pokémon
                    jogadorPokemon = trocarPokemonJogador(jogadorPokemons);  
                    // Permite que o jogador escolha outro Pokémon
                } else if (acaoJogador == 3) {
                    // Exibir histórico da batalha
                    exibirHistoricoDeBatalha(logDeBatalha);  
                    // Exibe as ações anteriores na batalha
                }

                // A CPU ataca se o jogador não trocar Pokémon
                if (!cpuPokemon.estaDerrotado()) {
                    int escolhaCPU = escolherAtaqueCPU(cpuPokemon, jogadorPokemon, dificuldade);
                    // CPU escolhe um ataque aleatório ou o melhor ataque com base na dificuldade
                    
                    Ataque ataqueCPU = cpuPokemon.getAtaque(escolhaCPU);  
                    // Seleciona o ataque da CPU
                    
                    int danoCPU = calcularDano(cpuPokemon, jogadorPokemon, ataqueCPU);  
                    // Calcula o dano do ataque da CPU
                    
                    jogadorPokemon.receberDano(danoCPU);  
                    // Jogador recebe o dano

                    // Exibir o dano causado pela CPU e o HP do jogador
                    cout << cpuPokemon.getNome() << " usou " << ataqueCPU.getNome() << " e causou " << danoCPU << " de dano!" << endl;
                    cout << jogadorPokemon.getNome() << " agora tem " << jogadorPokemon.getHP() << " de HP!" << endl;

                    // Verificar se o jogador foi derrotado
                    if (jogadorPokemon.estaDerrotado()) {
                        // Se o Pokémon do jogador foi derrotado
                        cout << jogadorPokemon.getNome() << " foi derrotado!" << endl;

                        // Jogador troca para o próximo Pokémon não derrotado
                        if (!jogadorPokemons.empty()) {
                            jogadorPokemon = jogadorPokemons[0];  
                            // Escolhe o próximo Pokémon disponível
                        }
                    }
                }
            }

        } else if (opcao == 2) {
            // Ajustar a dificuldade
            dificuldade = ajustarDificuldade();  
            // Permite ao jogador ajustar a dificuldade (fácil, médio ou difícil)
            cout << "Dificuldade ajustada para: " << dificuldade << endl;

        } else if (opcao == 3) {
            // Exibe o ranking de todos os jogadores cadastrados
            for (const auto& jogador : jogadores) {
                // Exibe as estatísticas (vitórias, derrotas e pontuação) de cada jogador
                cout << "\n----- Ranking do Jogador: " << jogador.getNome() << " -----" << endl;
                cout << "Vitórias (Fácil): " << jogador.getVitoriasFacil() << endl;
                cout << "Vitórias (Médio): " << jogador.getVitoriasMedio() << endl;
                cout << "Vitórias (Difícil): " << jogador.getVitoriasDificil() << endl;
                cout << "Derrotas: " << jogador.getDerrotas() << endl;
                cout << "Pontuação: " << jogador.getPontuacao() << endl;
                cout << "-----------------------------------------------" << endl;
            }

        } else if (opcao == 4) {
            // Sair do jogo
            cout << "Saindo do jogo..." << endl;
            break;  // Encerra o loop e sai do jogo

        } else {
            // Opção inválida
            cout << "Opção inválida! Tente novamente." << endl;
        }
    }

    return 0;  // Retorna 0 para indicar que o programa terminou corretamente
}
