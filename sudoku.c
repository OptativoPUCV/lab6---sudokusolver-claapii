#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct
{
   int sudo[9][9];
}Node;

Node* createNode()
{
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n)
{
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

int is_valid(Node* n)
{
   int i, j, k;
   for (i = 0; i < 9; i++) //Filas
      for(j = 0; j < 9; j++) //Columnas
         if(n->sudo[i][j] != 0) //Si hay un número
         {
            for (k = 0; k < 9; k++) //Revisa si el numero esta en la fila o columna
            {
               if (k != j && n->sudo[i][j] == n->sudo[i][k]) 
               { //Revisa si el numero esta en la columna
                  return 0;
               } 
               if (k != i && n->sudo[i][j] == n->sudo[k][j])
               { //Revisa si el número está en la fila
                  return 0;
               }
            }
            for (k = 0; k < 9; k++)
            {
               int p;
               for (p = 0 ; p < 9 ; p++)
               {
                  int m = 3 * (i/3) + (p/3);
                  int l = 3 * (j/3) + (p%3);
                  if (m != i && l != j && n->sudo[i][j] == n->sudo[m][j]) return 0;
                  if (m != i && l != j && n->sudo[i][j] == n->sudo[i][l]) return 0;
               }
            }
            
         }
   return 1;
}


List* get_adj_nodes(Node* n)
{
   List* list=createList();
   int i,j,k;
   for(i=0;i<9;i++) //Filas
      for(j=0;j<9;j++) //Columnas
         if(n->sudo[i][j]==0) //Si no hay un número
         {
            for(k=1;k<=9;k++) //Numeros 1-9
            {
               if (is_valid(n)) 
               {
                  Node* adj = (Node*) malloc(sizeof(Node));
                  adj = copy(n);
                  adj->sudo[i][j] = k;
                  if (is_valid(adj)) 
                     pushBack(list,adj); //Confirmamos si el nodo es valido
               }
            }      
         }
   
   return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
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