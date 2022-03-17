#ifndef DATA_H
#define DATA_H


class Data {
    int dia;
    int mes;
    int ano;

public:
    Data(std::string data);

    int getDia() const;

    int getMes() const;

    int getAno() const;

    int anosEntreDatas(Data* d1,Data* d2);

    int diasEntreDatas(Data* d1, Data* d2);

    int getDiasTotais();
};


#endif
