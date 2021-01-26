/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   micro_paint.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Marty <Marty@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/07 09:43:38 by Marty         #+#    #+#                 */
/*   Updated: 2020/12/09 09:22:18 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <math.h>

typedef struct	exam03
{
	int			w;
	int			h;
	char		cs;
	int			i;
	char		fill[256];
	float		x[256];
	float		y[256];
	float		width[256];
	float		height[256];
	char		cc[256];
}				t_data;

int		error_message(int ernb)
{
	if (ernb == 1)
		write(1, "Error: argument", 15);
	if (ernb == 2)
		write(1, "Error: Operation file corrupted\n", 32);
	return (1);
}

int		draw_square(t_data *d, int i, float x, float y)
{
	while (i >= 0)
	{
		if ((x >= d->x[i] && x <= d->x[i] + d->width[i]) &&
		(y >= d->y[i] && y <= d->y[i] + d->height[i]))
		{
			if (d->fill[i] == 'R' ||
			(x - d->x[i] < 1.000000000 || d->x[i] + d->width[i] - x < 1.00000000 ||
			y - d->y[i] < 1.000000000 || d->y[i] + d->height[i] - y < 1.00000000))
			{
				write(1, &d->cc[i], 1);
				return (1);
			}
		}
		i--;
	}
	return (0);
}

void	draw(t_data *d)
{
	float x;
	float y;

	y = 0;
	while (y < d->h)
	{
		x = 0;
		while (x < d->w)
		{
			if (draw_square(d, d->i - 1, x, y))
			{
				x++;
				continue ;
			}
			else
			{
				write(1, &d->cs, 1);
				x++;
			}
		}
		write(1, "\n", 1);
		y++;
	}
}

int		main(int argc, char *argv[])
{
	int		ret;
	FILE	*file;
	t_data	d;

	d.i = 0;
	if (argc != 2)
		return (error_message(1));
	file = fopen(argv[1], "r");
	if (!file)
		return (error_message(2));
	ret = fscanf(file, "%d %d %c\n", &d.w, &d.h, &d.cs);
	if (ret != 3 || d.w < 1 || d.w > 300 || d.h < 1 || d.h > 300 || !d.cs)
		return (error_message(2));
	while (1)
	{
		ret = fscanf(file, "%c %f %f %f %f %c\n", &d.fill[d.i], &d.x[d.i], &d.y[d.i], &d.width[d.i], &d.height[d.i], &d.cc[d.i]);
		if (ret == EOF)
			break ;
		if (ret != 6 || (d.fill[d.i] != 'r' && d.fill[d.i] != 'R') || d.width[d.i] <= 0 || d.height[d.i] <= 0)
			return (error_message(2));
		d.i++;
	}
	draw(&d);
	fclose(file);
	return (0);
}
