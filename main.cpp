#include <iostream>
#include <vector>
#include <string>
#include "pokemon.h"
#include "ataque.h"
#include "game.h"

using namespace std;

int main() {
    int opcao;
    vector<string> logDeBatalha;  // Adicionar o vetor para armazenar o histórico
    
    Ranking ranking = carregarRanking("ranking.txt");  // Carrega o ranking do arquivo no início do jogo
    int dificuldade = 1;  // Dificuldade padrão: Fácil
    cout << "A dificuldade atual é: " << dificuldade << endl;

    // Loop do menu
    while (true) {
        exibirMenu();
        cin >> opcao;

        //1 = iniciar batalha
        if (opcao == 1) {
            // Carregar Pokémons do arquivo
            vector<Pokemon> pokemons = carregarPokemons("pokemons.txt");
            vector<Ataque> ataques = carregarAtaques("ataques.txt");

            // Sortear Pokémons para o jogador e a CPU
            vector<Pokemon> jogadorPokemons, cpuPokemons;
            sortearPokemons(pokemons, jogadorPokemons, cpuPokemons, dificuldade);

            // Exibir Pokémons sorteados para o jogador e a CPU
            cout << "\nSeus Pokémons sorteados:\n";
            for (size_t i = 0; i < jogadorPokemons.size(); ++i) {
                cout << i + 1 << ". " << jogadorPokemons[i].getNome()
                    << " (HP: " << jogadorPokemons[i].getHP()
                    << ", Nível: " << jogadorPokemons[i].getNivel()
                    << ", Tipo 1: " << jogadorPokemons[i].getTipo1()
                    << ", Tipo 2: " << (jogadorPokemons[i].getTipo2().empty() ? "Nenhum" : jogadorPokemons[i].getTipo2())
                    << ")\n";
            }

            cout << "\nPokémons sorteados da CPU:\n";
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
            cout << "\nEscolha seu Pokémon inicial (1, 2 ou 3): ";
            cin >> escolhaInicial;
            escolhaInicial -= 1;  // Ajustar para o índice
            Pokemon& jogadorPokemon = jogadorPokemons[escolhaInicial];
            Pokemon& cpuPokemon = cpuPokemons[0];  // CPU começa com o primeiro Pokémon

            // Atribuir ataques aos Pokémons
            atribuirAtaquesAosPokemons(jogadorPokemons, ataques);
            atribuirAtaquesAosPokemons(cpuPokemons, ataques);

            // Loop da batalha
            while (true) {
                // Verificar se todos os Pokémons do jogador ou da CPU foram derrotados
                removerPokemonsDerrotados(jogadorPokemons);
                removerPokemonsDerrotados(cpuPokemons);

                if (jogadorPokemons.empty()) {
                    cout << "\nTodos os seus Pokémons foram derrotados! Você perdeu!" << endl;
                    atualizarDerrota(ranking);  // Atualiza derrotas no ranking
                    salvarRanking(ranking, "ranking.txt");  // Salva o ranking atualizado no arquivo
                    break;
                }

                if (cpuPokemons.empty()) {
                    cout << "\nTodos os Pokémons da CPU foram derrotados! Você venceu!" << endl;
                    atualizarRanking(ranking, dificuldade);  // Atualiza vitórias e pontuação com base na dificuldade
                    salvarRanking(ranking, "ranking.txt");  // Salva o ranking atualizado no arquivo
                    break;
                }


                // Exibir informações dos Pokémons em batalha
                cout << "\n----- Status dos Pokémons -----\n";
                cout << "Jogador: " << jogadorPokemon.getNome() << " - HP: " << jogadorPokemon.getHP() << endl;
                cout << "CPU: " << cpuPokemon.getNome() << " - HP: " << cpuPokemon.getHP() << endl;
                cout << "-------------------------------\n";

                // Ações do jogador
                cout << "\nEscolha uma ação:\n";
                cout << "1. Atacar\n2. Trocar Pokémon\n3. Exibir Histórico de Batalha\n";
                int acaoJogador;
                cin >> acaoJogador;

                if (acaoJogador == 1) {
                    // Exibir ataques e permitir escolha
                    exibirAtaques(jogadorPokemon);

                    int escolhaAtaque;
                    cin >> escolhaAtaque;
                    escolhaAtaque -= 1;  // Ajuste do índice

                    // Jogador ataca
                    Ataque ataqueJogador = jogadorPokemon.getAtaque(escolhaAtaque);
                    int danoJogador = calcularDano(jogadorPokemon, cpuPokemon, ataqueJogador);
                    cpuPokemon.receberDano(danoJogador);

                    // Exibir o dano causado e o HP do oponente
                    cout << jogadorPokemon.getNome() << " usou " << ataqueJogador.getNome() << " e causou " << danoJogador << " de dano!" << endl;
                    cout << cpuPokemon.getNome() << " agora tem " << cpuPokemon.getHP() << " de HP!" << endl;
                    
                
                    // Verificar se o Pokémon da CPU foi derrotado
                    if (cpuPokemon.estaDerrotado()) {
                        cout << cpuPokemon.getNome() << " foi derrotado!" << endl; 
                    
                        try {
                            
                            // Remover os Pokémons derrotados antes de trocar
                            removerPokemonsDerrotados(cpuPokemons);
                            // CPU troca para o próximo Pokémon não derrotado
                            cpuPokemon = trocarPokemonCPU(cpuPokemons);
                            cout << "CPU escolheu " << cpuPokemon.getNome() << " para continuar a batalha!" << endl;
                        } catch (const runtime_error& e) {
                            cout << "Todos os Pokémons da CPU foram derrotados! Você venceu!" << endl;
                            atualizarRanking(ranking, dificuldade);  // Atualiza derrotas no ranking
                            // Exibe o estado do ranking após a atualização
                            std::cout << "Depois da vitória - Vitórias (Fácil): " << ranking.vitoriasFacil 
                                        << ", Vitórias (Médio): " << ranking.vitoriasMedio 
                                        << ", Vitórias (Difícil): " << ranking.vitoriasDificil
                                        << ", Derrotas: " << ranking.derrotas 
                                        << ", Pontuação: " << ranking.pontuacao << std::endl;

                            // Salva o ranking no arquivo
                            salvarRanking(ranking, "ranking.txt");  // Salva o ranking atualizado no arquivo
                            break;  // Termina a batalha se não houver mais Pokémons
                        }
                    }
                }else if (acaoJogador == 2) {
                    // Jogador troca Pokémon
                    jogadorPokemon = trocarPokemonJogador(jogadorPokemons);
                } else if (acaoJogador == 3) {
                    // Exibir histórico da batalha
                    exibirHistoricoDeBatalha(logDeBatalha);
                }

                // A CPU ataca se o jogador não trocar Pokémon
                if (!cpuPokemon.estaDerrotado()) {
                    int escolhaCPU = escolherAtaqueCPU(cpuPokemon);
                    Ataque ataqueCPU = cpuPokemon.getAtaque(escolhaCPU);
                    int danoCPU = calcularDano(cpuPokemon, jogadorPokemon, ataqueCPU);
                    jogadorPokemon.receberDano(danoCPU);

                    // Exibir o dano causado pela CPU e o HP do jogador
                    cout << cpuPokemon.getNome() << " usou " << ataqueCPU.getNome() << " e causou " << danoCPU << " de dano!" << endl;
                    cout << jogadorPokemon.getNome() << " agora tem " << jogadorPokemon.getHP() << " de HP!" << endl;

                    // Verificar se o jogador foi derrotado
                    if (jogadorPokemon.estaDerrotado()) {
                        cout << jogadorPokemon.getNome() << " foi derrotado!" << endl;

                        // Jogador troca para o próximo Pokémon não derrotado
                        if (!jogadorPokemons.empty()) {
                            jogadorPokemon = jogadorPokemons[0];  // Próximo Pokémon
                        }
                    }
                }
            }

        } else if (opcao == 2) {
            // Ajustar a dificuldade
            dificuldade = ajustarDificuldade();
            cout << "Dificuldade ajustada para: " << dificuldade << endl;

        }else if (opcao == 3) {
            // Carregar o ranking novamente para garantir que está atualizado
            ranking = carregarRanking("ranking.txt");
            exibirRanking(ranking);  // Exibe o ranking carregado
        } else if (opcao ==4){
                reiniciarRanking(ranking);  // Chama a função para reiniciar o ranking        
        }else if(opcao == 5) {
            // Sair do jogo
            cout << "Saindo do jogo..." << endl;
            break;

        } else {
            cout << "Opção inválida! Tente novamente." << endl;
        }
    }

    return 0;
}

