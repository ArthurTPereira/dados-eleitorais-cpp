#include <string>
#include "Data.h"

Data::Data(std::string data) {
    int dia,mes,ano;
    std::sscanf(data.c_str(),"%d/%d/%d",&dia,&mes,&ano);

    this->dia = dia;
    this->mes = mes;
    this->ano = ano;
}

int Data::getDia() const {
    return this->dia;
}

int Data::getMes() const {
    return this->mes;
}

int Data::getAno() const {
    return this->ano;
}

int Data::anosEntreDatas(Data* d1, Data* d2) {
    const int diasMeses[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int v1 = 365 * d1->ano + d1->dia;
    int v2 = 365 * d2->ano + d2->dia;

    for (int i = 0; i < d1->mes; ++i) {
        v1 += diasMeses[i];
    }

    for (int i = 0; i < d2->mes; ++i) {
        v2 += diasMeses[i];
    }

    return (v1-v2) / 365;
}

int Data::diasEntreDatas(Data* d1, Data* d2) {
    const int diasMeses[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int v1 = 365 * d1->ano + d1->dia;
    int v2 = 365 * d2->ano + d2->dia;

    for (int i = 0; i < d1->mes; ++i) {
        v1 += diasMeses[i];
    }

    for (int i = 0; i < d2->mes; ++i) {
        v2 += diasMeses[i];
    }

    return (v1-v2);
}

int Data::getDiasTotais() {
    const int diasMeses[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int v1 = 365 * this->ano + this->dia;

    for (int i = 0; i < this->mes; ++i) {
        v1 += diasMeses[i];
    }

    return v1;
}