#include <ctime>
#include <sstream>
#include <fstream>
#include <iostream>
#include <time.h>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <cctype>
#include "../Lista/Lista.h"
#include "../HashMap/HashMap.h"
#include "../HashMap/HashMapList.h"
#define ARCHIVO "C:\\Users\\Joaquin\\Desktop\\Proyecto_Programacion3-ArgEc\\Inventariado_Fisico.csv"
using namespace std;

void Total_Articulos(int total_art){
    cout<<endl<<" Cantidad total de articulos totales: "<<total_art;
}

void Total_Articulos_Diferentes(int total_art_dif){
    cout<<endl<<" Cantidad total de articulos totales diferentes: "<<total_art_dif;
}

void min_stock(int Cant_Stock_MinS, Lista<string> Lista_Min_Stock){
    cout<<endl<<" \n--ARTICULOS CON STOCK MENOR O IGUAL A "<<Cant_Stock_MinS<<"-- ";
    for(int i=0; i<Lista_Min_Stock.getTamanio(); i++){
        cout<<endl<<" Articulo: "<<Lista_Min_Stock.getDato(i);
    }
}

void min_stock_deposito(int Cant_Stock_MSD, int Num_Deposito, Lista<string> Lista_Min_Stock_Deposito){
    cout<<endl<<" \n--ARTICULOS CON STOCK MENOR O IGUAL A "<<Cant_Stock_MSD<<" EN EL DEPOSITO "<<Num_Deposito<<"-- ";
    for(int i=0; i<Lista_Min_Stock_Deposito.getTamanio(); i++){
        cout<<endl<<" Articulo: "<<Lista_Min_Stock_Deposito.getDato(i);
    }
}

void stock_Deposito(string nombre_articulo, int Num_deposito, HashMap<string, vector<int>> Hash_Articulos){
    vector<int> Deposito;

    Deposito = Hash_Articulos.get(nombre_articulo);
    cout<<endl<<" Cantidad de stock del articulo "<<nombre_articulo<<" en el deposito "<<Num_deposito<<": "<<Deposito[Num_deposito-1]<<endl;
}

void stock_Nombre(string nombre_articulo, HashMap<string, vector<int>> Hash_Articulos){
    vector<int> Deposito;
    int Cantidad_Stock = 0;

    Deposito = Hash_Articulos.get(nombre_articulo);
    for(int i=0; i<Deposito.size(); i++){
        Cantidad_Stock += Deposito[i];
    }
    cout<<endl<<" Cantidad de stock del articulo "<<nombre_articulo<<": "<<Cantidad_Stock<<endl;
}

void max_stock(int Cant_Stock_MaxS, Lista<string> Lista_Max_Stock){
    cout<<endl<<" \n--ARTICULOS CON STOCK MAYOR O IGUAL A "<<Cant_Stock_MaxS<<"-- ";
    for(int i=0; i<Lista_Max_Stock.getTamanio(); i++){
        cout<<endl<<" Articulo: "<<Lista_Max_Stock.getDato(i);
    }
}

unsigned int HashFunc(string clave){
    unsigned int hash = 0;
    // Sumar los valores ASCII de los caracteres en la clave
    for (char c : clave) {
        hash += static_cast<unsigned int>(c);
    }
    // Aplicar una operación módulo para obtener un índice válido en la tabla hash
    hash = hash % 232;
    //cout<<endl<<" Hash para la clave '"<<clave<<"': "<<hash;
    return hash;
}

int main(){
    ifstream archivo(ARCHIVO);
    string line, Nombre_Art, Cols;
    int i, Cant_cols = 0, total_art=0, total_art_dif=0, n=80, Num_Deposito=3, Cant_Stock_MSD=6, Cant_Stock_MinS=15, Cant_Stock_MaxS=50;
    Lista<string> Lista_Min_Stock;
    Lista<string> Lista_Max_Stock;
    Lista<string> Lista_Min_Stock_Deposito;
    HashMap<string, vector<int>> Hash_Articulos(1000, HashFunc);
    getline(archivo, line);//encabezado
    stringstream c(line);

    while (getline(c, Cols, ',')){
        Cant_cols++;
    }

    while (getline(archivo, line)){
        stringstream s(line);//convertimos la cadena a un objeto el cual un programa puede insertar o extraer datos
        string Deposito;
        string word;
        int num=0, Cant_art=0, pos=0, Cant_stock_Dep;
        vector<int> Lista_Depositos(Cant_cols-3, 0);
        for (i = 0; i < Cant_cols; i++){
            getline(s, word, ',');

            if(i==2) Nombre_Art = word;

            if (i>2){
                if(word.size()>0){
                    num = stoi(word);
                    Cant_art += num;
                    total_art += num;
                    Lista_Depositos[pos] = num;
                    pos++;
                }else{
                    Lista_Depositos[pos] = 0;
                    pos++;
                }
            }

            if(i == Num_Deposito+2){
                if(word.size()>0 && stoi(word)<=Cant_Stock_MSD){
                    Lista_Min_Stock_Deposito.insertarUltimo(Nombre_Art);
                }
            }
        }
        if(Cant_art<=Cant_Stock_MinS) Lista_Min_Stock.insertarUltimo(Nombre_Art);
        if(Cant_art>=Cant_Stock_MaxS) Lista_Max_Stock.insertarUltimo(Nombre_Art);
        total_art_dif++;

        Hash_Articulos.put(Nombre_Art, Lista_Depositos);
    }

    archivo.close();
    string Nombre;
    clock_t begin; //Declacaramos el contador
    cout << "Comenzando a medir Tiempo\n" << endl;
    begin = clock(); //Empieza el contador

    //Total_Articulos(total_art);
    //Total_Articulos_Diferentes(total_art_dif);
    //min_stock(Cant_Stock_MinS, Lista_Min_Stock);
    //max_stock(Cant_Stock_MaxS, Lista_Max_Stock);
    //stock_Nombre("BANQUETA TAPIZADA COST BCO  BASE PINTADA NEGRO", Hash_Articulos);
    //stock_Deposito("BANQUETA TAPIZADA COST BCO  BASE PINTADA NEGRO", 4, Hash_Articulos);
    //min_stock_deposito(Cant_Stock_MSD, Num_Deposito, Lista_Min_Stock_Deposito);

    clock_t end = clock();
    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
    cout<<"Tardo elapsed_secs " << elapsed_secs << "\n" << std::endl;
    return 0;
}