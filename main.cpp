#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
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
        //std::exit(1);
    }

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

    std::list<Candidato> listaCandidatos;
    int counter = 0;
    for (auto& dado : csvCandidatos) {
        if (counter == 0) {
            counter++;
            continue;
        }
        Candidato candidato(std::stoi(dado[0]),std::stoi(dado[1]),dado[2],dado[3],dado[4],dado[5],dado[6],dado[7],std::stoi(dado[8]));
        listaCandidatos.push_back(candidato);
    }

    conteudoLinha = CSVparaLinha(argv[2]);
    std::list<std::vector<std::string>> csvPartidos;
    std::istringstream stringPartidos(conteudoLinha);
    std::list<Partido> listaPartidos;

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
        Partido partido(std::stoi(dado[0]),std::stoi(dado[1]),dado[2],dado[3]);
        listaPartidos.push_back(partido);
    }

    for (Candidato c : listaCandidatos) {
        for (Partido p : listaPartidos) {
            if (c.getNumeroPartido() == p.getNumeroPartido()) {
                c.setPartido(p);
            }
        }
    }

    for (Candidato c : listaCandidatos) {
        std::cout << c.getPartido()->getNumeroPartido() << std::endl;
    }

    return 0;
}
