#include <ctime>
#include <sstream>
#include <fstream>
#include <iostream>
#define ARCHIVO "C:\\Users\\Joaquin\\Desktop\\Proyecto_Programacion3-ArgEc\\Inventariado_Fisico.csv"
#include <C:\Users\Joaquin\Desktop\Proyecto_Programacion3-ArgEc\Lista\Lista.h>
#include <C:\Users\Joaquin\Desktop\Proyecto_Programacion3-ArgEc\Cola\Cola.h>
#include <C:\Users\Joaquin\Desktop\Proyecto_Programacion3-ArgEc\HashMap\HashMap.h>
#include <C:\Users\Joaquin\Desktop\Proyecto_Programacion3-ArgEc\Pila\Pila.h>
#include <C:\Users\Joaquin\Desktop\Proyecto_Programacion3-ArgEc\Arbol\ArbolBinario.h>

using namespace std;

void min_stock(int n){}
void min_stock(int n, int deposito){}
void stock(string nombre_articulo){}
void max_stock(int n){}


int main(){
    ifstream archivo(ARCHIVO);
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
}








/*clock_t begin;
    cout << "Comenzando a medir Tiempo\n" << endl;

    begin = clock();
    /*
     * Insertar código a medir tiempo aquí

    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    cout << "Tardo elapsed_secs" << elapsed_secs << "\n" << std::endl;*/