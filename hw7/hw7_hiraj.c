#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define ROWS 480
#define COLS 640

void header( int row, int col, unsigned char head[32] );
void generate(unsigned char image[ROWS][COLS], float r, float a, float m, float s0, float s1, float s2);

int main( int argc, char **argv )
{
	int		i;
	unsigned char	image1[ROWS][COLS],
					image2[ROWS][COLS],
					image3[ROWS][COLS],
					image4[ROWS][COLS],
					image5[ROWS][COLS],
					image6[ROWS][COLS],
					image7[ROWS][COLS],
					image8[ROWS][COLS],
					image9[ROWS][COLS],
					head[32];
	char			filename[50][50];
	FILE		*fp;

	header ( ROWS, COLS, head );

	strcpy(filename[0], "image1.ras");
	strcpy(filename[1], "image2.ras");
	strcpy(filename[2], "image3.ras");
	strcpy(filename[3], "image4.ras");
	strcpy(filename[4], "image5.ras");
	strcpy(filename[5], "image6.ras");
	strcpy(filename[6], "image7.ras");
	strcpy(filename[7], "image8.ras");
	strcpy(filename[8], "image9.ras");


	// generate images
	// r, a, m, s
	generate(image1, 50, 0.5, 1, 0, 0, 1);
	generate(image2, 50, 0.5, 1, (1.0/sqrt(3)), (1.0/sqrt(3)), (1.0/sqrt(3)));
	generate(image3, 50, 0.5, 1, 1, 0, 0.000000000001);
	generate(image4, 10, 0.5, 1, 0, 0, 1);
	generate(image5, 100, 0.5, 1, 0, 0, 1);
	generate(image6, 50, 0.1, 1, 0, 0, 1);
	generate(image7, 50, 1.0, 1, 0, 0, 1);
	generate(image8, 50, 0.5, 0.1, 0, 0, 1);
	generate(image9, 50, 0.5, 10000, 0, 0, 1);

	

	// write images to files
	if (!( fp = fopen( filename[0], "wb" ) ))
	{
	  fprintf( stderr, "error: could not open %s\n", filename[0] );
	  exit( 1 );
	}
	fwrite( head, 4, 8, fp );
	for ( i = 0 ; i < ROWS ; i++ )
	  fwrite( image1[i], sizeof(char), COLS, fp );
	fclose( fp );

	if (!( fp = fopen( filename[1], "wb" ) ))
	{
	  fprintf( stderr, "error: could not open %s\n", filename[1] );
	  exit( 1 );
	}
	fwrite( head, 4, 8, fp );
	for ( i = 0 ; i < ROWS ; i++ )
	  fwrite( image2[i], sizeof(char), COLS, fp );
	fclose( fp );

	if (!( fp = fopen( filename[2], "wb" ) ))
	{
	  fprintf( stderr, "error: could not open %s\n", filename[2] );
	  exit( 1 );
	}
	fwrite( head, 4, 8, fp );
	for ( i = 0 ; i < ROWS ; i++ )
	  fwrite( image3[i], sizeof(char), COLS, fp );
	fclose( fp );

	if (!( fp = fopen( filename[3], "wb" ) ))
	{
	  fprintf( stderr, "error: could not open %s\n", filename[3] );
	  exit( 1 );
	}
	fwrite( head, 4, 8, fp );
	for ( i = 0 ; i < ROWS ; i++ )
	  fwrite( image4[i], sizeof(char), COLS, fp );
	fclose( fp );

	if (!( fp = fopen( filename[4], "wb" ) ))
	{
	  fprintf( stderr, "error: could not open %s\n", filename[4] );
	  exit( 1 );
	}
	fwrite( head, 4, 8, fp );
	for ( i = 0 ; i < ROWS ; i++ )
	  fwrite( image5[i], sizeof(char), COLS, fp );
	fclose( fp );

	if (!( fp = fopen( filename[5], "wb" ) ))
	{
	  fprintf( stderr, "error: could not open %s\n", filename[5] );
	  exit( 1 );
	}
	fwrite( head, 4, 8, fp );
	for ( i = 0 ; i < ROWS ; i++ )
	  fwrite( image6[i], sizeof(char), COLS, fp );
	fclose( fp );

	if (!( fp = fopen( filename[6], "wb" ) ))
	{
	  fprintf( stderr, "error: could not open %s\n", filename[6] );
	  exit( 1 );
	}
	fwrite( head, 4, 8, fp );
	for ( i = 0 ; i < ROWS ; i++ )
	  fwrite( image7[i], sizeof(char), COLS, fp );
	fclose( fp );

	if (!( fp = fopen( filename[7], "wb" ) ))
	{
	  fprintf( stderr, "error: could not open %s\n", filename[7] );
	  exit( 1 );
	}
	fwrite( head, 4, 8, fp );
	for ( i = 0 ; i < ROWS ; i++ )
	  fwrite( image7[i], sizeof(char), COLS, fp );
	fclose( fp );

	if (!( fp = fopen( filename[8], "wb" ) ))
	{
	  fprintf( stderr, "error: could not open %s\n", filename[8] );
	  exit( 1 );
	}
	fwrite( head, 4, 8, fp );
	for ( i = 0 ; i < ROWS ; i++ )
	  fwrite( image9[i], sizeof(char), COLS, fp );
	fclose( fp );


	return 0;
}


