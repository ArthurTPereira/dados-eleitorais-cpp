#ifndef CANDIDATO_H
#define CANDIDATO_H

#include <string>
#include "Partido.h"

class Candidato {
    int numero;
    int votos_nominais;
    std::string situacao;
    std::string nome;
    std::string nome_urna;
    char sexo;
    std::string data_nasc;
    std::string destino_voto;
    int numero_partido;
    Partido partido;

public:
    Candidato(int numero, int votosNominais, const std::string &Situacao, const std::string &Nome,
              const std::string &nomeUrna,char Sexo,const std::string &dataNasc, const std::string &destinoVoto,
              int numeroPartido);

    int getNumero() const;

    void setNumero(int numero);

    int getVotosNominais() const;

    void setVotosNominais(int votosNominais);

    const std::string &getSituacao() const;

    void setSituacao(const std::string &Situacao);

    const std::string &getNome() const;

    void setNome(const std::string &Nome);

    const std::string &getNomeUrna() const;

    void setNomeUrna(const std::string &nomeUrna);

    char getSexo() const;

    void setSexo(char Sexo);

    const std::string &getDataNasc() const;

    void setDataNasc(const std::string &dataNasc);

    const std::string &getDestinoVoto() const;

    void setDestinoVoto(const std::string &destinoVoto);

    int getNumeroPartido() const;

    void setNumeroPartido(int numeroPartido);

    const Partido &getPartido() const;

    void setPartido(const Partido &Partido);

};


#endif //CANDIDATO_H
