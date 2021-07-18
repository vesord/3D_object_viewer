#include "scop.h"
#include "bmp_load.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

static int			read_bmp_headers(int fd, t_bmp_data *bmp_file)
{
	if (read(fd, &(bmp_file->bfh.type_1), 1) < 0 ||		// Check if 'B'
		read(fd, &(bmp_file->bfh.type_2), 1) < 0 ||		// Check if 'M'
		read(fd, &(bmp_file->bfh.size), 4) < 0 ||
		read(fd, &(bmp_file->bfh.reserved), 4) < 0 ||
		read(fd, &(bmp_file->bfh.offset_to_color_bits), 4) < 0 ||
		read(fd, &(bmp_file->bmi.size), 4) < 0 ||
		read(fd, &(bmp_file->bmi.width), 4) < 0 ||
		read(fd, &(bmp_file->bmi.height), 4) < 0 ||
		read(fd, &(bmp_file->bmi.planes), 2) < 0 ||
		read(fd, &(bmp_file->bmi.bpp), 2) < 0 ||			// Check if not 24 or 32
		read(fd, &(bmp_file->bmi.compression), 4) < 0 ||	// Check if not 0
		read(fd, &(bmp_file->bmi.img_size), 4) < 0 ||	// Check if 0
		read(fd, &(bmp_file->bmi.ppm_x), 4) < 0 ||
		read(fd, &(bmp_file->bmi.ppm_y), 4) < 0 ||
		read(fd, &(bmp_file->bmi.color_table), 4) < 0 ||
		read(fd, &(bmp_file->bmi.color_table_size), 4) < 0)
	{
		fprintf(stderr, "Cant read .bmp headers\n");
		return -1;
	}
	return 1;
}

static int			validate_bmp_data(t_bmp_data *bmp_file)
{
	if (!(bmp_file->bfh.type_1 == 'B' && bmp_file->bfh.type_2 == 'M'))
	{
		fprintf(stderr, "File is not supported: header is not \"BM\"");
		return -1;
	}
	if (bmp_file->bmi.bpp < 24)
	{
		fprintf(stderr, "File is not supported: bpp is too small");
		return -1;
	}
	if (bmp_file->bmi.size == 0)
	{
		fprintf(stderr, "File is not supported: size should not be 0");
		return -1;
	}
	if (bmp_file->bmi.compression != 0 && bmp_file->bmi.compression != 3 &&
		bmp_file->bmi.compression != 6)
	{
		fprintf(stderr, "File is not supported: size should not be compressed");
		return -1;
	}
	return 1;
}

static int			read_bmp_data(int fd, t_bmp_data *bmp_file)
{
	bmp_file->data = malloc(bmp_file->bmi.img_size);
	if (!bmp_file->data)
	{
		fprintf(stderr, "Not enough memory\n");
		return -1;
	}
	lseek(fd, bmp_file->bfh.offset_to_color_bits, SEEK_SET);
	if (read(fd, bmp_file->data, bmp_file->bmi.img_size) < 0)
	{
		fprintf(stderr, "Cant read pixel data\n");
		free(bmp_file->data);
		bmp_file->data = NULL;
		return -1;
	}
	return 1;
}

static t_bmp_data	*create_s_bmp_file()
{
	t_bmp_data *bmp_file;

	if ( !(bmp_file = malloc(sizeof(*bmp_file))) )
	{
		fprintf(stderr, "Not enough memory\n");
		return NULL;
	}
	bmp_file->data = NULL;
	return bmp_file;
}

t_bmp_data *bmp_load(const char *filename) {
	int					fd;
	t_bmp_data 			*bmp_file;

	fd = -1;
	bmp_file = NULL;

	if ((bmp_file = create_s_bmp_file()) == NULL ||
		(fd = open(filename, O_RDONLY)) < 0 ||
		read_bmp_headers(fd, bmp_file) < 0 ||
		validate_bmp_data(bmp_file) < 0 ||
		read_bmp_data(fd, bmp_file) < 0)
	{
		if (fd < 0)
			fprintf(stderr, "Failed to open file %s\n", filename);
		else
			close(fd);
		free(bmp_file);
		return NULL;
	}
	close(fd);
	return bmp_file;
}

void	free_bmp(t_bmp_data **bmp_ptr)
{
	if (!bmp_ptr || !*bmp_ptr)
		return;
	free((*bmp_ptr)->data);
	free(*bmp_ptr);
	*bmp_ptr = NULL;
}
