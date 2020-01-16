#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS   		 		 128
#define COLS				 128
#define LOGICAL_X_MIN			-4.0
#define LOGICAL_X_MAX			 4.0
#define LOGICAL_Y_MIN			-4.0
#define LOGICAL_Y_MAX			 4.0

void clear(unsigned char image[][COLS]);
int plot_logical_point(float x, float y, unsigned char image[][COLS]);
int plot_physical_point(int x, int y, unsigned char image[][COLS]);
int in_range(int x, int y);
void header(int row, int col, unsigned char head[32]);/*write header for the output images, do not modify this*/
void generate_orthogonal(float x0, float y0, float z0, float a, float b, float c, float fprime, float t_start, float t_end, unsigned char image[][COLS]);
void generate_perspective(float x0, float y0, float z0, float a, float b, float c, float fprime, float t_start, float t_end, unsigned char image[][COLS]);
void write_image(unsigned char image[][COLS], char filename[]);


int main(int argc, char **argv)
{
	unsigned char	image[ROWS][COLS];

	/* question 1d */
	clear(image);
	generate_orthogonal(0.5, -1.0, 0.0, 0.0, 1.0, -1.0, 1.0, 0.0, 100.0, image);
	write_image(image, "question_1d_orthogonal.ras");
	clear(image);
	generate_perspective(0.5, -1.0, 0.0, 0.0, 1.0, -1.0, 1.0, 0.0, 100.0, image);
	write_image(image, "question_1d_perspective.ras");

	/* question 2b */
	clear(image);
	generate_orthogonal(0.5, -1, -1, 1, 1, 0, 1, 0.01, 10000, image);
	generate_orthogonal(-0.5, -1, -1, 1, 1, 0, 1, 0.01, 10000, image);
	write_image(image, "question_2b_orthogonal_-1.ras");
	clear(image);
	generate_perspective(0.5, -1, -1, 1, 1, 0, 1, 0.01, 10000, image);
	generate_perspective(-0.5, -1, -1, 1, 1, 0, 1, 0.01, 10000, image);
	write_image(image, "question_2b_perspective_-1.ras");
	
	clear(image);
	generate_orthogonal(0.5, -1, -2, 1, 1, 0, 1, 0.01, 10000, image);
	generate_orthogonal(-0.5, -1, -2, 1, 1, 0, 1, 0.01, 10000, image);
	write_image(image, "question_2b_orthogonal_-2.ras");
	clear(image);
	generate_perspective(0.5, -1, -2, 1, 1, 0, 1, 0.01, 10000, image);
	generate_perspective(-0.5, -1, -2, 1, 1, 0, 1, 0.01, 10000, image);
	write_image(image, "question_2b_perspective_-2.ras");
	
	clear(image);
	generate_orthogonal(0.5, -1, -3, 1, 1, 0, 1, 0.01, 10000, image);
	generate_orthogonal(-0.5, -1, -3, 1, 1, 0, 1, 0.01, 10000, image);
	write_image(image, "question_2b_orthogonal_-3.ras");
	clear(image);
	generate_perspective(0.5, -1, -3, 1, 1, 0, 1, 0.01, 10000, image);
	generate_perspective(-0.5, -1, -3, 1, 1, 0, 1, 0.01, 10000, image);
	write_image(image, "question_2b_perspective_-3.ras");

	/* question 3b */
	clear(image);
	generate_orthogonal(-1, -1, 0, 0, 0, 1, 1, 0.01, 10000, image);
	generate_orthogonal(1, -1, 0, 0, 0, 1, 1, 0.01, 10000, image);
	write_image(image, "question_3b_orthogonal_0_1.ras");
	clear(image);
	generate_perspective(-1, -1, 0, 0, 0, 1, 1, 0.01, 10000, image);
	generate_perspective(1, -1, 0, 0, 0, 1, 1, 0.01, 10000, image);
	write_image(image, "question_3b_perspective_0_1.ras");

	clear(image);
	generate_orthogonal(-1, -1, 0, 0, 1, 1, 1, 0.01, 10000, image);
	generate_orthogonal(1, -1, 0, 0, 1, 1, 1, 0.01, 10000, image);
	write_image(image, "question_3b_orthogonal_1_1.ras");
	clear(image);
	generate_perspective(-1, -1, 0, 0, 1, 1, 1, 0.01, 10000, image);
	generate_perspective(1, -1, 0, 0, 1, 1, 1, 0.01, 10000, image);
	write_image(image, "question_3b_perspective_1_1.ras");

	clear(image);
	generate_orthogonal(-1, -1, 0, 0, -1, 1, 1, 0.01, 10000, image);
	generate_orthogonal(1, -1, 0, 0, -1, 1, 1, 0.01, 10000, image);
	write_image(image, "question_3b_orthogonal_-1_1.ras");
	clear(image);
	generate_perspective(-1, -1, 0, 0, -1, 1, 1, 0.01, 10000, image);
	generate_perspective(1, -1, 0, 0, -1, 1, 1, 0.01, 10000, image);
	write_image(image, "question_3b_perspective_-1_1.ras");

	clear(image);
	generate_orthogonal(-1, -1, 0, 0, 0, -1, 1, 0.01, 10000, image);
	generate_orthogonal(1, -1, 0, 0, 0, 1, 1, 0.01, 10000, image);
	write_image(image, "question_3b_orthogonal_0_-1.ras");
	clear(image);
	generate_perspective(-1, -1, 0, 0, 0, -1, 1, 0.01, 10000, image);
	generate_perspective(1, -1, 0, 0, 0, -1, 1, 0.01, 10000, image);
	write_image(image, "question_3b_perspective_0_-1.ras");

	clear(image);
	generate_orthogonal(-1, -1, 0, 0, 1, -1, 1, 0.01, 10000, image);
	generate_orthogonal(1, -1, 0, 0, 1, -1, 1, 0.01, 10000, image);
	write_image(image, "question_3b_orthogonal_1_-1.ras");
	clear(image);
	generate_perspective(-1, -1, 0, 0, 1, -1, 1, 0.01, 10000, image);
	generate_perspective(1, -1, 0, 0, 1, -1, 1, 0.01, 10000, image);
	write_image(image, "question_3b_perspective_1_-1.ras");

	clear(image);
	generate_orthogonal(-1, -1, 0, 0, -1, -1, 1, 0.01, 10000, image);
	generate_orthogonal(1, -1, 0, 0, -1, -1, 1, 0.01, 10000, image);
	write_image(image, "question_3b_orthogonal_-1_-1.ras");
	clear(image);
	generate_perspective(-1, -1, 0, 0, -1, -1, 1, 0.01, 10000, image);
	generate_perspective(1, -1, 0, 0, -1, -1, 1, 0.01, 10000, image);
	write_image(image, "question_3b_perspective_-1_-1.ras");


	return 0;
}

