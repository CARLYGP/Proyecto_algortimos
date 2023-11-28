#ifndef HASHMAP_HPP
#define HASHMAP_HPP
#include<map>

#include <string>
#include <iostream>


const unsigned TABLE_SIZE = 26;

template <typename VT>
struct Cell {  
  VT val;
  std::string key;
  Cell<VT> *next;
};

template <typename VT>
class HashMap {
 private:
  Cell<VT> **table; // apuntador de apuntadores
  unsigned table_size;//tamaño para la tabla
  unsigned _size;  //contador de cuantos elementos hay en la tabla

  unsigned hash(std::string k);  // la funcion hash para hayar el indice que implementamos antes
  Cell<VT>* find_in_bucket(unsigned b,std::string k);  // operacion para buscar dentro de la lista anidada si la llave esta 
  
 public:
  HashMap();  // constructor que deberia inicializar la tabla, apartar espacio para el ** 
  //~HashMap(); // va a hacer uso de clear
  void insert(std::string k, VT val);
  void remove(std::string k);
  VT get(std::string k);
  void display();
  unsigned size(){
      return _size;
  }
};

//IMPLEMENTATION ---------------------------------------------

template <typename VT>
HashMap<VT>::HashMap() {
  table_size = TABLE_SIZE;
  _size = 0;
  table = new Cell<VT>*[table_size]; // crear un nuevo nodo y no entiendo muy bien el *[table_size]
  for(int i = 0; i < table_size; i++)
    table[i] = nullptr; // hacer que todos los buckets apunten a null
}



template <typename VT>
unsigned HashMap<VT>::hash(std::string k) {
    unsigned int hashVal = 0;

    if (!k.empty()) {
      // Se obtiene el primer carácter de la cadena k y lo convierte a minúsculas utilizando la función tolower.
        char firstChar = tolower(k[0]); 
        if (firstChar >= 'a' && firstChar <= 'z') { // verificar si la primera letra pertenece al conjunto de letras
            hashVal = firstChar - 'a'; // El hash va a ser el ascci de la letra menos el ascci de 'a'
        }
    }

    return hashVal % table_size; // modulo para asignar posicion correspondiente
}




template <typename VT>
Cell<VT>* HashMap<VT>::find_in_bucket(unsigned b, std::string k) { 
  Cell<VT>* cursor = table[b]; 
  while(cursor != nullptr){ 
    if(cursor->key == k)  
      return cursor; 
    cursor = cursor->next;  
  }
  return cursor; 
}

template <typename VT>
void HashMap<VT>::insert(std::string k, VT val) {
    unsigned bucket = hash(k);
    
    // Buscar si la clave ya existe 
    Cell<VT>* existingCell = find_in_bucket(bucket, k);
    
    if (existingCell == nullptr) {
        // La clave no existe
        Cell<VT>* newCell = new Cell<VT>;
        newCell->key = k;
        newCell->val = val;
        newCell->next = table[bucket];
        table[bucket] = newCell;
        _size++;
    } else {
        // La clave ya existe
        Cell<VT>* newCell = new Cell<VT>;
        newCell->key = k;
        newCell->val = val;
        newCell->next = nullptr;

       
        Cell<VT>* cursor = existingCell;
        while (cursor->next != nullptr) {
            cursor = cursor->next;
        }
        cursor->next = newCell;
        _size++;
    }
}



template <typename VT>
VT HashMap<VT>::get(std::string k) {
  unsigned bucket = hash(k);
  Cell<VT>* c = find_in_bucket(bucket, k);
  if(c == nullptr)
    throw std::runtime_error("get: key not found.");
  return c->val;
}

template <typename VT>
void HashMap<VT>::remove(std::string k) {
  unsigned bucket = hash(k);
  Cell<VT> *c = find_in_bucket(bucket, k);

  if(c == nullptr)
    throw std::runtime_error("remove: key not found.");
  if(table[bucket] == c){
    table[bucket] = c->next;
  }else{
    Cell<VT> *cursor = table[bucket];
    while(cursor->next != c)
      cursor = cursor->next;
    cursor->next = c->next;
  }
  delete c;
  _size--;
}

template <typename VT>
void HashMap<VT>::display() {
  Cell<VT> *cursor;
  for(int i = 0; i < table_size; i++){
    std::cout << i << ": ";
    cursor = table[i];
    while(cursor != nullptr){
      std::cout << "(" << cursor->key << ","
    << cursor->val << ") ";
      cursor = cursor->next;
    }
    std::cout << "\n";
  }
}

#endif
