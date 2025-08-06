//PROGRAMA PARA TEORÍA DE CONJUNTOS, CAPAZ DE RECONOCER UN SEMIGRUPO EN UN CONJUNTO DADO
//MEDIANTE UN CUADRO DE DOBLE ENTRADA, SE PUEDE INCLUSO OBTENER LOS RESULTADOS DE OPERADORES NO COMUNES
//TENER EN CUENTA QUE UN SEMIGRUPO REQUIRE DOS COSAS: QUE CUMPLA LA LEY DE COMPOSICIÓN INTERNA
//(ES DECIR, QUE TODAS LAS OPERACIONES SE ENCUENTREN DENTRO DEL CONJUNTO) Y QUE CUMPLA LA PROPIEDAD ASOCIATIVA
//EL PROGRAMA INDICARÁ ADEMÁS SI ALGUNA DE ESTAS DOS LEYES NO SE CUMPLE
//Creado por @CarlosHoo7

#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <string>
using namespace std;

vector <int> ObtenerConjunto();
vector<vector<int>> GenerarMatriz(vector<int> conjunto, bool* comprobar);
bool ComprobarAsociatividad(vector<vector<int>> matriz, vector<int> conjunto);
map <pair <int, int>, int> MapearCoordenadasMatriz(vector<vector<int>> matriz, vector<int> conjunto); 
bool EsInt(string cadena);
bool CompararCadenas (string cadena1, string cadena2);

