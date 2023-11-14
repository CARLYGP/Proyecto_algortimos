#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include"Hash_table.hpp"
#include"Arbol_binario.hpp"

using namespace std;



struct contacto{
    string nombre; 
    double telefono;
    vector<string>redes_sociales;
    // como hago el icono
    string direccion;
};

int main(){
    queue<contacto> cola_de_contactos;
    Btree<int> mi_arbol;
    HashMap<int> hash;
    
    int exit=1;
while(exit!=0){
    contacto c;
    string n="";
    int count=0;
    cout<<"Ingrese su nombre"<<endl;
   cin>>c.nombre;
    
    for (int i=0;i<c.nombre.size();i++){
        count+=tolower(c.nombre[i]); // Tolower nos permite que si el usuario metió algun digito en mayuscula convertirlo a minuscula

    }//cout econtrará una llave unica para cada nombre
    
    cout<<count;
    
    cola_de_contactos.push(c);
    mi_arbol.insert(count);

cout<<"oprima 0 si quiere salir"<<endl;
    cin>>exit;
}

mi_arbol.inOrden();

vector<int>vec=mi_arbol.get_vector();


for(int i = vec.size() - 1; i >= 0; --i){ //recorrer el vector al reves ya que el inorder quedó al reves entonces podriamos mirar usar una cola tambien
     hash.insert(cola_de_contactos.front().nombre,vec[i]);
     cola_de_contactos.pop(); 
     // hacer una copia para no perder los contactos
}

//podria no usar el hash y solo usar el vector ordenado

hash.display();
    //si hay una colision ( es decir que se agrega el mismo nombre, hay que hacer que el nodo donde esta el nombre repetido apunte a una lista de nombres repetidos)
mi_arbol.display(); // el arbol está ordenado

return 0;
}
// para que la tabla hash este organizada, encontrar un valor hash que al aplicarle el modulo de lo necesario para quedar ordenado