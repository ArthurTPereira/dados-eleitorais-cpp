#include "Candidato.h"

Candidato::Candidato(int numero, int votosNominais,const std::string &Situacao,const std::string &Nome, const std::string &nomeUrna,
                     char Sexo, const std::string &dataNasc, const std::string &destinoVoto, int numeroPartido) {
    this->numero = numero;
    this->votos_nominais = votosNominais;
    this->situacao = Situacao;
    this->nome = Nome;
    this->nome_urna = nomeUrna;
    this->sexo = Sexo;
    this->data_nasc = dataNasc;
    this->destino_voto = destinoVoto;
    this->numero_partido = numeroPartido;
}

int Candidato::getNumero() const {
    return numero;
}

void Candidato::setNumero(int Numero) {
    Candidato::numero = Numero;
}

int Candidato::getVotosNominais() const {
    return votos_nominais;
}

void Candidato::setVotosNominais(int votosNominais) {
    votos_nominais = votosNominais;
}

const std::string &Candidato::getSituacao() const {
    return situacao;
}

void Candidato::setSituacao(const std::string &Situacao) {
    Candidato::situacao = Situacao;
}

const std::string &Candidato::getNome() const {
    return nome;
}

void Candidato::setNome(const std::string &Nome) {
    Candidato::nome = Nome;
}

const std::string &Candidato::getNomeUrna() const {
    return nome_urna;
}

void Candidato::setNomeUrna(const std::string &nomeUrna) {
    nome_urna = nomeUrna;
}

char Candidato::getSexo() const {
    return sexo;
}

void Candidato::setSexo(char Sexo) {
    Candidato::sexo = Sexo;
}

const std::string &Candidato::getDataNasc() const {
    return data_nasc;
}

void Candidato::setDataNasc(const std::string &dataNasc) {
    data_nasc = dataNasc;
}

const std::string &Candidato::getDestinoVoto() const {
    return destino_voto;
}

void Candidato::setDestinoVoto(const std::string &destinoVoto) {
    destino_voto = destinoVoto;
}

int Candidato::getNumeroPartido() const {
    return numero_partido;
}

void Candidato::setNumeroPartido(int numeroPartido) {
    numero_partido = numeroPartido;
}

const Partido &Candidato::getPartido() const {
    return partido;
}

void Candidato::setPartido(const Partido &Partido) {
    Candidato::partido = Partido;
}
