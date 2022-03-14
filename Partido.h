#ifndef PARTIDO_H
#define PARTIDO_H

#include <string>
#include <list>

class Candidato;

class Partido {
    int numero_partido;
    int votos_legenda;
    std::string nome_partido;
    std::string sigla_partido;
    int votos_totais;
    int votos_nominais;
    int candidatos_eleitos;
    std::vector<Candidato*> lista_candidatos;

public:
    Partido(int nPartido, int votosLegenda, const std::string &nomePartido, const std::string &siglaPartido);

    int getNumeroPartido() const;

    void setNumeroPartido(int numeroPartido);

    int getVotosLegenda() const;

    void setVotosLegenda(int votosLegenda);

    const std::string &getNomePartido() const;

    void setNomePartido(const std::string &nomePartido);

    const std::string &getSiglaPartido() const;

    void setSiglaPartido(const std::string &siglaPartido);

    int getVotosTotais() const;

    void setVotosTotais(int votosTotais);

    int getVotosNominais() const;

    void setVotosNominais(int votosNominais);

    int getCandidatosEleitos() const;

    void setCandidatosEleitos(int candidatosEleitos);

    std::vector<Candidato*> getListaCandidatos();

    void incrementaVotos(int votos);

    void incrementaCandidatosEleitos();

    void adicionaCandidato(Candidato* p);

};


#endif //PARTIDO_H