/* generates orthogonal image */
void generate_orthogonal(float x0, float y0, float z0, float a, float b, float c, float fprime, float t_start, float t_end, unsigned char image[][COLS])
{
	float t, x, y, z, xprime, yprime;
	
	for (t = t_start; t < (t_end + 0.001); t += .001)    /* adjusted t to cover entire image */
	{
		/* parametric line */
		x = x0 + t * a;
		y = y0 + t * b;
		z = z0 + t * c;

		/* orthogonal projection */
		xprime = x;
		yprime = y;			

		/* plot point to the image */
		plot_logical_point(xprime, yprime, image);
	}
}

/* generates perspective image */
void generate_perspective(float x0, float y0, float z0, float a, float b, float c, float fprime, float t_start, float t_end, unsigned char image[][COLS])
{
	float t, x, y, z, xprime, yprime;

	for (t = t_start; t < (t_end + 0.001); t += .001)    /* adjusted t to cover entire image */
	{
		/* parametric line */
		x = x0 + t * a;
		y = y0 + t * b;
		z = z0 + t * c;

		/* orthogonal projection */
		xprime = (fprime / z) * x;
		yprime = (fprime / z) * y;			

		/* plot point to the image */
		plot_logical_point(xprime, yprime, image);
	}
}

/* writes image to file */
void write_image(unsigned char image[][COLS], char filename[])
{	
	int			i;
	FILE			*fp;
	char			 *ofile;
	unsigned char head[32];

	//_CRT_SECURE_NO_WARNINGS
	/* Create a header */ 
	header(ROWS, COLS, head);

	ofile = filename; // this is the name of your output file, modify the name according to the requirements

	if (!(fp = fopen(ofile, "wb")))
		fprintf(stderr, "error: could not open %s\n", ofile), exit(1);

	/* Write the header */
	fwrite(head, 4, 8, fp);

	for (i = 0; i < ROWS; i++) fwrite(image[i], 1, COLS, fp);
	fclose(fp);

}

void clear(unsigned char image[][COLS])
{
	int	i, j;
	for (i = 0; i < ROWS; i++)
		for (j = 0; j < COLS; j++) image[i][j] = 0;
}

int plot_logical_point(float x, float y, unsigned char image[][COLS])
{
	int	nx, ny;
	float	xc, yc;
	xc = COLS / ((float)LOGICAL_X_MAX - LOGICAL_X_MIN);
	yc = ROWS / ((float)LOGICAL_Y_MAX - LOGICAL_Y_MIN);
	nx = (x - LOGICAL_X_MIN) * xc;
	ny = (y - LOGICAL_Y_MIN) * yc;
	return plot_physical_point(nx, ny, image);
}

int plot_physical_point(int x, int y, unsigned char image[][COLS])
{
	if (in_range(x, y)) //return 0;
	return image[y][x] = 255;
	return 0;
}

int in_range(int x, int y)
{
	return x >= 0 && x < COLS && y >= 0 && y < ROWS;
}

void header(int row, int col, unsigned char head[32])
{
	int *p = (int *)head;
	char *ch;
	int num = row * col;

	/* Choose little-endian or big-endian header depending on the machine. Don't modify the contents */
	
	// Little-endian for PC
	*p = 0x956aa659;
	*(p + 3) = 0x08000000;
	*(p + 5) = 0x01000000;
	*(p + 6) = 0x0;
	*(p + 7) = 0xf8000000;

	ch = (char*)&col;
	head[7] = *ch;
	ch++;
	head[6] = *ch;
	ch++;
	head[5] = *ch;
	ch++;
	head[4] = *ch;

	ch = (char*)&row;
	head[11] = *ch;
	ch++;
	head[10] = *ch;
	ch++;
	head[9] = *ch;
	ch++;
	head[8] = *ch;

	ch = (char*)&num;
	head[19] = *ch;
	ch++;
	head[18] = *ch;
	ch++;
	head[17] = *ch;
	ch++;
	head[16] = *ch;
	

	/*
	// Big-endian for unix
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
