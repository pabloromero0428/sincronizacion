# Contrador preciso #

## Archivos disponibles ##

Para el desarrollo de esta parte del laboratorio se proporsionan los siguientes 3 archivos:
1. [counter.h](counter.h): Archivo cabecera del contador preciso (tomado del texto guia).
2. [counter.c](counter.c) Archivo fuente del contador preciso (tomado del texto guia).
3. [test_precise_counter.c](test_precise_counter.c): Archivo a completar con el fin de analizar el impacto en el desempeño al crear hilos que usen el contador simple (archivo a completar).
4. [Makefile](Makefile): Makefile para ahorar el proceso de compilación y enlazado.

Adicionalmente se recomienda que tenga los siguientes documentos a la mano:
1. [27. Interlude: Thread API](https://ceunican.github.io/aos/27.Interlude_Thread_API.pdf)
2. [29. Lock-based Concurrent Data Structures](https://ceunican.github.io/aos/29.Lock-based_Concurrent_Data_Structures.pdf)

## Procedimiento ##

### Paso 1 ###

Complete el archivo [test_precise_counter.c](test_precise_counter.c) de tal manera que permita ingresar desde linea de comandos los siguientes parametros:
1. Valor maximo del contador: ```MAXCNT```
2. Numero de hilos que seran lanzados: ```NUMTHREADS```
   
Segun lo anterior, la forma de pasar argumentos a la aplicación será la siguiente una vez este completamente terminada:  

```
./NOMBRE_EJECUTABLE <MAXCNT> <NUMTHREADS>
```

A continuación (para su comodidad) se muestra el esqueleto del código a completar ([test_precise_counter.c](test_precise_counter.c)) de modo que lo único que usted tendra que hacer es llenar el codigo siguiendo las instrucciones dadas en el esqueleto:

```C
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include "counter.h"

/* structs */
// code here (if you required it)...

/* start_routine header */
// code here...

/* Global variables */
// code here (if you required it)...

int main(int argc, char *argv[]) { 

    /* get the command's line parameters */
    // code here...


    /* Declaration of struct timeval variables */
    // code here...


    /* Initializing conter */
    // code here...


    /* Threads handlers */
    // code here...


    /* Thread creation */
    // code here...


    /* Time starts counting */
    // code here...


    /* Creating a Threads */
    // code here...
   

    /* Threads joins */
    // code here...


    /* Time stops counting here */
    // code here...


    /* get the end time */
    // code here...
    

    /* get the elapset time (end_time - start_time) */
    // code here...


    /* print the results (number threads employed, counter value, elasep time) */
    // code here...


    return 0;
}

/* start_routine definition */
// code here...





```

Compile y pruebe las veces que crea necesario hasta que tenga la certeza de que su programa hace lo que quiere (guiese de los que aprendió en el capitulo [Lock-based Concurrent Data Structures](http://pages.cs.wisc.edu/~remzi/OSTEP/threads-locks-usage.pdf) **en la sección de Concurrent Counters**. 

Para la compilación ejecute el comando ```make```:

```
make
```

### Paso 2 ###

Una vez tenga el programa listo, ejecutelo para los casos en los cuales se van a manejar 1, 2, 4, 8 y 16 hilos y pase como valor maximo del contador el valor de 10000000. Anote en una tabla los valores asociados al numero de hilos, el valor del contador logrado con estos y el tiempo gastado para cada caso.
