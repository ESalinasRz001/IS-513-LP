# include  < stdio.h >
# include  < stdlib.h >
# include  < string.h >

int  main () {
	int c = 0 ;
	char EndStatus [ 100 ];

		ARCHIVO * archivo;
	caracter de char ;
	
	archivo = fopen ( " analizador.txt " , " r " );
	
	if (archivo == NULL ){
            printf ( " \n Error de apertura del archivo. \n \n " );
        }
        more{
            printf ( " \n El contenido del archivo de prueba es \n \n " );
            while ((caracter = fgetc (file))! = EOF){
		// printf ("% c", caracter);
		if (caracter> = ' a ' && caracter <= ' z ' ) {
			char status [] = " <Tkn_Min> " ;
			printf ( " % s " , status);
		}
		if (caracter> = ' A ' && caracter <= ' Z ' ) {
			char status [] = " <Tkn_May> " ;
			printf ( " % s " , status);
		}
		if (caracter> = ' 0 ' && caracter <= ' 9 ' ) {
			char status [] = " <Tkn_Num> " ;
			printf ( " % s " , status);
		}
		if (caracter == '  ' ) {
			char status [] = " <Tkn_Spc> " ;
			printf ( " % s " , status);
		}
}
    }
        fclose (file);
	
	
	return  0 ;
}