void generate(unsigned char image[ROWS][COLS], float r, float a, float m, float s0, float s1, float s2)
{
	int i, j, x, y;
	float h_mag, L_l, L_s, alpha, L;
	float s[3], v[3], h[3], n[3];

	s[0] = s0;
	s[1] = s1;
	s[2] = s2;

	v[0] = 0;
	v[1] = 0;
	v[2] = 1;

	// generate h vector
	for (i = 0; i < 3; i++)
	{
		h[i] = s[i] * v[i];
	}

	// normalize the vector
	h_mag = sqrt(pow(h[0], 2) + pow(h[1], 2) + pow(h[2], 2));
	for (i = 0; i < 3; i++)
	{
		h[i] = h[i] / h_mag;
	}

	// iterate through the image
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			// change origin
			x = j - (COLS / 2);
			y = (ROWS / 2) - i;

			// check if the point is on the sphere
			if (pow(x, 2) + pow(y, 2) <= pow(r, 2))
			{
				// find the unit normal
				n[0] = x / r;
				n[1] = y / r;
				n[2] = (sqrt(pow(r, 2) - (pow(x, 2) + pow(y, 2)))) / r;

				// use dot product of two unit vectors to find angle between them
				L_l = (n[0] * s[0]) + (n[1] * s[1]) + (n[2] * s[2]);

				// ensure cos is in range
				if (L_l >= 0)
				{
					// use dot product to get alpha
					alpha = acosf((n[0] * h[0]) + (n[1] * h[1]) + (n[2] * h[2]));

					// calculate Ls
					L_s = exp((-1.0)*pow((alpha / m), 2));

					// calculate L
					L = (L_l * a) + (L_s * (1 - a));

					// remap L (0 -> 1) to pixel (0 -> 255)	
					if (L >= 0.0)
					{
						image[i][j] = L * 255;
					} else if (L > 1.0)
					{
						image[i][j] = 255;
					}
				}
			}
		}
	}

}

void header( int row, int col, unsigned char head[32] )
{
	int *p = (int *)head;
	char *ch;
	int num = row * col;

	/* Choose little-endian or big-endian header depending on the machine. Don't modify this */
	/* Little-endian for PC */
	
	*p = 0x956aa659;
	*(p + 3) = 0x08000000;
	*(p + 5) = 0x01000000;
	*(p + 6) = 0x0;
	*(p + 7) = 0xf8000000;

	ch = (char*)&col;
	head[7] = *ch;
	ch ++; 
	head[6] = *ch;
	ch ++;
	head[5] = *ch;
	ch ++;
	head[4] = *ch;

	ch = (char*)&row;
	head[11] = *ch;
	ch ++; 
	head[10] = *ch;
	ch ++;
	head[9] = *ch;
	ch ++;
	head[8] = *ch;
	
	ch = (char*)&num;
	head[19] = *ch;
	ch ++; 
	head[18] = *ch;
	ch ++;
	head[17] = *ch;
	ch ++;
	head[16] = *ch;
	

	/* Big-endian for unix */
	/*
	*p = 0x59a66a95;
	*(p + 1) = col;
	*(p + 2) = row;
	*(p + 3) = 0x8;
	*(p + 4) = num;
	*(p + 5) = 0x1;
	*(p + 6) = 0x0;
	*(p + 7) = 0xf8;
*/
}

