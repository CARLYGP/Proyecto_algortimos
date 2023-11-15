#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include <string>
#include <iostream>
#include <stdexcept>

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
  unsigned size();
  
  void display();
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
        char firstChar = tolower(k[0]);

        // Check if the character is a lowercase letter
        if (firstChar >= 'a' && firstChar <= 'z') {
            hashVal = static_cast<unsigned>(firstChar - 'a');
        }
    }

    return hashVal % table_size;
}

template <typename VT>
Cell<VT>* HashMap<VT>::find_in_bucket(unsigned b, std::string k) { // se busca linealmente en el bucket 
  Cell<VT>* cursor = table[b]; // crear apuntador cursor que apunte al primer elemento del indice indicado de la tabla 
  while(cursor != nullptr){ // mientras el apuntador sea diferente de a null 
    if(cursor->key == k) // si el cursor encientra la llave y es == a k ingresada 
      return cursor; // return el cursor que es un apuntador 
    cursor = cursor->next;  // sino vaya al siguinte elemento de la tabla
  }
  return cursor; 
}

template <typename VT>
void HashMap<VT>::insert(std::string k, VT val) { // 
  
  // primero vamos a crear al nodo (bucket)
  unsigned bucket = hash(k);// bucket va a tener el indice hash
  Cell<VT>* c = find_in_bucket(bucket, k);
  if(c == nullptr){
    Cell<VT>* n = new Cell<VT>;
    n->key = k;
    n->val = val;
    if(table[bucket] == nullptr){
      n->next = nullptr;
    }else{
      n->next = table[bucket];
    }
    table[bucket] = n;
    _size++;
  }else{
    c->val = val;
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
