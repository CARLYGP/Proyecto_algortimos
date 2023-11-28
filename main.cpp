#include<iostream>
#include<string>
#include <cstring>//pata strslen
#include<map>
#include<fstream> // para hacer copia de seguridad en archivo
#include"Hash_table.hpp"
#include"Arbol_binario.hpp"
#include<vector>
// el arbol sirve como historial de nombres
using namespace std;
struct contacto{
  
    string nombre;
    string telefono;
    string redes_sociales;
    string Instagram;
    string Github; 
    string direccion;
    string calle;
    string numero;
    string indicativo; //(-)
    int veces_repetido;
    int veces_visitado; //# de veces que se ha visitado en cada ejecución un perfil
};
// hacer que el valor que tenga cada nombre sea su indice en el vector ordenado
int main(){
    
    map<string,contacto>datos_no_rep; //si solo se necesita el nombre para acceder al contacto
    map<string,contacto>datos_rep2;  // se necesita el numero porque el nombre esta repetido
    map<string,int>datos_rep; // mirar cuantas veces esta repetido el nombre
    Btree<string> mi_arbol;
    HashMap<string> hash;
    int exit=1;
    int opciones;
    int salir=1;

while(salir==1){
    cout<<"--------------------------Libreta de contactos---------------------------"<<endl;
    cout<<"1:Agregar contacto"<<endl;
     cout<<"2:Buscar contacto"<<endl;
     cout<<"3:Eliminar contacto"<<endl;
     cout<<"4:Mostrar lista completa de contactos"<<endl;
     cout<<"5:Mostrar contactos ordenados por letra"<<endl;
     cout<<"6:Mostrar cantidad de contactos en la lista"<<endl;
     cout<<"7:Mostar lista de contactos con su frecuencia de busqueda"<<endl;
     cout<< "8:Realizar copia de seguridad en archivo de texto"<<endl;
     cout<<"9:Salir"<<endl; //opciones    
    cin>>opciones;
   // si oprime buscar contacto, mirar si quiere buscar por letra
    if (opciones==1){
        
    contacto c;
        
    string nombre="";
    int count=0;
    cout<<"Ingrese su nombre"<<endl;
   cin>>c.nombre;
   cout<<"Ingrese su telefono";
   cin>>c.telefono;
   cout<<"Ingrese su direccion cada dato de su direccion: "<<endl;// hacer una estructura que guarde calle, #, - 
   cout<<"Ingrese calle"<<endl;
   cin>>c.calle;
   cout<<"Ingrese numero(#)"<<endl;
   cin>>c.numero;
   cout<<"Ingrese (-)"<<endl;
   cin>>c.indicativo;
   c.direccion="calle" + c.calle + "#"+ c.numero+"-"+ c.indicativo; // concatenacion de direccion
   cout<<"Usuario de Instagram"<<endl;
   cin>> c.Instagram;
   cout<<"Usuario de Github"<<endl;
   cin>>c.Github;
  
   c.veces_repetido=0;
    if (mi_arbol.find(c.nombre)==1){
        c.veces_repetido+=1;
    }
    c.veces_visitado=0;
   mi_arbol.insert(c.nombre);
    hash.insert(c.nombre,c.telefono); 
    // asignacion de nombre con contacto para que pueda ser variable el valor
    
    datos_no_rep[c.nombre]=c;
    datos_rep2[c.telefono]=c; 
    datos_rep[c.nombre]=c.veces_repetido;
    
    }  if (opciones ==2){
        string num;
        string n;
        cout<<"Ingrese nombre que quiere buscar"<<endl;
        cin>>n;
        
        auto item = datos_rep.find(n);
        if (item != datos_rep.end()) {

        if( item->second>=1){
            auto item = datos_rep2.find(num);
                 if (item != datos_rep2.end()) {
                     item->second.veces_visitado+=1; // si se ingresa un nombre repetido se aumenta el atributo veces_visitado
                    
                    }
                    
              cout<<"Se necesita informacion adicional, ingrese el numero del contacto"<<endl; // cuando el nombre es repetido
              cin>>num;
              int opc1;
              cout<<"Perfecto, quiere saber info de " << n <<" sobre: (1:direccion)(2:redes sociales)(3:salir)"<<endl;
              cin>>opc1;
              // se va a mostrar la informacion de los contactos repetidos
              if(opc1==1){
                 auto item = datos_rep2.find(num);
                 if (item != datos_rep2.end()) {
                 cout<<item->second.direccion<<endl;
                 
                    }
                }else if(opc1==2){
                    auto item = datos_rep2.find(num);
                         if (item != datos_rep2.end()) {
                            cout<<"Instagram: "<<item->second.Instagram<<" Github: " <<item->second.Github <<endl;
                        }
                }else if(opc1==3){
                    break;
                }
                }else{
                    auto item = datos_no_rep.find(n);
                         if (item != datos_no_rep.end()) {
                             item->second.veces_visitado+=1;
                        }
                    int cerrar=1;
                    while (cerrar==1){
                    int opc;
                    cout<<"Perfecto, quiere saber info de "<< n <<" sobre: (1:telefono)(2:direccion)(3:redes sociales)(4:salir)"<<endl;
                    cin>>opc;
                           
                    if(opc==1){
                        auto item = datos_no_rep.find(n);
                         if (item != datos_no_rep.end()) {
                            cout<<item->second.telefono<<endl;
                        }

                    }else if(opc==2){
                        auto item = datos_no_rep.find(n);
                         if (item != datos_no_rep.end()) {
                            cout<<item->second.direccion<<endl;
                        }
                    }else if(opc==3){
                        auto item = datos_no_rep.find(n);
                         if (item != datos_no_rep.end()) {
                            cout<<"Instagram: "<<item->second.Instagram<<" Github: " <<item->second.Github <<endl;
                        }
                        
                    }
                    
                    else if(opc==4){
                        cerrar=0;
                       
                    }

                }
                }
            } 
        }if (opciones==3){
        string cont;
        cout<<"Ingrese el nombre del contacto que quiere eliminar"<<endl;
        cin>>cont;
        //---------------- caso repetidos------------------
        auto item = datos_rep.find(cont);
        if (item != datos_rep.end()) {
            if( item->second>=1){
                string num2;
                cout<<"se necesita informacion adicional, ingrese el numero del contacto"<<endl; // cuando el nombre es repetido
                cin>>num2;
                 auto item = datos_rep2.find(num2); // se busca en el mapa de repetidos el numero que se asocia al contacto que buscamos
                 if (item != datos_rep2.end()) {
                    hash.remove(item->second.nombre);
                        }
                    
            }else{
                 hash.remove(cont);
            }
            //--------------- caso no repetidos----------------
        }
    } if(opciones==4){
         mi_arbol.display(); //historial de contactos 
    }if (opciones==5){
        hash.display();
    }if (opciones==6){
        cout<<"Hay "<<hash.size()<<" Contactos en la libreta disponibles"<<endl;
    }if(opciones==7){
        mi_arbol.inOrden();
        vector<string>vector2=mi_arbol.get_vector();
            for (int i=0;i<vector2.size();i++){
               auto item = datos_no_rep.find(vector2[i]);
                         if (item != datos_no_rep.end()) {
                            cout<<"{"<<"Nombre: "<<vector2[i]<<","<<"frecuencia de visitas del perfil: "<<item->second.veces_visitado<<"}"<<endl;
                        }
       
                }
            }if (opciones==8){
          mi_arbol.inOrden();
         vector<string>vector=mi_arbol.get_vector();
         ofstream archivo;
        archivo.open("Copia_de_seguridad.txt",ios::out);// abrir archivo
            if(archivo.fail()){
                cout<<"no se pudo abrir el archivo";
            }
            for (int i=0;i<vector.size();i++){
              // tambien hay que revisar si esta repedido :)
                auto item = datos_no_rep.find(vector[i]);
                         if (item != datos_no_rep.end()) {
                            archivo<<"{"<<vector[i]<<" , "<<"Telefono: "<<item->second.telefono<<" , "<<"Direccion: "<<item->second.direccion<<","<<"Instagram: "<<item->second.Instagram<<","<<"Github: "<<item->second.Github<<","<<"# de veces que se visitó en perfil: "<<item->second.veces_visitado<<"}"<<endl;
                        } 
                }
            
            archivo.close();
    }

    else if (opciones==9){
        salir =0;
    }else if(opciones>8 or opciones<1){  // por si el usuario ingresa un comando invalido
        salir=0;
    }
}
return 0;
}