int main (){
    //ORDEN PRINCIPAL DE LAS FUNCIONES
    vector<int> conjunto = ObtenerConjunto();
    bool compInterna;
    vector<vector<int>> matriz = GenerarMatriz(conjunto, &compInterna);
    cout<<endl<<endl;
    if(compInterna){
        if (ComprobarAsociatividad(matriz, conjunto)){
            cout<<"El conjunto insertado SI es un semigrupo"<<endl;
        } else{
            cout<<"El conjunto insertado NO es un semigrupo (No cumple con la asociatividad)"<<endl;
        }
    } else {
        cout<<"El conjunto insertado NO es un semigrupo (No cumple con la ley de composicion interna)"<<endl;
    }
    cout<<endl<<"Creado por: @CarlosHoo7"<<endl;
    system("pause");
}
vector<int> ObtenerConjunto(){
    vector <int> conjunto;
    bool listo = false;
    while (!listo){
        system("cls");
        cout<<"Bienvenido al verificador de Semigrupos"<<endl<<
        "Este programa es capaz de revisar en un cuadro de doble entrada, si un conjunto es un semigrupo o no."<<endl<<
        "Un cuadro de doble entrada, es una manera de representar una operacion binaria."<<endl<<
        "Creado por: CarlosHoo"<<endl<<endl;
        int elemento;
        string input;
        bool existe = false;
        cout<<"Ingrese un numero que desee agregar al conjunto (No se puede agregar elementos repetidos)"<<endl;
        cout<<"Elementos del conjunto actual:"<<endl<<"{ ";
        for (int elem: conjunto){
            cout<<elem;
            if(elem != conjunto.back()){
                cout<<", ";
            }
        }
        cout<<" }"<<endl<<endl;
        cout<<"Una vez termine de agregar todos los elementos del conjunto, escriba \"listo\"" <<endl;
        cin>>input;
        if(EsInt(input)){
            elemento = stoi(input);
        } else if (!EsInt(input)){
            if (CompararCadenas(input, "listo")){
                listo = true;
            }
        }
        for (int elem : conjunto){
            if (elem == elemento){
                existe = true;
            }
        }
        if (!existe){
            conjunto.push_back(elemento);
        }   
    }
    return conjunto;
}
vector<vector<int>> GenerarMatriz(vector<int> conjunto, bool* comprobar){
    bool listo = false;
    bool yaAsignado= false;
    bool compInterna = false;
    vector<vector <int>> matriz (conjunto.size());
    int dimension = matriz.size();
    //CREANDO MATRIZ
    for (int i = 0; i < dimension; i++){
        matriz[i] = vector<int>(dimension);
    }
    int indiceFilas = 0, indiceColumnas = 0;
    int opcion;
    
    while (!listo){
        system("cls");
        cout<<"Que operador desea usar?:"<<endl<<"\t(0) Suma"<<endl<<"\t(1) Multiplicacion"<<endl<<"\t(2) Otro operador"<<endl;
        cout<<"En el caso de no tener operador comun (suma o multiplicacion), puedes rellenar el cuadro con los resultados"<<endl<<
        "manualmente."<<endl;
        cin>>opcion;
        switch (opcion){
            //SUMA
            case 0:
                for(int i = 0; i < dimension; i++){
                    for(int j = 0; j < dimension; j++){
                        int operacion = conjunto[i] + conjunto[j];
                        matriz[i][j] = operacion;
                        for (int elem :conjunto){
                            if(operacion == elem){
                                compInterna = true;
                            } else {compInterna = false;}
                        }
                    }
                }
                yaAsignado= true;
                listo = true;
                break;
            //MULTIPLICACION
            case 1:
                for(int i = 0; i < dimension; i++){
                    for(int j = 0; j < dimension; j++){
                        int operacion = conjunto[i] * conjunto[j];
                        matriz[i][j] = operacion;
                        for (int elem :conjunto){
                            if(operacion== elem){
                                compInterna = true;
                            } else {compInterna = false;}
                        }
                    }
                } 
                yaAsignado=true;
                listo = true;
                break;
            case 2:
                listo = true;
                break;
            default:
                break;
            }
    }
    listo = false;
    while (!listo){
        system("cls");
        cout<<"CUADRO DE DOBLE ENTRADA DEL CONJUNTO DADO"<<endl;
        cout<<"\n";
        cout<<"\n";
        //COLUMNAS
        cout<<"#\t";
        for (int elem : conjunto){
            cout<<elem<<"\t";
        }
        //FILAS
        cout<<endl;
        int indiceMostrar = 0;
        for (int elem : conjunto){
            cout<<elem;
            for (int subelem : matriz[indiceMostrar]){
                cout<<"\t"<<subelem;
            }
            cout<<endl;
            indiceMostrar++;
        }
        if(!yaAsignado){
            cout<<endl<<"Complete el cuadro con los resultados al operar cada elemento entre si"<<endl;
            string input;
            cin>>input;
            
            if(EsInt(input)){
                matriz[indiceFilas][indiceColumnas] = stoi(input);
                for (int elem :conjunto){
                    if(matriz[indiceFilas][indiceColumnas] == elem){
                        compInterna = true;
                    }
                }
                indiceColumnas++;
                if (indiceColumnas == dimension){
                    indiceColumnas = 0;
                    indiceFilas++;
                }
            }    
            if(indiceFilas == dimension){
                yaAsignado=true;
            }
        } else { listo = true;}
    }
    *comprobar = compInterna;
    return matriz;
}
bool ComprobarAsociatividad(vector<vector<int>> matriz, vector<int> conjunto){
    map <pair<int,int>, int> coordenadas = MapearCoordenadasMatriz(matriz, conjunto);
    int dimension = conjunto.size();
    //Centro es igual a la mitad de la dimension, inclusivamente
    int centro = dimension % 2 == 0? dimension /2 : ((dimension-1) / 2) + 1;
    int resto = dimension - centro;
    int tanda1, tanda2;
    if(resto > 1){
        tanda1 = resto % 2 == 0? resto /2 : ((resto-1)/2) + 1;
    } else {
        tanda1 = 1;
    }
    tanda2 = resto-tanda1;
    for(int fila = 0; fila < dimension; fila++){
        //OPERACION LINEAL
        int resultadoLineal;
            resultadoLineal = conjunto[fila];
            for (int i = 0; i < dimension; i++){
                if (conjunto [i] != conjunto [fila]){
                    resultadoLineal = coordenadas[make_pair(resultadoLineal, conjunto[i])];
                }
            }
        //OPERACION CENTRICA
        int resultadoCentrica;
            vector<int> conjuntoSinFila;
            int filaCentrica, columnaCentrica;
            for (int elem : conjunto){
                if (elem != conjunto[fila]){
                    conjuntoSinFila.push_back(elem);
                }
            }
            filaCentrica = conjuntoSinFila[tanda1-1];
            for (int i = 1; i < centro; i++){
                int indice = tanda1-1+i;
                filaCentrica = coordenadas[make_pair(filaCentrica, conjuntoSinFila[indice])];
            }
            columnaCentrica = conjunto[fila];
            //Sumar los primeros numeros antes del parentesis central
            for (int i = 0; i < tanda1-1; i++){
                columnaCentrica = coordenadas[make_pair(columnaCentrica, conjuntoSinFila[i])];
            }
            //Sumar los numeros despues del parentesis central
            for (int i = 0; i < tanda2; i++){
                int indice = dimension + i - tanda2 - 1 ;
                columnaCentrica = coordenadas[make_pair(columnaCentrica, conjuntoSinFila[indice])];
            }
            resultadoCentrica = coordenadas[make_pair(filaCentrica,columnaCentrica)];
        //VERIFICAR ASOCIATIVIDAD
        if(resultadoLineal != resultadoCentrica){
            return false;
        }
    }
    
    return true;
}
map <pair<int, int>, int> MapearCoordenadasMatriz(vector<vector<int>> matriz, vector<int> conjunto){
    map <pair <int, int>, int> coordenadas;
    int dimension = conjunto.size();
    for (int fila= 0; fila < dimension; fila++){
        for (int columna = 0; columna < dimension; columna++){
            coordenadas[make_pair(conjunto[fila], conjunto[columna])] = matriz[fila][columna];
        }
    }
    return coordenadas;
}
bool EsInt(string cadena){
    int cantidad = cadena.length();
    for (int i = 0; i < cantidad; i++){
        if (isdigit(cadena[i]) == false){
            return false;
        }
    }
    return true;
}
bool CompararCadenas(string cadena1, string cadena2){
    if (cadena1.length() != cadena2.length()){
        return false;
    } else {
        int cantidad = cadena2.length();
        for (int i = 0; i < cantidad; i++){
            if(tolower(cadena1[i]) != tolower(cadena2[i])){
                return false;
            }
        }
    }
    return true;
}
