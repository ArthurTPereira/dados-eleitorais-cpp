#ifndef CANDIDATO_H
#define CANDIDATO_H

#include <string>

class Partido;

class Candidato {
    int numero;
    int votos_nominais;
    std::string situacao;
    std::string nome;
    std::string nome_urna;
    std::string sexo;
    std::string data_nasc;
    std::string destino_voto;
    int numero_partido;
    Partido* partido;

public:
    Candidato(int numero, int votosNominais, const std::string &Situacao, const std::string &Nome,
              const std::string &nomeUrna, const std::string &Sexo, const std::string &dataNasc, const std::string &destinoVoto,
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

    std::string getSexo() const;

    void setSexo(const std::string &Sexo);

    const std::string &getDataNasc() const;

    void setDataNasc(const std::string &dataNasc);

    const std::string &getDestinoVoto() const;

    void setDestinoVoto(const std::string &destinoVoto);

    int getNumeroPartido() const;

    void setNumeroPartido(int numeroPartido);

    Partido* getPartido() const;

    void setPartido(Partido &Partido);

};


#endif //CANDIDATO_H
