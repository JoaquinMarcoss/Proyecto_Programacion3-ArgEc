#include <ctime>
#include <sstream>
#include <fstream>
#include <iostream>
#include <time.h>
#include <cmath>
#include <vector>
#include <cctype>
#include "../Lista/Lista.h"
#include "../Pila/Pila.h"
#include "../Cola/Cola.h"
#include "../HashMap/HashMap.h"
#include "../HashMap/HashMapList.h"
#include "../Arbol/ArbolBinario.h"
#define ARCHIVO "C:\\Users\\Joaquin\\Desktop\\Proyecto_Programacion3-ArgEc\\Inventariado_Fisico.csv"
using namespace std;

void Total_Articulos(int total_art){
    cout<<endl<<" Cantidad total de articulos totales: "<<total_art;
}

void Total_Articulos_Diferentes(int total_art_dif){
    cout<<endl<<" Cantidad total de articulos totales diferentes: "<<total_art_dif;
}

void min_stock(Lista<string> Lista_Min_Stock){
    cout<<endl<<" \n--MINIMO STOCK-- ";
    for(int i=0; i<Lista_Min_Stock.getTamanio(); i++){
        cout<<endl<<" Articulo: "<<Lista_Min_Stock.getDato(i);
    }
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

void stock_Nombre(string nombre_articulo){

}

unsigned int HashFunc(string clave) {
    unsigned int hash = 0;
    // Sumar los valores ASCII de los caracteres en la clave
    for (char c : clave) {
        hash += static_cast<unsigned int>(c);
    }
    // Aplicar una operación módulo para obtener un índice válido en la tabla hash
    hash = hash % 100000;
    cout<<endl<<" Hash para la clave: "<<clave<<": "<<hash;
    return hash;
}

void stock_Deposito(string nombre_articulo){
    ifstream archivo(ARCHIVO);
    string line, Nombre_Art, Cols;
    int i, Cant_cols = 0, total_art=0, total_art_dif=0, n=80;
    vector<int> Vector_Depositos;
    HashMap<string, vector<int>> Hash_Articulos(100000, &HashFunc);
    getline(archivo, line);//encabezado
    stringstream c(line);

    while (getline(c, Cols, ',')){
        Cant_cols++;
    }

    while (getline(archivo, line)){
        stringstream s(line);//convertimos la cadena a un objeto el cual un programa puede insertar o extraer datos
        string Deposito;
        string word;
        vector<int> Lista_Depositos(Cant_cols-3, 0);
        int num=0, Cant_art=0;
        for (i = 0; i < Cant_cols; i++){
            getline(s, word, ',');

            if(i==2) Nombre_Art = word;

            if (i > 2){
                if(word.size()>0) {
                    num = stoi(word);
                    Lista_Depositos[i] = num;
                }else{
                    Lista_Depositos[i] = 0;
                }
            }
        }
        Hash_Articulos.put(Nombre_Art, Lista_Depositos);
    }
    vector<int> Deposito;
    Deposito = Hash_Articulos.get(nombre_articulo);
    for(int i=0; i<5; i++){
        cout<<endl<<Deposito[i];
    }
}

void max_stock(Lista<string> Lista_Max_Stock){
    cout<<endl<<" \n--MAXIMO STOCK-- ";
    for(int i=0; i<Lista_Max_Stock.getTamanio(); i++){
        cout<<endl<<" Articulo: "<<Lista_Max_Stock.getDato(i);
    }
}



int main(){
    ifstream archivo(ARCHIVO);
    string line, Nombre_Art, Cols;
    int i, Cant_cols = 0, total_art=0, total_art_dif=0, n=80;
    vector<int> Vector_Depositos;
    Lista<string> Lista_Min_Stock;
    Lista<string> Lista_Max_Stock;
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
        if(Cant_art<=n) Lista_Min_Stock.insertarUltimo(Nombre_Art);
        if(Cant_art>=n) Lista_Max_Stock.insertarUltimo(Nombre_Art);
        total_art_dif++;
        }

        archivo.close();
        string Nombre;
        clock_t begin; //Declacaramos el contador
        cout << "Comenzando a medir Tiempo\n" << endl;
        begin = clock(); //Empieza el contador


        //Total_Articulos(total_art);
        //Total_Articulos_Diferentes(total_art_dif);
        //min_stock(Lista_Min_Stock);
        //max_stock(Lista_Max_Stock);
        stock_Deposito("BANQUETA TAPIZADA COST BCO  BASE PINTADA NEGRO");

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