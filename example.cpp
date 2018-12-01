int get_data_2() {
	char* FileName = "datos_nand.dat";
	
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
		printf("Error");
		exit(20);
	}
	
	for ( i = 0 ; i < posnum ; i++ ){
		fscanf( fd, "%f %f", &x, &y);
		test[ total ].p[0] = x ;
		test[ total ].p[1] = y ;
		hits[ total++ ] = 0;  
	}
	
	fscanf( fd, "%d", &negnum); {
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

