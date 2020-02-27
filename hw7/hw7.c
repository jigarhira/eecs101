#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 480
#define COLS 640

int main( int argc, char **argv )
{
	int		i;
	unsigned char	image[ROWS][COLS];
	FILE		*fp;

	if ( argc != 2 )
	{
	  fprintf( stderr, "usage: %s output-file\n", argv[0] );
	  exit( 1 );
	}







	if (!( fp = fopen( argv[1], "wb" ) ))
	{
	  fprintf( stderr, "error: could not open %s\n", argv[1] );
	  exit( 1 );
	}

	for ( i = 0 ; i < ROWS ; i++ )
	  fwrite( image[i], sizeof(char), COLS, fp );
	fclose( fp );

	return 0;
}

