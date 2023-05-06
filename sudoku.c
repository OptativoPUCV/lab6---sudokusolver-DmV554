#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){

  for(int i=0; i<9; i++) {
    int*vectorCerosFilas = calloc(9, sizeof(int));
    int*vectorCerosColumnas = calloc(9, sizeof(int));
    for(int k=0; k<9; k++) {
      int num = n->sudo[i][k];
      int numColumna = n->sudo[k][i];
      
      if(num != 0) {
        if(vectorCerosFilas[num] == 0) {
          vectorCerosFilas[num] = 1;
        } else {
          return 0;
        }
      }
      if(numColumna != 0) {
        if(vectorCerosColumnas[numColumna] == 0) {
          vectorCerosColumnas[numColumna] = 1;
        } else {
          return 0;
        }
      }
  
    }
  }



  for (int l = 0; l < 9; l++) {
        int *vectorSubMatrices = calloc(9, sizeof(int));
        for (int p = 0; p < 9; p++) {
            int i = 3*(l/3) + (p/3);
            int j = 3*(l%3) + (p%3);

            int numSub = n->sudo[i][j];

          if(numSub != 0) {
            if(vectorSubMatrices[numSub] == 0) {
              vectorSubMatrices[numSub] = 1;
            } else {
              return 0;
            }
          }
            
        }
    }

  
  
    return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
  
    for(int i=0; i<9; i++) {
      Node*nuevoNodo = copy(n);
      int primerCasillaEsta = 0;
      for(int k=0; k<9; k++) {
        for(int j=0; j<9; j++) {
          if(nuevoNodo->sudo[k][j] == 0 && primerCasillaEsta == 0) {
            nuevoNodo->sudo[k][j] = i+1;
            primerCasillaEsta = 1;
          }
        }
      }
      if(primerCasillaEsta == 1 && is_valid(nuevoNodo)) {
        pushBack(list, nuevoNodo);
      }
      
    }
    return list;


  /*List* list=createList();
    
    for(int i=0; i<9; i++) {
      for(int k=0; k<9; k++) {
        if(n->sudo[i][k] == 0) {
           for(int j=0; j<9; j++) {
              Node*nuevoNodo = copy(n);
              nuevoNodo->sudo[i][k] = j+1;
              pushBack(list, nuevoNodo);
          }
        }
      }
    }
    return list;
}*/
  
}


int is_final(Node* n){
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            if(n->sudo[i][j] == 0){
                return 0;
            }
        }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont){
  /*Stack* S = createStack();
  push(S, initial);

  while(S != NULL) {
    Node*nodoCurrent = top(S);
    pop(S);

    if(is_final(nodoCurrent)) {
      return nodoCurrent;
    }

    List* nodosAdyacentes = get_adj_nodes(nodoCurrent);
    
        Node* NodoAd = first(nodosAdyacentes);
        while(NodoAd){
            push(S, NodoAd);
            NodoAd = next(nodosAdyacentes);
        }

        free(nodoCurrent);
    
  }
  
  return NULL;*/

   Stack* S = createStack();
    push(S, initial);
    
    while(S != NULL){
        Node* current = top(S);
        pop(S);
        (*cont)++;
        
        if(is_final(current)){
            clean(S);
            return current;
        }
        
        List* adj_nodes = get_adj_nodes(current);
        Node* adj_node = first(adj_nodes);
        while(adj_node){
            push(S, adj_node);
            adj_node = next(adj_nodes);
        }
        
        free(current);
        clean(adj_nodes);
    }
    
    clean(S);
    return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/