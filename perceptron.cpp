/*Implementación del perceptrón*/

#include <stdio.h>
#include <stdlib.h>

#define NUM 2         
#define LIMIT 100     
#define SESSIONS 3000 

typedef struct
{
  float p[NUM];
} vector;

vector w, test[LIMIT], prueba[LIMIT];
int hits[LIMIT], total, pruebanum;

float bias = 0.5;


void print_vector( vector v ) 
{
  int i;
  for ( i = 0 ; i < NUM ; i++ ) printf("  %.4f ", v.p[i] );
  printf("\n");
}


float sum(  vector x)
{
  int i;
  float s = 0.0;
  for ( i = 0 ; i < NUM ; i++ )  s += x.p[i];
  return s;
}


float scalar_mult(  vector x, vector y)
{
  int i;
  float s = 0.0;
  for ( i = 0 ; i < NUM ; i++ )  s += ( x.p[i] * y.p[i] );
  return s;
}



float net(  vector x )
{
  return( (scalar_mult( x, w ) + bias > 0.0));
}


void educate_net()
{
  vector x;
  int i, j, correct_result;

  for ( i = 0 ; i < total ; i++ )
    {
      x = test[i];
      correct_result = hits[i];
      
      if ( net(x) != correct_result )
        if ( correct_result == 0 )
          {
            
            for (j=0;j<NUM;j++) w.p[j] -= x.p[j];
            bias -= 1.0;
          }
        else
          {
         
            for (j=0;j<NUM;j++) w.p[j] += x.p[j];
            bias += 1.0;
          }
    }
}



int check_performance()
{
  vector x;
  int j, count=0;
  for ( j = 0 ; j < total ; j++ )
    {
      x = test[j];
      if ( net(x) == hits[j] )
        count++;
    }
  return count;
}

int checker(char input[],char check[])
{
    int i,result=1;
    for(i=0; input[i]!='\0' || check[i]!='\0'; i++) {
        if(input[i] != check[i]) {
            result=0;
            break;
        }
    }
    return result;
}

int get_data_or() {
	const char* FileName = "datos.dat";
	
	FILE *fd;
	int i, posnum, negnum;
	float x,y;
	
	if ( (fd = fopen(FileName,"r")) == NULL ) {
	  printf ("no-input-file");
	  exit(10);
	}

	total = 0;
	fscanf( fd, "%d", &posnum);
	if (posnum > LIMIT) {
		printf("Error");
		exit(20);
	}
	for ( i = 0 ; i < posnum ; i++ ) {
		fscanf( fd, "%f %f", &x, &y);
		test[ total ].p[0] = x ;
		test[ total ].p[1] = y ;
		hits[ total++ ] = 1;  
	}

	fscanf( fd, "%d", &negnum);
	if ((negnum+total) > LIMIT) {
		printf("Error");
		exit(21);
	}
	for ( i = 0 ; i < negnum ; i++ ) {
		fscanf( fd, "%f %f", &x, &y);
		test[ total ].p[0] = x ;
		test[ total ].p[1] = y ;
		hits[ total++ ] = 0; 
	}
  
	return (0) ;
}

int get_data_nor() {
	const char* FileName = "datos.dat";
	
	FILE *fd;
	int i, posnum, negnum;
	float x,y;
	
	if ( (fd = fopen(FileName,"r")) == NULL ) {
	  printf ("no-input-file");
	  exit(10);
	}

	total = 0;
    
	fscanf( fd, "%d", &posnum);
	if (posnum > LIMIT) {
		printf("Error");
		exit(20);
	}
	for ( i = 0 ; i < posnum ; i++ ) {
		fscanf( fd, "%f %f", &x, &y);
		test[ total ].p[0] = x ;
		test[ total ].p[1] = y ;
		hits[ total++ ] = 0;  
	}
	
	fscanf( fd, "%d", &negnum);
	if ((negnum+total) > LIMIT) {
		printf("Error");
		exit(21);
	}
	for ( i = 0 ; i < negnum ; i++ ) {
		fscanf( fd, "%f %f", &x, &y);
		test[ total ].p[0] = x ;
		test[ total ].p[1] = y ;
		hits[ total++ ] = 1; 
	}

	return (0) ;
}

int get_data_nand() {
	const char* FileName = "datos_nand.dat";
	
	FILE *fd;
	int i, posnum, negnum;
	float x,y;
	
	if ( (fd = fopen(FileName,"r")) == NULL ){
		printf ("no-input-file");
		exit(10);
	}
	
	total = 0;
	
	fscanf( fd, "%d", &posnum);
	if (posnum > LIMIT) {
		printf("Error a");
		exit(20);
	}
	
	for ( i = 0 ; i < posnum ; i++ ){
		fscanf( fd, "%f %f", &x, &y);
		test[ total ].p[0] = x ;
		test[ total ].p[1] = y ;
		hits[ total++ ] = 0;  
	}
	
	fscanf( fd, "%d", &negnum); {
		printf("Error b");
		exit(21);
	}
	
	for ( i = 0 ; i < negnum ; i++ ) {
		fscanf( fd, "%f %f", &x, &y);
		test[ total ].p[0] = x ;
		test[ total ].p[1] = y ;
		hits[ total++ ] = 1; 
	}
	
	return (0) ;
}



main() {
	char operador [80];
	printf ("Ingrese Operador (or, nand, ..): ");
	scanf("%79s", operador);  
	
	int i=0,right;
	vector x;
	
	for ( i = 0 ; i < NUM ; i++ ) w.p[i] = 0.0;
	
	if( checker(operador, "or") )
		get_data_or();
	else if( checker(operador, "nand") )
		get_data_nand();
	else if( checker(operador, "nor") )
		get_data_nor(); 
	else{
		printf("\n\nNo se reconoce Operador.");
		exit(1);
	}
	
	while ( ((right=check_performance()) != total ) && ( i++ < SESSIONS ) )
		educate_net();
	  
	if ( check_performance() != total){
		printf("fallo");
		exit(1);
	}
	
	printf("Datos de entrenamiento\n");	
	
	for(i=0;i<total;i++) {
		print_vector(test[i]);
		printf("%f\n",net(test[i]));
	}
	
	/*aqui se ponen los datos para probar la red*/
	
	x.p[0]=0.0;
	x.p[1]=0.0;
	
	printf("Datos de prueba\n");
	
	print_vector(x);
	printf("%f\n",net(x));
	
	getchar(); getchar();
}



