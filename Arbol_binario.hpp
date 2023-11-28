#ifndef _BTREE_HPP
#define _BTREE_HPP
#include <iostream>
#include <cmath>
#include <cstdlib>
#include<vector>
using namespace std;

template <typename T>
struct Node {
  T key;
  Node<T> *left;
  Node<T> *right;
  Node<T> *parent;
};


template <typename T>
class Btree {
private:
  
// crear nueva funcion que busque un nodo en el arbol y si llega a estar entonces en el vector donde se almacenan todos los nombres en orden buscar el nombre repetido y esa celda apuntar a una lista enlazada
  Node<T> *root;
  unsigned size; 
  vector<T>v1;
  void insert_node(Node<T>* &node, Node<T> *p, T k) ;
  void display_node(Node<T> *node, int level);
  Node<T>* find_node(Node<T> *node, T k);
  Node<T>* remove_node(Node<T>* &node, T k);
  Node<T>* successor(Node<T> *node);//nodo successor
  Node<T>* predecessor(Node<T> *node);//nodo predecessor
  void destroy_recursive(Node<T> *node);// destructor de la clase
  void inOrden(Node<T>* n);
  /**/
  
public:
  Btree();
  ~Btree();
  unsigned get_size();
  bool empty();
  void insert(T k);
  bool remove(T k);
  bool find(T k);
  void inOrden();
  void display();
  void mostrar_vector(){
    for (int i=0;i<v1.size();i++){
        cout<<v1[i]<<endl;
    }
  }

  vector<T> get_vector(){
    return v1;
  }

};

//IMPLEMENTATION---------------------
template <typename T>
Btree<T>::Btree() {
  root = nullptr;
  size = 0;
}

template <typename T>
Btree<T>::~Btree() {
  destroy_recursive(root);
}

template <typename T>
void Btree<T>::destroy_recursive(Node<T> *node) {
  if(node != nullptr){
    destroy_recursive(node->left);
    destroy_recursive(node->right);
    delete node;
  }
}

template <typename T>
unsigned Btree<T>::get_size() {
  return size;
}

template <typename T>
bool Btree<T>::empty() {
  return root == nullptr;
}

template <typename T>
void Btree<T>::insert_node(Node<T>* &node, Node<T> *p, T k) {
  if(node == nullptr){
    node = new Node<T>;
    node->key = k;
    node->left = nullptr;
    node->right = nullptr;
    node->parent = p;
    size++;
  }else{
    if(k <= node->key) // si es menor o igual el nuevo elemento, se agrega a la izq
      insert_node(node->left, node, k);
    else
      insert_node(node->right, node, k);
  }
}


template <typename T>
void Btree<T>::insert(T k) {
  insert_node(root, nullptr, k);
}



template <typename T>
Node<T>* Btree<T>::find_node(Node<T>* node, T k) {
  if(node == nullptr)
    return nullptr;
  else if(node->key == k)
    return node;
  else{
    if(node->key >= k)
      return find_node(node->left, k);
    else
      return find_node(node->right, k);
  }
}

template <typename T>
bool Btree<T>::find(T k) {
  return find_node(root, k) != nullptr;
}



template <typename T>
Node<T>* Btree<T>::successor(Node<T> *node) {
  if(node == maximum(root))
    return nullptr;
  if(node->right != nullptr)
    return minimum(node->right);
  Node<T> *p = node->parent;
  while(p != nullptr && node == p->right){
    node = p;
    p = node->parent;
  }
  return p;
}

template <typename T>
Node<T>* Btree<T>::predecessor(Node<T> *node) {
  if(node == minimum(root))
    return nullptr;
  if(node->left != nullptr)
    return maximum(node->left);
  Node<T> *p = node->parent;
  while(p != nullptr && node == p->left){ //mientras que sea hijo izquierdo
    node = p;
    p = node->parent;
  }
  return p;
}

template <typename T>
Node<T>* Btree<T>::remove_node(Node<T>* &node, T k) {
  Node<T> *target = find_node(node, k);
  if(target != nullptr){
    Node<T> *p = target->parent;
    if(target->left == nullptr && target->right == nullptr){
      std::cout << "Case: no children\n";
      if(target == p->left)
	p->left = nullptr;
      else
	p->right = nullptr;
      delete target;
      size--;
    }else if(target->left == nullptr){
      std::cout << "Case: right child\n";
      if(target == p->left)
	p->left = target->right;
      else
	p->right = target->right;
      delete target;
      size--;
    }else if(target->right == nullptr){
      std::cout << "Case: left child\n";
      if(target == p->left)
	p->left = target->left;
      else
	p->right = target->left;
      delete target;
      size--;
    }else{
      std::cout << "Case: two children\n";
      Node<T> *s = successor(target);
      target->key = s->key;
      p = remove_node(s,s->key);
    }
    return p;
  }
  return nullptr;
}

template <typename T>
bool Btree<T>::remove(T k) {
  return remove_node(root, k) != nullptr;
}



template <typename T>
void Btree<T>::inOrden(Node<T>* n) { // el recorrido es (left,root,right)
  if(n != nullptr){ 
    inOrden(n-> left);// recorrer por la parte izq
    v1.push_back(n->key); 
    inOrden(n-> right); // recorrer la parte derecha e imprimir
  }

}

template <typename T>
void Btree<T>::inOrden() {
    inOrden(root);
    std::cout << "\n";
}



template <typename T>
void Btree<T>::display_node(Node<T> *node, int level) {
  if(node != nullptr){
    level++;
    display_node(node->left, level);
    std::cout << node->key << "(" << level-1 << ") ";
    display_node(node->right, level);
  }
}


template <typename T>
void Btree<T>::display() {
  display_node(root, 0);
  std::cout << "\n";
}

#endif
