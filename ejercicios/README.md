# Manejo de estructuras que usan locks #

## Fuentes de consulta ##
1. Material de clase (Videos y diapostivas).
2. Texto guía [**Operating Systems: Three Easy Pieces**](http://pages.cs.wisc.edu/~remzi/OSTEP/). Para desarrollar este laboratorio se recomienda tener a la mano el capítulo [Lock-based Concurrent Data Structures](http://pages.cs.wisc.edu/~remzi/OSTEP/threads-locks-usage.pdf)

## Ejercicios ##

1. Consulte el uso de la función ```gettimeofday``` para medir el tiempo de ejecución de un programa
   * ¿Cómo se utiliza esta función (muestre un ejemplo)? 
```
Se utiliza para medir de forma precisa el tiempo que tarda en ejecutarse cierta operación,
que  se encuentra en la librería "sys/time.h". Esta función ofrece teóricamente una precisión de
 microsegundos (0,001 milisegundos). Su sintaxis es la siguiente:

int gettimeofday (struct timeval *tp, NULL);

Siendo timeval un registro con 2 campos: int tv_sec, int tv_usec, que indican los segundos y microsegundos, 
respectivamente.



```
![alt tag](https://github.com/pabloromero0428/sincronizacion/blob/master/PARTE%201%20Soluci%C3%B3n/P1/Punto1.png)

   * ¿Cuál es el intervalo de tiempo más corto que se puede medir con esta función?
   
```
EL intervalo más corto que se puede medir es: 1 Microsegundo.
```
2. Consulte cuantas CPUs hay disponibles en el sistema que usted está utilizando. (Pista use el comando lscpu)

![alt tag](https://github.com/pabloromero0428/sincronizacion/blob/master/PARTE%201%20Soluci%C3%B3n/P2/Cpus.png)

3. Desarrolle un programa que utilice un contador concurrente simple. Mida cuánto tiempo lleva incrementar el contador muchas veces a medida que aumenta el número de hilos (1, 2, 4, 8 y 16). Para tal fin, siga las instrucciones que aparecen en el directorio [preciso](./preciso). Una vez complete los pasos continue con el tercer punto.
4. Desarrolle una versión del contador aproximado (*sloppy counter*) y mida su desempeño a medida que se varía el número de hilos. En este caso, solo maneje un umbral de S = 1024 variando el número de hilos (1, 2, 4, 8 y 16). Las intrucciones para ello se encuentran en el directorio [aproximado](./aproximado).
5. Grafique los resultados obtenidos de las pruebas recopiladas (en las tablas) para el **número de hilos .vs. el tiempo (en segundos)**, estas siguen la tendencia de la figura **29.5** del libro (la cual se muestra a continuación):

![fig_performance](fig_performance.jpg)

   * ¿Los valores que usted obtuvo siguen una tendencia como la que se muestra en el texto guía (mostrada anteriormente)?

```
Con respecto al contador preciso los valores de arrojados no se asemejan debido a que es secuencial por ende entre mas hilos tenga para llegar al valor maximo del contador va disminuir considerablemente 
```

![alt tag](https://github.com/pabloromero0428/sincronizacion/blob/master/PARTE%201%20Soluci%C3%B3n/P5/Contadorpreciso.png)
   
```
Pero en el contador aproximado se nota que aunque no se comporta totalmente a la figura 29.5 hay una pequeña similitud en que
 los datos aumenta todo esto se debe al humbra con el cual se ejecuta el codigo ademas de la cantidad de hilos.
```
![alt tag](https://github.com/pabloromero0428/sincronizacion/blob/master/PARTE%201%20Soluci%C3%B3n/P5/Aproximado.png)
  
   
   * ¿Cuántas CPUs hay disponibles en el sistema que usted está utilizando?  
   
   ```
   La pc con el cual se hizo el laboratorio cuenta con 4cpu
   ```
   
   * ¿Este número afecta de alguna manera sus mediciones?
   
  ```
   De alguna manera el número de CPUs afecta las mediciones pues dependiendo a estas encontonces podriamos obtener mejores o 
menores tiempos y aunque el libro guia lo manejar de forma muy similar, las condiciones de la maquina y otros factores pueden 
no dar los datos como para hacer una comparacion muy especifica y detallada de lo que pasa
   ```

6. Mejore el archivo [test_aproximate_mejorado_counter.c](./aproximado_mejorado/test_aproximate_mejorado_counter.c) (el cual se encuentra en el directorio [aproximado_mejorado](./aproximado_mejorado)) de tal modo que, además de permitir modificar el numero de hilos y el valor máximo del contador a emplear, permita modificar también el umbral o factor de apromación (S), para esto se puede basar en el ejercicio 3. De este modo los parametros serán:
   * Umbral: ```APPROXIMATION_FACTOR```
   * Valor máximo del contador: ```MAXCNT```
   * Número de hilos que serán lanzados: ```NUMTHREADS```
   
Según lo anterior, la forma de pasar argumentos a la aplicación será la siguiente, una vez esté completamente terminada:  

```
./NOMBRE_EJECUTABLE <APPROXIMATION_FACTOR> <MAXCNT> <NUMTHREADS>
```

Luego, ejecute varias veces la aplicación dejando constante el valor máximo del contador en 10000000 y el número de hilos en 4, pero cambiando el valor del umbral a los siguientes valores: 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 y 1024. ¿La gráfica sigue una tendencia similar a la mostrada en la figura **29.6** del texto guía (la cual se muestra a continuación)?

![fig_S](fig_S.jpg)


![alt tag](https://github.com/pabloromero0428/sincronizacion/blob/master/PARTE%201%20Soluci%C3%B3n/P6/AproximadoMG.png)
![alt tag](https://github.com/pabloromero0428/sincronizacion/blob/master/PARTE%201%20Soluci%C3%B3n/P6/aproximadomejorado.png)

```
Como se muestra en la figura anterior respecto a los datos que el algoritmo arroja la tendencia es muy similar a la de la 
figura 29.6 pero el ultimo dato que es arrojado se sale de la tendencia. 

```
