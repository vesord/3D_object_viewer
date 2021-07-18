#ifndef BMP_H
# define BMP_H

typedef struct	s_bmp_file_header
{
	char	type_1;
	char	type_2;
	int		size;
	int		reserved;
	int		offset_to_color_bits;
}				t_bmp_file_header;

typedef struct	s_bmp_info
{
	int		size;
	int		width;
	int		height;
	short	planes;
	short	bpp;
	int		compression;
	int		img_size;
	int		ppm_x;
	int		ppm_y;
	int		color_table;
	int		color_table_size;
}				t_bmp_info;

typedef struct	s_bmp_file
{
	char	*data;
	t_bmp_file_header	bfh;
	t_bmp_info			bmi;

}				t_bmp_data;

t_bmp_data *bmp_load(const char *filename);

#endif
