/*
This is a simple C++ program.
Call this file Sample.cpp.
*/

#include <iostream>
#include <stdlib.h> /* srand, rand */
#include <math.h>       /* pow */
#include <assert.h>     /* assert */
#include <fstream>  /* ofstream */

using namespace std;

#define MAX_CITIES 100  //Numero maximo de ciudades o nodos definidos con anterioridad
#define MAX_DIST 30000   //Distancia maxima entre ciudades
#define MAX_TOUR (MAX_CITIES * MAX_DIST) //Distancia maxima que una hormiga puede recorrer
#define MAX_ANTS 100   //Numero maximo de hormigas. Se define igual a la cantidad de nodos (cada nodo se inicializa con una hormiga)



//definicion de los parametros de convergencia a la solucion
#define ALPHA 1.0 //es el parametro de la metaheuristica que representa la importancia del camino
#define BETA 5.0 //es el parametro de la metaheuristica que representa la visibilidad del camino. Visibilidad es la inversa de la distancia entre dos nodos
#define RHO 0.5 //evaporacion rate
#define QVAL 100 //constante que define la cantidad de feromona que se deposita en cada camino
#define MAX_TOURS 50 //numero maximo de viajes que puede realizar una hormiga
#define MAX_TIME (MAX_TOURS * MAX_CITIES) //tiempo maximo de calculo definido en caso que no se encuentre la solucion 
#define INIT_PHER (1.0/MAX_CITIES) //valor de inicializacion de cada camino con feromona



//definicion de estructuras ciudad y hormiga
struct cityType{
int x,y; //coordenadas de la ciudad
};
cityType cities[MAX_CITIES];//definicion del arreglo de miembros del tipo ciudad 


struct antType{
int curCity; //indice de identificacion de la ciudad actual
int nextCity; //indice de identificacion de la proxima ciudad
int pathIndex; //identificacion del camino de la hormiga
int tabu[MAX_CITIES]; //arreglo de las ciudades que ya visito la hormiga
int path[MAX_CITIES]; //arreglo de los recorridos que ya realizo la hormiga 
double tourLength; //distacia que la hormiga recorrio en su camino
};
antType ants[MAX_ANTS];//definicion del arreglo de miembros del tipo hormiga (cada nodo se inicializa con una hormiga)



 
double dist[MAX_CITIES][MAX_CITIES]; //arreglo que registra las distancias entre cada nodo o ciudad
double phero[MAX_CITIES][MAX_CITIES]; //arreglo que registra la feromona entre cada nodo o ciudad
double best=(double)MAX_TOUR; //registra el mejor camino despues de cada iteracion
int bestIndex;







//************************************************definicion de funciones*******

