#include<iostream>
#include<string>
#include <cstring>//pata strslen
#include<vector>
#include<map>
#include"Hash_table.hpp"
#include"Arbol_binario.hpp"
#include<unordered_map>

using namespace std;


int asignarValorLexicografico(const std::string& palabra) {
    std::unordered_map<char, int> valorLetra;

    // Asigna valores únicos a cada letra basándose en su posición lexicográfica
    for (char letra = 'a'; letra <= 'z'; ++letra) {
        valorLetra[letra] = letra - 'a' + 1;
    }

    int valorTotal = 0;

    // Calcula el valor total sumando los valores de cada letra en la palabra
    for (char letra : palabra) {
        letra = std::tolower(letra);
        valorTotal += valorLetra[letra];
    }

    return valorTotal;
}


struct contacto{
    int suma;
    char nombre[100]; 
    double telefono;
    vector<string>redes_sociales;
    // como hago el icono
    string direccion;
};
// hacer que el valor que tenga cada nombre sea su indice en el vector ordenado
int main(){
    
    Btree<int> mi_arbol;
    HashMap<int> hash;

   
    map<int,int>map1;  // que con la clave del vector ordenado buscar string asociado
    map<int,contacto>map2;
    int exit=1;
while(exit!=0){
    contacto c;
    string n="";
    int count=0;
    cout<<"Ingrese su nombre"<<endl;
   cin>>c.nombre;

    count=asignarValorLexicografico(c.nombre);

    cout<<count;
    c.suma=count;
    
    map2[count]=c;
    
    mi_arbol.insert(count);

cout<<"oprima 0 si quiere salir"<<endl;
    cin>>exit;
}

mi_arbol.inOrden();

vector<int>vec=mi_arbol.get_vector();

// tener cuidado si hay un valor repetido poner condicion(modificar su count para que sea unico y mandarlo al)
for (int i = 0; i < vec.size(); ++i) {
    map1[vec[i]] = i;
    }


for(int i = 0; i < vec.size(); ++i){
 auto item = map1.find(vec[i]);
 auto item2=map2.find(vec[i]);
    if (item != map1.end() and item2 != map2.end()) {
        hash.insert(item2->second.nombre,item->second);
    cout << "La llave existe  " << item->first << ";" << item->second << "}\n";
    cout<<"llave 2 "<<item2->first<<";"<<item2->second.nombre<<endl;
  } else {
    cout << "La llave no existe" << endl;
  }
}

//los nombres de la cola no estan ordenados
    
//podria no usar el hash y solo usar el vector ordenado

hash.display();
    //si hay una colision ( es decir que se agrega el mismo nombre, hay que hacer que el nodo donde esta el nombre repetido apunte a una lista de nombres repetidos)
//mi_arbol.display(); 
// el arbol está ordenado



return 0;
}
// para que la tabla hash este organizada, encontrar un valor hash que al aplicarle el modulo de lo necesario para quedar ordenado

>>>>>>> Stashed changes
