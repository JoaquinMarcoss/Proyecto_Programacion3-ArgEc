#include <sstream>
#include <fstream>
#include <iostream>
#include <time.h>
#include <vector>
#include <cstring>
#include <string>
#include "../Lista/Lista.h"
#include "../HashMap/HashMap.h"
#define ARCHIVO "C:\\Users\\Joaquin\\Desktop\\Proyecto_Programacion3-ArgEc\\Inventariado_Fisico.csv"
using namespace std;

void Total_Articulos(int total_art){
    cout<<" \nCANTIDAD TOTAL DE ARTICULOS: "<<total_art<<endl;
}

void Total_Articulos_Diferentes(int total_art_dif){
    cout<<" \nCANTIDAD TOTAL DE ARTICULOS DIFERENTES: "<<total_art_dif<<endl;
}

void Min_Stock(int Cant_Stock_MinS, Lista<string> Lista_Min_Stock){
    cout<<" \n--- ARTICULOS CON STOCK MENOR O IGUAL A "<<Cant_Stock_MinS<<" --- ";
    for(int i=0; i<Lista_Min_Stock.getTamanio(); i++){
        cout<<endl<<" Articulo: "<<Lista_Min_Stock.getDato(i);
    }
    cout<<endl;
}

void Min_Stock_Deposito(int Cant_Stock_MSD, int Num_Deposito, Lista<string> Lista_Min_Stock_Deposito){
    cout<<" \n--- ARTICULOS CON STOCK MENOR O IGUAL A "<<Cant_Stock_MSD<<" EN EL DEPOSITO "<<Num_Deposito<<" --- ";
    for(int i=0; i<Lista_Min_Stock_Deposito.getTamanio(); i++){
        cout<<endl<<" Articulo: "<<Lista_Min_Stock_Deposito.getDato(i);
    }
    cout<<endl;
}

void Stock_Deposito(string nombre_articulo, int Num_deposito, HashMap<string, vector<int>> Hash_Articulos){
    vector<int> Deposito;
    Deposito = Hash_Articulos.get(nombre_articulo);
    cout<<" \nCANTIDAD DE STOCK DE '"<<nombre_articulo<<"' EN EL DEPOSITO "<<Num_deposito<<": "<<Deposito[Num_deposito-1]<<endl;
}

void Stock_Nombre(string nombre_articulo, HashMap<string, vector<int>> Hash_Articulos){
    vector<int> Deposito;
    int Cantidad_Stock = 0;
    Deposito = Hash_Articulos.get(nombre_articulo);
    for(int i=0; i<Deposito.size(); i++){
        Cantidad_Stock += Deposito[i];
    }
    cout<<" \nCANTIDAD DE STOCK DEL ARTICULO '"<<nombre_articulo<<"': "<<Cantidad_Stock<<endl;
}

void Max_Stock(int Cant_Stock_MaxS, Lista<string> Lista_Max_Stock){
    cout<<" \n--- ARTICULOS CON STOCK MAYOR O IGUAL A "<<Cant_Stock_MaxS<<" --- ";
    for(int i=0; i<Lista_Max_Stock.getTamanio(); i++){
        cout<<endl<<" Articulo: "<<Lista_Max_Stock.getDato(i);
    }
    cout<<endl;
}

unsigned int HashFunc(string clave){
    unsigned int hash = 0;
    // Sumar los valores ASCII de los caracteres en la clave
    for (char c : clave){
        hash += static_cast<unsigned int>(c);
    }
    // Aplicar una operación módulo para obtener un índice válido en la tabla hash
    hash = hash % 2087;
    //cout<<endl<<" Hash para la clave '"<<clave<<"': "<<hash;
    return hash;
}


/* argc = Cuantos argumentos le estamos
 *        pasando a la hora de ejecutarse
 *
 * argv = Cada uno de los argumentos dichos
 *        (cadenas de caracteres)
 */
