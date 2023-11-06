#include <ctime>
#include <sstream>
#include <fstream>
#include <iostream>
#include <time.h>
#include <cmath>
#include <cctype>
#include "../Lista/Lista.h"
#include "../Pila/Pila.h"
#include "../Cola/Cola.h"
#include "../HashMap/HashMap.h"
#include "../HashMap/HashMapList.h"
#include "../Arbol/ArbolBinario.h"
#define ARCHIVO "C:\\Users\\Joaquin\\Desktop\\Proyecto_Programacion3-ArgEc\\Inventariado_Fisico.csv"
using namespace std;

void Cant_Articulos(){}

void min_stock(HashMap<int,string> H_min){
    cout<<endl<<" --MINIMO STOCK--"<<endl;
    H_min.print();
}

void min_stock(int n, int deposito){
    ifstream archivo(ARCHIVO);
    string line, Nombre_Art, Cols;
    int i, Cant_cols=0;

    getline(archivo, line);//encabezado
    stringstream c(line);
    while(getline(c, Cols, ',')){
        Cant_cols++;
    }

    while (getline(archivo, line)) {
        stringstream s(line);
        string word;
        int num = 0, Cant_art = 0;
        for (i = 0; i<Cant_cols; i++) {
            getline(s, word, ',');
            if (i == 2){
                Nombre_Art = word;
            }
            if (i == deposito+2){
                try{
                    Cant_art = stoi(word);
                }catch (const invalid_argument &e){}
            }
        }
        if(Cant_art!=0 && Cant_art<=n){
            cout<<endl<<" Nombre del Articulo: "<<Nombre_Art;
            cout<<endl<<" Stock en el Deposito "<<deposito<<": "<<Cant_art;
        }
    }
}

void stock(string nombre_articulo){

}

void stock(string nombre_articulo, int deposito){
    ifstream archivo(ARCHIVO);
    string line, Nombre_Art, Cols;
    int i, Cant_cols=0;

    getline(archivo, line);//encabezado
    stringstream c(line);
    while(getline(c, Cols, ',')){
        Cant_cols++;
    }

    while (getline(archivo, line)) {
        stringstream s(line);
        string word;
        int num = 0, Cant_art = 0;
        for (i = 0; i<Cant_cols; i++) {
            getline(s, word, ',');
            if (i == 2){
                Nombre_Art = word;
            }
            if (i == deposito+2){
                try{
                    Cant_art = stoi(word);
                }catch (const invalid_argument &e){}
            }
        }
        if(Cant_art!=0){
            cout<<endl<<" Nombre del Articulo: "<<Nombre_Art;
            cout<<endl<<" Stock en el Deposito "<<deposito<<": "<<Cant_art;
        }
    }
}

void max_stock(HashMap<int,string> H_max){
    cout<<endl<<" --MAXIMO STOCK--"<<endl;
    H_max.print();
}

int main(int argc, char **argv){
    ifstream archivo(ARCHIVO);
    string line, Nombre_Art, Cols;
    int i, Cant_cols = 0, total_art=0, total_art_dif=0, n=80;
    HashMap<int, string> Art_Min_Stock(500);
    HashMap<int, string> Art_Max_Stock(500);


    getline(archivo, line);//encabezado
    stringstream c(line);
    while (getline(c, Cols, ',')){
        Cant_cols++;
    }

    while (getline(archivo, line)){
        stringstream s(line);//convertimos la cadena a un objeto el cual un programa puede insertar o extraer datos
        string Deposito;
        string word;
        int num=0, Cant_art=0;
        for (i = 0; i < Cant_cols; i++){
            getline(s, word, ',');

            if(i==2) Nombre_Art = word;

            if (i > 2){
                if(word.size()>0) {
                    num = stoi(word);
                    Cant_art += num;
                    total_art += num;
                }
            }
        }
        if(Cant_art<=n) Art_Min_Stock.put(Cant_art, Nombre_Art);
        if(Cant_art>=n) Art_Max_Stock.put(Cant_art, Nombre_Art);
        total_art_dif++;
        }

        archivo.close();

        clock_t begin; //Declacaramos el contador
        cout << "Comenzando a medir Tiempo\n" << endl;
        begin = clock(); //Empieza el contador

        cout<<endl<<total_art;
        cout<<endl<<total_art_dif<<endl;
        min_stock(Art_Min_Stock);
        max_stock(Art_Max_Stock);

        cout << endl;
        clock_t end = clock();
        double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
        cout << "Tardo elapsed_secs " << elapsed_secs << "\n" << std::endl;
        return 0;
    }







/*clock_t begin;
    cout << "Comenzando a medir Tiempo\n" << endl;

    begin = clock();
    /*
     * Insertar código a medir tiempo aquí

    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    cout << "Tardo elapsed_secs" << elapsed_secs << "\n" << std::endl;*/

/*
 * ifstream archivo(ARCHIVO);
    string linea;
    int total_art_dif=0; // total de articulos diferentes
    int total_art=0; // total de articulos

    if(!archivo.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return 1; // Sale del programa con un código de error
    }

    getline(archivo,linea);//descartamos el encabezado 1,2,3,,4,,,5,,6 --> [1,2,3,4,5,6]

    while(getline(archivo,linea)){
        stringstream s(linea);//convertimos la cadena a un objeto el cual un programa puede insertar o extraer datos
        string Grupo, Cod_Barras, Articulo, Dep_1, Dep_2, Dep_3, Dep_4, Dep_5;

        //extraemos los cada dato de la fila
        getline(s, Grupo, ',');
        getline(s, Cod_Barras, ',');
        getline(s, Articulo, ',');
        getline(s, Dep_1, ',');
        getline(s, Dep_2, ',');
        getline(s, Dep_3, ',');
        getline(s, Dep_4, ',');
        getline(s, Dep_5, ',');

        //Imprimimos los datos por pantalla
        if(Grupo!=""){
            cout<<endl<<"\n=========================================================";
            cout<<endl<<"Grupo: "<<Grupo;
            total_art_dif++;
        }
        cout<<endl<<"\nCodigo de Barras: "<<Cod_Barras;
        cout<<endl<<"Articulo: "<<Articulo;
        total_art++;
        if(Dep_1!="") cout<<endl<<"Deposito 1: "<<Dep_1;
        if(Dep_2!="") cout<<endl<<"Deposito 2: "<<Dep_2;
        if(Dep_3!="") cout<<endl<<"Deposito 3: "<<Dep_3;
        if(Dep_4!="") cout<<endl<<"Deposito 4: "<<Dep_4;
        if(Dep_5!="") cout<<endl<<"Deposito 5: "<<Dep_5;
    }

    cout<<endl<<" Total de articulos: "<<total_art;
    cout<<endl<<" Total de articulos diferentes: "<<total_art_dif;
    archivo.close();
    return 0;
}*/