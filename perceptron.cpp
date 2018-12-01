/*Implementación del perceptrón*/

#include <stdio.h>
#include <stdlib.h>

#define NUM 2         
#define LIMIT 100     
#define SESSIONS 3000 

typedef struct { 
	float p[NUM]; 
} vector;

vector w, test[LIMIT], prueba[LIMIT];

// For RED xor 
//****************
float w11 = 0.5; bool turn_w11 = false;
float w12 = -0.5; bool turn_w12 = true;
float w13 = -0.5; bool turn_w13 = true;
float w14 = 0.5; bool turn_w14 = false;
float w21 = 0.5; bool turn_w21 = false;
float w22 = 0.5; bool turn_w22 = false;

float u1 = 0.5; bool turn_u1 = false;
float u2 = 0.5; bool turn_u2 = false;
float u3 = 0.5; bool turn_u3 = false;

//****************

int hits[LIMIT], total, pruebanum;

float bias = 0.5;

void print_vector( vector v )  {
	int i;
	for ( i = 0 ; i < NUM ; i++ ) printf("  %.4f ", v.p[i] );
	printf("\n");
}

float sum(  vector x) {
	int i;
	float s = 0.0;
	for ( i = 0 ; i < NUM ; i++ )  s += x.p[i];
	return s;
}


float scalar_mult(  vector x, vector y) {
	int i;
	float s = 0.0;
	for ( i = 0 ; i < NUM ; i++ )  
		s += ( x.p[i] * y.p[i] );
	return s;
}


// For RED xor 
//****************
float scalar_mult_params( 
	float x,
	float y,
	float first_w,
	float second_w,
	float check_u) {
		if ( (x*first_w) + (y*second_w) >= check_u ) return 1.0;
		else return 0.0;
}

float net_xor(  vector x ) {
	
	float y1 = scalar_mult_params(x.p[0], x.p[1], w11, w13, u1);
	float y2 = scalar_mult_params(x.p[0], x.p[1], w12, w14, u2);
	float y = scalar_mult_params(y1, y2, w21, w22, u3);
	
	return y;
}

void educate_net_xor() {
	vector x;
	int i, j, correct_result;
	float unit = 0.1;
	
	for ( i = 0 ; i < total ; i++ ) {
		x = test[i];
		correct_result = hits[i];
		
		if ( net_xor(x) != correct_result ) {
			w11 += (turn_w11) ? unit : -1 * unit;
			w12 += (turn_w12) ? unit : -1 * unit;
			w13 += (turn_w13) ? unit : -1 * unit;
			w14 += (turn_w14) ? unit : -1 * unit;
			w21 += (turn_w21) ? unit : -1 * unit;
			w22 += (turn_w22) ? unit : -1 * unit;
			
			u1 += (turn_u1) ? unit : -1 * unit;;
			u2 += (turn_u2) ? unit : -1 * unit;
			u3 += (turn_u3) ? unit : -1 * unit;
			
			if( w11 < 0) turn_w11 = true;
			else if( w11 > 0.5) turn_w11 = false;
			if( w12 > 0) turn_w12 = false;
			else if( w12 < -0.5) turn_w12 = true;
			if( w13 > 0) turn_w13 = false;
			else if( w13 < -0.5) turn_w13 = true;
			if( w14 < 0) turn_w14 = true;
			else if( w14 > 0.5) turn_w14 = false;
			if( w21 < 0) turn_w21 = true;
			else if( w21 > 0.5) turn_w21 = false;
			if( w22 < 0) turn_w22 = true;
			else if( w22 > 0.5) turn_w22 = false;
			
			if( u1 < 0) turn_u1 = true;
			else if( u1 > 0.5) turn_u1 = false;
			if( u2 < 0) turn_u2 = true;
			else if( u2 > 0.5) turn_u2 = false;
			if( u3 < 0) turn_u3 = true;
			else if( u3 > 0.5) turn_u3 = false;
			
		}
	}
}

int check_performance_xor() {
	vector x;
	int j, count=0;
	for ( j = 0 ; j < total ; j++ ) {
		x = test[j];
		if ( net_xor(x) == hits[j] )
			count++;
		}
	return count;
}

//****************


float net(  vector x ) {
	return( (scalar_mult( x, w ) + bias > 0.0));
}


void educate_net() {
	vector x;
	int i, j, correct_result;
	
	for ( i = 0 ; i < total ; i++ ) {
		x = test[i];
		correct_result = hits[i];
		
		if ( net(x) != correct_result )
			if ( correct_result == 0 ) {
				for (j=0;j<NUM;j++) 
					w.p[j] -= x.p[j];
				bias -= 1.0;
			}
			else {
			
				for (j=0;j<NUM;j++)
					w.p[j] += x.p[j];
				bias += 1.0;
			}
	}
}



int check_performance() {
	vector x;
	int j, count=0;
	for ( j = 0 ; j < total ; j++ ) {
		x = test[j];
		if ( net(x) == hits[j] )
			count++;
		}
	return count;
}

int checker(char input[],char check[]) {
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

int get_data_xor() {
	const char* FileName = "datos_xor.dat";
	
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
		test[ total ].p[0] = x;
		test[ total ].p[1] = y;
		
		if(x == y){
			hits[ total ] = 0;
		} else {
			hits[ total ] = 1;
		}
			
		total++;
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
	else if( checker(operador, "xor") )
		get_data_xor();
	else{
		printf("\n\nNo se reconoce Operador.");
		exit(1);
	}
	
	if( checker(operador, "xor") ){
		while ( ((right=check_performance_xor()) != total ) && ( i++ < SESSIONS ) )
			educate_net_xor();
		if ( check_performance_xor() != total){
			printf("fallo Xor");
			exit(1);
		}
	}else{
		while ( ((right=check_performance()) != total ) && ( i++ < SESSIONS ) )
			educate_net();
		if ( check_performance() != total){
			printf("fallo !");
			exit(1);
		}
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



