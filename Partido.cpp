#include <vector>
#include "Partido.h"

Partido::Partido(int nPartido, int votosLegenda,const std::string &nomePartido,const std::string &siglaPartido) {
    this->numero_partido = nPartido;
    this->votos_legenda = votosLegenda;
    this->nome_partido = nomePartido;
    this->sigla_partido = siglaPartido;
    this->votos_totais = 0;
    this->votos_nominais = 0;
    this->candidatos_eleitos = 0;
}

int Partido::getNumeroPartido() const {
    return numero_partido;
}

void Partido::setNumeroPartido(int numeroPartido) {
    numero_partido = numeroPartido;
}

int Partido::getVotosLegenda() const {
    return votos_legenda;
}

void Partido::setVotosLegenda(int votosLegenda) {
    votos_legenda = votosLegenda;
}

const std::string &Partido::getNomePartido() const {
    return nome_partido;
}

void Partido::setNomePartido(const std::string &nomePartido) {
    nome_partido = nomePartido;
}

const std::string &Partido::getSiglaPartido() const {
    return sigla_partido;
}

void Partido::setSiglaPartido(const std::string &siglaPartido) {
    sigla_partido = siglaPartido;
}

int Partido::getVotosTotais() const {
    return votos_totais;
}

void Partido::setVotosTotais(int votosTotais) {
    votos_totais = votosTotais;
}

int Partido::getVotosNominais() const {
    return votos_nominais;
}

void Partido::setVotosNominais(int votosNominais) {
    votos_nominais = votosNominais;
}

int Partido::getCandidatosEleitos() const {
    return candidatos_eleitos;
}

void Partido::setCandidatosEleitos(int candidatosEleitos) {
    candidatos_eleitos = candidatosEleitos;
}

std::vector<Candidato*> Partido::getListaCandidatos() {
    return this->lista_candidatos;
}

void Partido::incrementaVotos(int votos) {
    this->votos_nominais += votos;
    this->votos_totais += votos;
}

void Partido::incrementaCandidatosEleitos() {
    this->candidatos_eleitos++;
}

void Partido::adicionaCandidato(Candidato* p) {
    this->lista_candidatos.push_back(p);
}

