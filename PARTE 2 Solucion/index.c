#include <sys/types.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

// basic node structure
typedef struct BookNode
{
  int id;
  char name[15];
  int num_pages;
  int pub_year;
  struct BookNode *next;
  int isAvailable;
} BookNode;

// basic list structure (one used per list)
typedef struct BookList
{
  BookNode *head;
  pthread_mutex_t lock;
} BookList;

typedef struct
{
  int correctReservationCount; 
  int errorReservationCount;
  BookList *L;
} argsThread;

void List_Init(BookList *L)
{
  L->head = NULL;
  pthread_mutex_init(&L->lock, NULL);
}

int List_Insert(BookList *L, int id, char name[], int num_pages, int pub_year)
{
  pthread_mutex_lock(&L->lock);
  BookNode *new = malloc(sizeof(BookNode));
  if (new == NULL)
  {
    perror("malloc");
    pthread_mutex_unlock(&L->lock);
    return -1; // fail
  }
  new->id = id;
  strcpy(new->name, name);
  new->num_pages = num_pages;
  new->pub_year = pub_year;
  new->isAvailable = 1;
  new->next = L->head;
  L->head = new;
  pthread_mutex_unlock(&L->lock);
  return 0; // success
}

int reserve(BookList *L, int id)
{
  /*
    -1: No esta el libro con el id indicado
    0: Reserva exitosa
    1: El libro se encuentra reservado
  */
  pthread_mutex_lock(&L->lock);
  BookNode *curr = L->head;
  while (curr)
  {
    if (curr->id == id)
    {
      if (curr->isAvailable)
      {
        curr->isAvailable = 0;
        pthread_mutex_unlock(&L->lock);
        return 0;
      }
      pthread_mutex_unlock(&L->lock);
      return 1;
    }
    curr = curr->next;
  }
  pthread_mutex_unlock(&L->lock);
  return -1;
}

void* attentionOffice(void *param){
  srand (time(NULL));
  argsThread *args = (argsThread *) param;
  for (int i = 0; i < 1000; i++)
  {
    int bookId = rand() % 10000;
    int statusReserve = reserve(args->L, bookId);
    if (statusReserve == 0)
    {
      args->correctReservationCount++;
    }else{
      args->errorReservationCount++;
    }
  }
  return NULL;
}

int main(int argc, char *argv[])
{
  printf(":: Iniciando sistema de bibliotecas :: \n\n");
  //Etapa 1
  BookList books;
  List_Init(&books);
  for (int i = 0; i < 10000; i++)
  {
    char nameBook[15] = "book_";
    char prefixNameBook[4];
    sprintf(prefixNameBook, "%i", i%1000);
    strcat(nameBook, prefixNameBook);
    List_Insert(&books, i, nameBook, 100, 1996);
  }
  //Etapa 2
  clock_t startTime = clock();
  double allTime;

  pthread_t threads[4];
  argsThread argThreads[4];
  for (int i = 0; i < 4; i++)
  {
    argThreads[i] = (argsThread){0, 0, &books};
    pthread_create(&threads[i], NULL, attentionOffice, &argThreads[i]);
  }
  int successfulReservationsCount = 0, faildReservationCout = 0;
  for (int i = 0; i < 4; i++)
  {
    pthread_join(threads[i], NULL);
    successfulReservationsCount += argThreads[i].correctReservationCount;
    faildReservationCout += argThreads[i].errorReservationCount;
    printf("Office %i has finished its  workload, successful loans %i, failed loans %i \n", i, argThreads[i].correctReservationCount, argThreads[i].errorReservationCount);
  }
  clock_t endTime = clock();
  allTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
  
  printf("Simulation done! execution time: %f s \n", allTime);
  printf("Total successful loans %i, total failed loans %i \n", successfulReservationsCount, faildReservationCout);
  
  BookNode *curr = books.head;
  int x = 0;
  while (curr)
  {
    if (curr->isAvailable)
    {
      x++;
    }
    curr = curr->next;
  }
  printf("Number of remaining available books %i  \n", x);
}