#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include "Partido.h"
#include "Candidato.h"

std::string CSVparaLinha(const std::string& path) {
    auto var = std::ostringstream{};
    std::ifstream arquivo(path);
    var << arquivo.rdbuf();
    return var.str();
}

int main(int argc, char* argv[]) {

    if (argc != 4) {
        std::cout << "Erro: Argumentos insuficientes." << std::endl;
        std::exit(1);
    }

    setlocale(LC_ALL,"pt_BR.UTF-8");

    std::string conteudoLinha = CSVparaLinha(argv[1]);

    std::list<std::vector<std::string>> csvCandidatos;
    std::istringstream stringCandidatos(conteudoLinha);
    std::string linha;

    while(getline(stringCandidatos, linha)) {
        std::istringstream ls(linha);
        std::string candidato;
        std::vector<std::string> linhaCsv;

        while (getline(ls,candidato,',')) {
            linhaCsv.push_back(candidato);
        }
        csvCandidatos.push_back(linhaCsv);
    }

    std::vector<Candidato*> listaCandidatos;
    int counter = 0;
    for (auto& dado : csvCandidatos) {
        if (counter == 0) {
            counter++;
            continue;
        }
        Candidato* candidato = new Candidato(std::stoi(dado[0]),std::stoi(dado[1]),dado[2],dado[3],dado[4],dado[5],dado[6],dado[7],std::stoi(dado[8]));
        listaCandidatos.push_back(candidato);
    }

    conteudoLinha = CSVparaLinha(argv[2]);
    std::list<std::vector<std::string>> csvPartidos;
    std::istringstream stringPartidos(conteudoLinha);
    std::vector<Partido*> listaPartidos;

    while(getline(stringPartidos,linha)) {
        std::istringstream ls(linha);
        std::string partido;
        std::vector<std::string> linhaCsv;

        while (getline(ls,partido,',')) {
            linhaCsv.push_back(partido);
        }
        csvPartidos.push_back(linhaCsv);
    }

    counter = 0;
    for (auto& dado : csvPartidos) {
        if (counter == 0) {
            counter++;
            continue;
        }
        Partido* partido = new Partido(std::stoi(dado[0]),std::stoi(dado[1]),dado[2],dado[3]);
        partido->setVotosTotais(partido->getVotosLegenda());
        listaPartidos.push_back(partido);
    }

    std::sort(listaCandidatos.begin(),listaCandidatos.end(),[](Candidato* c1, Candidato* c2) {
        if (c1->getVotosNominais() != c2->getVotosNominais()) {
            return c2->getVotosNominais() < c1->getVotosNominais();
        }
        return c2->getDataNasc() < c1->getDataNasc();
    });

    std::vector<Candidato*> candidatosEleitos;
    int vagas = 0;

    //Verifica a quantidade de candidatos eleitos e os adiciona ao novo vetor
    for (Candidato* c : listaCandidatos) {
        if (c->getSituacao() == "Eleito" && c->getDestinoVoto() == "Válido") {
            vagas++;
            candidatosEleitos.push_back(c);
        }

        //Associa cada candidato ao seu partido
        for (Partido* p : listaPartidos) {
            if (c->getNumeroPartido() == p->getNumeroPartido()) {
                c->setPartido(*p);

                //Incrementa os votos do candidato atual ao número de votos do seu partido
                if (c->getDestinoVoto() == "Válido") {
                    p->adicionaCandidato(c);
                    p->incrementaVotos(c->getVotosNominais());
                }

                //Se o candidato atual for eleito, incrementa o número de candidatos eleitos do partido
                if (c->getSituacao() == "Eleito" && c->getDestinoVoto() == "Válido") {
                    p->incrementaCandidatosEleitos();
                }
            }
        }
    }



    //Imprime a quantidade de candidatos eleitos (1)
    std::cout << "Número de vagas: " << vagas << "\n" << std::endl;




    int pos = 1;
    //Imprime os vereadores eleitos, na ordem decrescente de votos (2)
    std::cout << "Vereadores eleitos:\n";
    for (Candidato* c : candidatosEleitos) {
        std::cout << pos << " - " << c->getNome() << " / " << c->getNomeUrna() << " (" << c->getPartido()->getSiglaPartido() << ", "<< c->getVotosNominais() << " votos)" << std::endl;
        pos++;
    }

    //Imprime os candidatos mais votados dentro do número de vagas (3)
    pos = 1;
    std::cout << "\nCandidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):" << std::endl;
    for (int i = 0; i < vagas; ++i) {
        std::cout << pos << " - " << listaCandidatos[i]->getNome() << " / " << listaCandidatos[i]->getNomeUrna() << " (" << listaCandidatos[i]->getPartido()->getSiglaPartido() << ", "<< listaCandidatos[i]->getVotosNominais() << " votos)" << std::endl;
        pos++;
    }



    //Imprime os candidatos que teriam sido eleitos, caso a votação fosse majoritária (4)
    std::cout << "\nTeriam sido eleitos se a votação fosse majoritária, e não foram eleitos:" << std::endl;
    std::cout << "(com sua posição no ranking de mais votados)" << std::endl;

    for (int i = 0; i < vagas; ++i) {
        if (listaCandidatos[i]->getSituacao() != "Eleito") {
            std::cout << (i+1) << " - " << listaCandidatos[i]->getNome() << " / " << listaCandidatos[i]->getNomeUrna() << " (" << listaCandidatos[i]->getPartido()->getSiglaPartido() << ", "<< listaCandidatos[i]->getVotosNominais() << " votos)" << std::endl;
        }
    }

    //Imprime os candidatos que foram beneficiados pelo sistema proporcional (5)
    std::cout << "\nEleitos, que se beneficiaram do sistema proporcional:" << std::endl;
    std::cout << "(com sua posição no ranking de mais votados)" << std::endl;

    for (int i = vagas; i < (int)listaCandidatos.size(); ++i) {
        if (listaCandidatos[i]->getSituacao() == "Eleito") {
            std::cout << (i+1) << " - " << listaCandidatos[i]->getNome() << " / " << listaCandidatos[i]->getNomeUrna() << " (" << listaCandidatos[i]->getPartido()->getSiglaPartido() << ", "<< listaCandidatos[i]->getVotosNominais() << " votos)" << std::endl;
        }
    }

    //Ordena o vetor de partidos em ordem decrescente de votos totais, priorizando o partido com menor número
    std::sort(listaPartidos.begin(),listaPartidos.end(),[](Partido* p1, Partido* p2) {
        if (p1->getVotosTotais() != p2->getVotosTotais()) {
            return p2->getVotosTotais() < p1->getVotosTotais();
        }
        return p1->getNumeroPartido() < p2->getNumeroPartido();
    });


    //Imprime os votos totalizados por partido e o número de candidatos eleitos (6)
    std::cout << "\nVotação dos partidos e número de candidatos eleitos:" << std::endl;
    pos = 1;
    for (Partido* p : listaPartidos) {
        if (p->getVotosNominais() > 1) {
            //plural e singular
            //std::cout << pos << " - " << p->getSiglaPartido() << " - " << p->getNumeroPartido() << ", " << p->getVotosTotais() << " voto (" <<
            //            p->getVotosNominais() << "nominal e " << p->getVotosLegenda() << " de legenda), " << p->getCandidatosEleitos() << "candidato eleito" << std::endl;
        } else {
            std::cout << pos << " - " << p->getSiglaPartido() << " - " << p->getNumeroPartido() << ", " << p->getVotosTotais() << " voto (" <<
            p->getVotosNominais() << "nominal e " << p->getVotosLegenda() << " de legenda), " << p->getCandidatosEleitos() << "candidato eleito" << std::endl;
        }
        pos++;
    }

    //Ordena os partidos na ordem decrescente de votos de legenda, priorizando a ordem de votos nominais e em seguina, número do partido
    std::sort(listaPartidos.begin(),listaPartidos.end(),[](Partido* p1, Partido* p2) {
        if (p1->getVotosLegenda() != p2->getVotosLegenda()) {
            return p2->getVotosLegenda() < p1->getVotosLegenda();
        }
        else if (p1->getVotosNominais() != p2->getVotosNominais()) {
            return p2->getVotosNominais() < p1->getVotosNominais();
        }

        return p1->getNumeroPartido() < p2->getNumeroPartido();
    });

    //Imprime os votos de legenda com a porcentagem em relação aos votos totais (7)
    std::cout << "\nVotação dos partidos (apenas votos de legenda):" << std::endl;
    pos = 1;

    for (Partido* p : listaPartidos) {
        if (p->getVotosTotais() != 0) {
            if (p->getVotosTotais() > 1) {
                std::printf("%d - %s - %d, %d votos de legenda (%.2f%% do total do partido)\n",pos,p->getSiglaPartido().c_str(),
                            p->getNumeroPartido(),p->getVotosLegenda(), 100.0 * p->getVotosLegenda()/p->getVotosTotais());
            } else {
                std::printf("%d - %s - %d, %d voto de legenda (%.2f%% do total do partido)\n",pos,p->getSiglaPartido().c_str(),
                            p->getNumeroPartido(),p->getVotosLegenda(), 100.0 * p->getVotosLegenda()/p->getVotosTotais());
            }
        } else {
            std::cout << pos << " - " << p->getSiglaPartido() << " - " << p->getNumeroPartido() << ", " << p->getVotosLegenda() <<
            " voto de legenda (porporção não calculada, 0 voto no partido)" << std::endl;
        }
        pos++;
    }

    //Ordena os candidatos dos partidos na ordem decrescente de votos nominais, priorizando a idade do mais velho.
    for (Partido* p : listaPartidos) {
        if (p->getListaCandidatos().empty()) {
            std::sort(p->getListaCandidatos().begin(), p->getListaCandidatos().end(),[](Candidato* c1, Candidato* c2) {
                if (c1->getVotosNominais() != c2->getVotosNominais()) {
                    return c2->getVotosNominais() < c1->getVotosNominais();
                }

                return c2->getDataNasc() < c1->getDataNasc();
                //fazer comparacao correta
            });
        }
    }

    //Ordena os partidos por ordem decrescente de votos nominais do candidato mais votado de cada partido,
    // priorizando o número do partido
    std::sort(listaPartidos.begin(),listaPartidos.end(),[](Partido* p1, Partido* p2) {
        if (p1->getListaCandidatos().empty() || p2->getListaCandidatos().empty()) {
            return false;
        }
        else if (p1->getListaCandidatos()[0]->getVotosNominais() != p2->getListaCandidatos()[0]->getVotosNominais()) {
            return p2->getListaCandidatos()[0]->getVotosNominais() < p1->getListaCandidatos()[0]->getVotosNominais();
        }
            return p1->getNumeroPartido() < p2->getNumeroPartido();
    });


    pos = 1;
    //Imprime os primeiros e último colocados de cada partido (8)
    std::cout << "\nPrimeiro e último colocados de cada partido:" << std::endl;

    for (Partido* p : listaPartidos) {
        if (!p->getListaCandidatos().empty()) {
            if (p->getListaCandidatos()[p->getListaCandidatos().size() - 1]->getVotosNominais() > 1) {

                //Imprime no formato especificado
                std::cout << pos << " - " << p->getSiglaPartido() << " - " << p->getNumeroPartido() << ", " << p->getListaCandidatos()[0]->getNomeUrna() <<
                " (" << p->getListaCandidatos()[0]->getNumero() << ", " << p->getListaCandidatos()[0]->getVotosNominais() << " votos) / " <<
                p->getListaCandidatos()[p->getListaCandidatos().size() - 1]->getNomeUrna() << " (" << p->getListaCandidatos()[p->getListaCandidatos().size() - 1]->getNumero()
                << ", " << p->getListaCandidatos()[p->getListaCandidatos().size() - 1]->getVotosNominais() << " votos)" << std::endl;
            } else {

                //Imprime no formato especificado
                std::cout << pos << " - " << p->getSiglaPartido() << " - " << p->getNumeroPartido() << ", " << p->getListaCandidatos()[0]->getNomeUrna() <<
                          " (" << p->getListaCandidatos()[0]->getNumero() << ", " << p->getListaCandidatos()[0]->getVotosNominais() << " votos) / " <<
                          p->getListaCandidatos()[p->getListaCandidatos().size() - 1]->getNomeUrna() << " (" << p->getListaCandidatos()[p->getListaCandidatos().size() - 1]->getNumero()
                          << ", " << p->getListaCandidatos()[p->getListaCandidatos().size() - 1]->getVotosNominais() << " voto)" << std::endl;
            }
        }
        pos++;
    }




    //Variaveis para imprimir os itens 9 e 10
    int intervalos[] = {0,0,0,0,0}; // Cada posição indica um dos intervalos determinados, em ordem
    int masculino = 0;
    int feminino = 0;

    for (Candidato* c : candidatosEleitos) {

        //Verifica se é masculino ou feminino
        if (c->getSexo() == "M") {
            masculino++;
        } else {
            feminino++;
        }

        //comparar as datas
    }




    //Imprime a distribuição de eleitos por faixa etária, considerando a idade do candidato no dia da eleição (9)
    std::cout << "\nEleitos, por faixa etária (na data da eleição):" << std::endl;

    //Imprime a distribuição de eleitos por sexo (10)
    std::cout << "Eleitos, por sexo:" << std::endl;
    std::printf("Feminino: %d (%.2f%%)\n",feminino,100.0 * feminino / vagas);
    std::printf("Masculino: %d (%.2f%%)\n",masculino,100.0 * masculino / vagas);

    int votos_validos = 0;
    int votos_nominais = 0;
    int votos_legenda = 0;

    //Calcula os votos totais, nominais e de legenda
    for (Partido* p : listaPartidos) {
        votos_validos += p->getVotosTotais();
        votos_nominais += p->getVotosNominais();
        votos_legenda += p->getVotosLegenda();
    }

    //Imprime o total de votos, os nominais e os de legenda (11)
    std::printf("\nTotal de votos válidos:    %d\n",votos_validos);
    std::printf("Total de votos nominais:   %d (%.2f%%)\n",votos_nominais,100.0 * votos_nominais/votos_validos);
    std::printf("Total de votos de legenda: %d (%.2f%%)\n",votos_legenda,100.0 * votos_legenda/votos_validos);

    //Libera a memória alocada para os candidatos e partidos
    for (Candidato* c : listaCandidatos) {
        delete(c);
    }

    for (Partido* p : listaPartidos) {
        delete(p);
    }

    return 0;
}
