//
// Created by Raul.Mosquera on 23/05/2021.
//

#ifndef EDA_TREE_TESTER_H
#define EDA_TREE_TESTER_H

#include "../Components/two_d_range_tree.h"

class metadata {
public:
    vector<coordinate> points;
    coordinate begin;
    coordinate end;
};

class tester {
public:

    void static process(string fileNameIn) {
        two_d_range_tree tree2D;

        auto dataTest = readFromFile(fileNameIn);

        tree2D.build_tree(dataTest.points);

        auto result = tree2D.range_query(dataTest.begin, dataTest.end);
        cout << " Ordered result " << endl;
        sort(result.begin(), result.end(), cmpCoordinateX);

        //Creacion del archivo
        ofstream archivo;
        string NombreArchivo,newName;
        cout<<"Escriba el nombre de como se llamara su archivo:  ";
        getline(cin,NombreArchivo);
        newName = "../Result/"+NombreArchivo;
        archivo.open(newName.c_str(),ios::out);
        if(archivo.fail()){cout<<"No se encontro el archivo";exit(1);}

        for(auto elem: result) {
            cout << elem.first << " " << elem.second << endl;
            archivo<< elem.first << " " << elem.second << endl;
        }
        cout << " Text created address : '../Result/"<<NombreArchivo<<"'"<<endl;
        archivo.close();

    }

private:
    metadata static readFromFile(const string& fileNameIn) {
        metadata data;
        vector<coordinate> tmp;
        fstream file;
        string linea;
        file = fstream();

        file.open(fileNameIn, ios::in);

        if (!file.is_open())
            cout << " File error " << endl;

        getline(file, linea);
        data.begin = getCoord(linea);

        getline(file, linea);
        data.end = getCoord(linea);

        getline(file, linea);
        auto N = stoi(linea);

        for (int i = 0; i < N; i++) {
            getline(file, linea);
            auto coor = getCoord(linea);
            data.points.push_back(coor);
        }

        if (file.is_open())
            file.close();

        return data;
    }

    coordinate static getCoord(string line) {
        coordinate x_y;
        char str[line.length() + 1];
        strcpy(str, line.c_str());

        char *pch;
        pch = strtok(str, " ");

        int index = 0;
        while (pch != NULL) {
            switch (index) {
                case 0:
                    x_y.first = atoi(pch);
                    break;
                case 1:
                    x_y.second = atoi(pch);
                    break;
            }
            pch = strtok(NULL, " ");
            index++;
        }

        return x_y;
    }
};


#endif //EDA_TREE_TESTER_H