int main(int argc, char **argv){
    int i, Cant_cols=0, total_art=0, total_art_dif=0,Num_Stock_Deposito=1, Num_Deposito=1, Cant_Stock_MSD=1, Cant_Stock_MinS=0, Cant_Stock_MaxS=0;
    string Nombre_Articulo_Stock, Nombre_Articulo_Deposito;
    int bandera=2;
    cout<<"\nCantidad de argumentos: "<<argc<<endl;
        //Minimo Stock
        if(strcmp(argv[1],"-min_stock")==0) Cant_Stock_MinS = stoi(argv[2]);
        //Maximo Stock
        if(strcmp(argv[1],"-max_stock")==0) Cant_Stock_MaxS = stoi(argv[2]);
        //Minimo Stock por deposito
        if(strcmp(argv[1],"-min_stock")==0 && argc>3){
            Cant_Stock_MSD = stoi(argv[2]);
            Num_Deposito = stoi(argv[3]);
        }
        //Stock de un articulo
        if(strcmp(argv[1],"-stock")==0){
            for (i=2; i<argc; i++){
                Nombre_Articulo_Stock += argv[i];
                if(i<argc-1){
                    Nombre_Articulo_Stock += " ";
                }
                bandera++;
            }
        }
        //Stock de un articulo por deposito
        if(strcmp(argv[1],"-stock")==0 && bandera!=argc){
            for (i=2; i<argc-1; i++){
                Nombre_Articulo_Deposito += argv[i];
                if(i<argc-2){
                    Nombre_Articulo_Deposito += " ";
                }
                cout<<endl<<bandera<<endl;
                cout<<Nombre_Articulo_Deposito<<endl;
            }
            Num_Stock_Deposito = stoi(argv[argc-1]);
            cout<<Num_Stock_Deposito<<endl;
        }


    ifstream archivo(ARCHIVO);
    string line, Nombre_Art, Cols;

    Lista<string> Lista_Min_Stock; //Listado de artículos que están en el mínimo de stock.
    Lista<string> Lista_Max_Stock; //Listado de artículos que igualan o superen determinada cantidad en stock.
    Lista<string> Lista_Min_Stock_Deposito; //Listado de artículos que están en el mínimo de stock y por depósito.
    HashMap<string, vector<int>> Hash_Articulos(2087, HashFunc); //Hashmap de los articulos y sus depositos.

    getline(archivo, line); //Descartamos el encabezado
    stringstream encabezado(line);

    while (getline(encabezado, Cols, ',')){ //Contamos la cantidad de columnas del archivo
        Cant_cols++;
    }

    while (getline(archivo, line)){
        stringstream files(line); //Convertimos la cadena a un objeto el cual un programa puede insertar o extraer datos
        string word;
        int num, Cant_art=0, pos=0;

        vector<int> Lista_Depositos(Cant_cols-3, 0);

        for (i = 0; i < Cant_cols; i++){
            getline(files, word, ',');

            if(i==2) Nombre_Art = word;

            if (i>2){
                if(!word.empty()){
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
                if(!word.empty() && stoi(word)<=Cant_Stock_MSD){
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
    //Total_Articulo Diferentes
    if(strcmp(argv[1],"-total_art_dif")==0) Total_Articulos_Diferentes(total_art_dif);
    //Total_Articulo
    if(strcmp(argv[1],"-total_art")==0) Total_Articulos(total_art);
    //Minimo Stock
    if(strcmp(argv[1],"-min_stock")==0 && argc==3) Min_Stock(Cant_Stock_MinS, Lista_Min_Stock);
    //Maximo Stock
    if(strcmp(argv[1],"-max_stock")==0) Max_Stock(Cant_Stock_MaxS, Lista_Max_Stock);
    //Minimo Stock por deposito
    if(strcmp(argv[1],"-min_stock")==0 && argc==4) Min_Stock_Deposito(Cant_Stock_MSD, Num_Deposito, Lista_Min_Stock_Deposito);
    //Stock de un articulo
    if(strcmp(argv[1],"-stock")==0 && bandera==argc) Stock_Nombre(Nombre_Articulo_Stock, Hash_Articulos);
    //Stock de un articulo por deposito
    if(strcmp(argv[1],"-stock")==0 && bandera!=argc) Stock_Deposito(Nombre_Articulo_Deposito, Num_Stock_Deposito, Hash_Articulos);

    clock_t begin; //Declacaramos el contador
    cout<<"\nComenzando a medir Tiempo" << endl;
    begin = clock(); //Empieza el contador

    clock_t end = clock();
    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
    cout<<"\nTardo elapsed_secs " << elapsed_secs << "\n" << std::endl;
    return 0;
}