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
   int i, j;
   //Filas
   for (i = 0; i < 9; i++){
      int arrayF[10] = {0};
      for(j = 0; j < 9; j++){
         if(n->sudo[i][j] == 0) continue;
         if(n->sudo[i][j] < 1 || n->sudo[i][j] > 9) return 0;
         if(arrayF[n->sudo[i][j]] != 0) return 0;
         arrayF[n->sudo[i][j]] = 1;
      }
   }

   //Columnas
   for (i = 0; i < 9; i++){
      int arrayC[10] = {0};
      for(j = 0; j < 9; j++){
         if(n->sudo[j][i] == 0) continue;
         if(n->sudo[j][i] < 1 || n->sudo[j][i] > 9) return 0;
         if(arrayC[n->sudo[j][i]] != 0) return 0;
         arrayC[n->sudo[j][i]] = 1;
      }
   }

   //Revisar Matrices
   for(int k = 0 ; k < 9 ; k++)
   {
      int arrayS[10] = {0};
      for (int p = 0 ; p < 9 ; p++)
      {
         i = 3*(k/3) + (p/3);
         j = 3*(k%3) + (p%3);
         if (n->sudo[i][j] == 0) continue;
         if (n->sudo[i][j] < 1 || n->sudo[i][j] > 9) return 0;
         if (arrayS[n->sudo[i][j]] != 0) return 0;
         arrayS[n->sudo[i][j]] = 1;
      }
   }
            
   return 1;
}


List* get_adj_nodes(Node* n)
{
   List* list=createList();
   int i,j,k;
   int firstC = 0;
   for(i=0;i<9;i++) //Filas
      for(j=0;j<9;j++) //Columnas
         if(n->sudo[i][j]==0 && firstC == 0) //Si no hay un número
         {
            firstC = 1;
            for(k=1;k<10;k++) //Numeros 1-9
            {
               Node* adj = copy(n);
               adj->sudo[i][j] = k;
               if (is_valid(adj) && firstC == 1) pushBack(list,adj); //Confirmamos si el nodo es valido
            }      
         }
   
   return list;
}


int is_final(Node* n)
{
   if (n == NULL) return 0;
   int i,j;
   for(i = 0 ; i < 9 ; i++) //Filas
      for (j = 0 ; j < 9 ; j++) //Columnas
      {
         if (n->sudo[i][j] == 0) //Si hay un espacio vacio
            return 0;
      }
   return 1;
}

Node* DFS(Node* initial, int* cont)
{
   Stack *pila = createStack();
   cont = 0;
   push(pila, initial);
   while (!is_empty(pila))
   {
      Node* n = (Node *)top(pila);
      pop(pila);
      if (is_final(n)) return n;
      List* adj = get_adj_nodes(n);
      Node* aux = first(adj);
      while (aux != NULL)
      {
         push(pila, aux);
         aux = next(adj);
         if (is_final(aux)) cont++;
      }
      free(n);
   }

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