#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS		(int)480
#define COLUMNS		(int)640

void sobel(unsigned char in_image[ROWS][COLUMNS], int out_image[ROWS][COLUMNS], int operator[3][3], int *max);
void sgm(int ximage[ROWS][COLUMNS], int yimage[ROWS][COLUMNS], unsigned char out_image[ROWS][COLUMNS], int *max);
void binary(unsigned char sgmimage[ROWS][COLUMNS], unsigned char out_image[ROWS][COLUMNS], int threshold);
void clear( unsigned char image[][COLUMNS] );
void clear_int(int image[][COLUMNS]);
void header( int row, int col, unsigned char head[32] );

int main( int argc, char **argv )
{

	int				i, threshold[3], max[3];
	FILE			*fp;
	int				ximage[ROWS][COLUMNS], yimage[ROWS][COLUMNS];
	unsigned char	image[ROWS][COLUMNS], sgmimage[ROWS][COLUMNS], bimage[ROWS][COLUMNS], head[32];
	char			filename[6][50], ifilename[50];

	int sobel_x[3][3] = {
							{-1, 0, 1},
							{-2, 0, 2},
							{-1, 0, 1}
						};
	int sobel_y[3][3] = {
							{-1, -2, -1},
							{0, 0, 0},
							{1, 2, 1}
						};

	threshold[0] = 40;

	strcpy( filename[0], "image" );
	header ( ROWS, COLUMNS, head );


	printf( "Maximum of Gx, Gy, SGM\n" );

	clear_int( ximage );
	clear_int( yimage );
	clear(sgmimage);
	clear(bimage);

	/* Read in the image */
	strcpy( ifilename, filename[0] );
	if (( fp = fopen( strcat(ifilename, ".raw"), "rb" )) == NULL )
	{
		fprintf( stderr, "error: couldn't open %s\n", ifilename );
		exit( 1 );
	}			
	for ( i = 0; i < ROWS ; i++ )
		if ( fread( image[i], sizeof(char), COLUMNS, fp ) != COLUMNS )
		{
		fprintf( stderr, "error: couldn't read enough stuff\n" );
		exit( 1 );
		}
	fclose( fp );

	max[0] = 0; //maximum of Gx
	max[1] = 0; //maximum of Gy
	max[2] = 0; //maximum of SGM

	/* Compute Gx, Gy, SGM, find out the maximum and normalize*/
	
	/* Gx */
	sobel(image, ximage, sobel_x, &max[0]);
	
	/* Gy */
	sobel(image, yimage, sobel_y, &max[1]);

	/* SGM */
	sgm(ximage, yimage, sgmimage, &max[2]);

	/* Binary */
	binary(sgmimage, bimage, threshold[0]);


	/* Write SGM to a new image */
	strcpy( ifilename, filename[0] );
	if (!( fp = fopen( strcat( ifilename, "-s.ras" ), "wb" ) ))
	{
		fprintf( stderr, "error: could not open %s\n", ifilename );
		exit( 1 );
	}
	fwrite( head, 4, 8, fp );
	for ( i = 0 ; i < ROWS ; i++ ) fwrite( sgmimage[i], 1, COLUMNS, fp );	
	fclose( fp );
	
	/* Write the binary image to a new image */
	strcpy( ifilename, filename[0] );
	if (!( fp = fopen( strcat( ifilename, "-b.ras" ), "wb" ) ))
	{
		fprintf( stderr, "error: could not open %s\n", ifilename );
		exit( 1 );
	}
	fwrite( head, 4, 8, fp );
	for ( i = 0 ; i < ROWS ; i++ ) fwrite( bimage[i], 1, COLUMNS, fp );
	fclose( fp );

	printf( "%d %d %d\n", max[0], max[1], max[2] );


	return 0;
}


void sobel(unsigned char in_image[ROWS][COLUMNS], int out_image[ROWS][COLUMNS], int operator[3][3], int *max)
{
	/* iterate through the pixels excluding the border */
	int i, j, a, b, sobel_sum;	/* used for convolution */

	/* reset max */
	*max = 0;

	for (i = 1; i < (ROWS - 1); i++) {
		for (j = 1; j < (COLUMNS - 1); j++) {
			/* iterate through the operator */
			sobel_sum = 0;
			for (a = -1; a < 2; a++) {
				for (b = -1; b < 2; b++) {
					sobel_sum += in_image[i + a][j + b] * operator[a + 1][b + 1];
				}
			}
			/* save the raw value */
			out_image[i][j] = sobel_sum;
			
			/* find the maximum */
			if (sobel_sum > *max) {
				*max = sobel_sum;
			}
		}
	}

}


void sgm(int ximage[ROWS][COLUMNS], int yimage[ROWS][COLUMNS], unsigned char out_image[ROWS][COLUMNS], int *max)
{
	/* iterate through the pixels */
	int i, j;	/* used for convolution */
	float norm;	/* normalizing factor */
	int image_int[ROWS][COLUMNS];	/* int image used to save unnormalized image */

	/* reset max */
	*max = 0;

	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLUMNS; j++) {
			/* save the raw value of sgm */
			image_int[i][j] = (ximage[i][j] * ximage[i][j]) + (yimage[i][j] * yimage[i][j]);
			
			/* find the maximum */
			if (image_int[i][j] > *max) {
				*max = image_int[i][j];
			}
		}
	}

	/* calculate the normalizing factor */
	norm = 255.0 / (float)(*max);
	
	/* normalize the image */
	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLUMNS; j++) {
			out_image[i][j] = (unsigned char)(norm * (float)abs(image_int[i][j]));
		}
	}
}


void binary(unsigned char sgmimage[ROWS][COLUMNS], unsigned char out_image[ROWS][COLUMNS], int threshold)
{
	int i, j;

	/* iterate through the image pixels */
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLUMNS; j++)
		{
			/* compare pixel with threshold */
			if (sgmimage[i][j] > threshold)
			{
				out_image[i][j] = 255;
			}
			else
			{
				out_image[i][j] = 0;
			}
		}
	}
}


void clear( unsigned char image[][COLUMNS] )
{
	int	i,j;
	for ( i = 0 ; i < ROWS ; i++ )
		for ( j = 0 ; j < COLUMNS ; j++ ) image[i][j] = 0;
}

void clear_int(int image[][COLUMNS])
{
	int i, j;
	for (i = 0; i < ROWS; i ++)
	{
		for (j = 0; j < COLUMNS; j++)
		{
			image[i][j] = 0;
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