void init() //inicializacion de las hormigas y caminos 
{
    int from,to,ant;
 
    //creacion de las ciudades o nodos
 
    for(from = 0; from < MAX_CITIES; from++)
    {
        //randomly place cities-----------------------------cambiar para que se pueda cargar la lista de ciudades
 
        cities[from].x = rand()%MAX_DIST;
 
        cities[from].y = rand()%MAX_DIST;
        //printf("\n %d %d",cities[from].x, cities[from].y);
        for(to=0;to<MAX_CITIES;to++)
        {
            dist[from][to] = 0.0; // inicializacion de las distancias
            phero[from][to] = INIT_PHER; // inicializacion de la feromona
        }
    }
 
    //calculo de la distancias
 
    for(from = 0; from < MAX_CITIES; from++)
    {
        for( to =0; to < MAX_CITIES; to++)
        {
            if(to!=from && dist[from][to]==0.0)
            {
                int xd = pow( abs(cities[from].x - cities[to].x), 2);
                int yd = pow( abs(cities[from].y - cities[to].y), 2);
 
                dist[from][to] = sqrt(xd + yd);
                dist[to][from] = dist[from][to];
 
            }
        }
    }
 
    //creacion de la hormigas, se inicializa una hormiga en cada nodo
 
    to = 0;
    for( ant = 0; ant < MAX_ANTS; ant++)
    {
        if(to == MAX_CITIES)
            to=0;
 
        ants[ant].curCity = to++;
 
        for(from = 0; from < MAX_CITIES; from++)
        {
            ants[ant].tabu[from] = 0; //0 significa que la ciudad no ha sido visitada todavia 
            ants[ant].path[from] = -1; 
        }
 
        ants[ant].pathIndex = 1;
        ants[ant].path[0] = ants[ant].curCity;
        ants[ant].nextCity = -1;
        ants[ant].tourLength = 0;
 
        //lse carga la primera ciudad en la lista tabu
 
        ants[ant].tabu[ants[ant].curCity] =1; //1 significa que la ciudad ya fue visitada
 
    }
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//reinicializacion de las hormiga y redistribucion
void restartAnts()
{
    int ant,i,to=0;
 
    for(ant = 0; ant<MAX_ANTS; ant++)
    {
        if(ants[ant].tourLength < best) // se registra la longitud del mejor camino
        {
            best = ants[ant].tourLength;
            bestIndex = ant;
        }
 
        ants[ant].nextCity = -1;  //se reinicializa la estructura de hormigas 
        ants[ant].tourLength = 0.0;
 
        for(i=0;i<MAX_CITIES;i++)
        {
            ants[ant].tabu[i] = 0;
            ants[ant].path[i] = -1;
        }
 
        if(to == MAX_CITIES)
            to=0;
 
        ants[ant].curCity = to++;
 
        ants[ant].pathIndex = 1;
        ants[ant].path[0] = ants[ant].curCity;
 
        ants[ant].tabu[ants[ant].curCity] = 1;
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double antProduct(int from, int to)//para el calculo de la ecuacion 4.1
{
    return(( pow( phero[from][to], ALPHA) * pow( (1.0/ dist[from][to]), BETA))); 
}
 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int selectNextCity( int ant ) //esta funcion selecciona la proxima ciudad para visitar. La proxima ciudad se selecciona deacuerdo a la probabilidad de la ecuacion 4.1
{
    int from, to;
    double denom = 0.0; //se inicializa el denominador de la ecuacion 4.1 para luego hacer la sumatoria de productos
 
    from=ants[ant].curCity; //selecciona proxima ciudad

 /* calculo del denominador*/
    for(to=0;to<MAX_CITIES;to++)     
    {      
	 if(ants[ant].tabu[to] == 0)       
         {        
	 denom += antProduct( from, to ); 
         }  
    }  
   
    assert(denom != 0.0);      
    do  
     {      
     	double p; //probabilidad ecuacion 4.1      
     	to++;              
     	if(to >= MAX_CITIES)
     	to=0;
     	if(ants[ant].tabu[to] == 0)
     	{
     		p = antProduct(from,to)/denom;
 
 		//printf("\n%lf %lf", (double)rand()/RAND_MAX,p);
            	double x = ((double)rand()/RAND_MAX);    //ver si da error cccccccccccccccccccccccc
            	if(x < p)
            	{
                	//printf("%lf %lf Yo!",p,x);
 
                	break;
               }
        }
    }while(1);
 
    return to;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//esta funcion mueve las hormigas de la ciudad actual a la proxima deacuerdo a la pobabilidad ecuacion 4.1
int simulateAnts()
{
    int k;
    int moving = 0; //retorna 0 cuando ya se completaron todas las ciudades
 
    for(k=0; k<MAX_ANTS; k++)
    {
        //se verifica que la hormiga todavia tiene ciudades para visitar
        if( ants[k].pathIndex < MAX_CITIES )        
        {         
        	ants[k].nextCity = selectNextCity(k);           
                ants[k].tabu[ants[k].nextCity] = 1;             
		ants[k].path[ants[k].pathIndex++] = ants[k].nextCity;                       
		ants[k].tourLength += dist[ants[k].curCity][ants[k].nextCity];                      
 
 		
 		//al final si se llga al termino del ultimo nodo se suma a la longitud total la distancia hasta la ciudad de inicio.
               if(ants[k].pathIndex == MAX_CITIES)
               {
                	ants[k].tourLength += dist[ants[k].path[MAX_CITIES -1]][ants[k].path[0]];
               }
 
               ants[k].curCity = ants[k].nextCity;
               moving++;
 
        }
    }
 
    return moving;
}
 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//esta funcion actualiza la feromona cuando finaliza el recorrido y tambien maneja la evaporacion 
 
void updateTrails()
{
    int from,to,i,ant;
 
    //evaporacion de feromona
 
    for(from=0; from<MAX_CITIES;from++)
    {
        for(to=0;to<MAX_CITIES;to++)
        {
            if(from!=to)
            {
                phero[from][to] *=( 1.0 - RHO);
 
                if(phero[from][to]<0.0)
                {
                    phero[from][to] = INIT_PHER;
                }
            }
        }
    }
 
    //suma nueva feromona al camino
 
    for(ant=0;ant<MAX_ANTS;ant++)
    {
        for(i=0;i<MAX_CITIES;i++)
        {
            if( i < MAX_CITIES-1 )
            {
                from = ants[ant].path[i];
                to = ants[ant].path[i+1];
            }
            else
            {
                from = ants[ant].path[i];
                to = ants[ant].path[0];
            }
 
            phero[from][to] += (QVAL/ ants[ant].tourLength);
            phero[to][from] = phero[from][to];
 
        }
    }
 
    for (from=0; from < MAX_CITIES;from++)
    {
        for( to=0; to<MAX_CITIES; to++)
        {
            phero[from][to] *= RHO;
        }
    }
 
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void emitDataFile(int bestIndex)
{
    ofstream f1;
    f1.open("Data.txt");
    antType antBest;
    antBest = ants[bestIndex];
    //f1<<antBest.curCity<<" "<<antBest.tourLength<<"\n";
    int i;
    for(i=0;i<MAX_CITIES;i++)
    {
        f1<<antBest.path[i]<<" ";
    }
 
    f1.close();
 
    f1.open("city_data.txt");
    for(i=0;i<MAX_CITIES;i++)
    {
        f1<<cities[i].x<<" "<<cities[i].y<<"\n";
    }
    f1.close();
 
}



////////////////////prog proncipal/////////////////////////////////////////////////


int main()
{
    int curTime = 0;
    cout<<"MaxTime="<<MAX_TIME;
 
    srand(time(NULL));
 
    init();
 
    while( curTime++ < MAX_TIME)
    {
        if( simulateAnts() == 0)
        {
            updateTrails();
 
            if(curTime != MAX_TIME)
                restartAnts();
 
            cout<<"\nTime is "<<curTime<<"("<<best<<")";
 
        }
    }
 
    cout<<"\nBest tour = "<<best<<endl;
 
    emitDataFile(bestIndex);
 
    return 0;
}

