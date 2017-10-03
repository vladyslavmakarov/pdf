/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 13:54:39 by vmakarov          #+#    #+#             */
/*   Updated: 2017/09/03 13:54:41 by vmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int ac, char **av)
{
	t_point		***m;
	t_helper	*meta;

	if (ac != 2)
	{
		ft_putstr("Usage : ./fdf <filename> [ case_size z_size ]");
		ft_putstr("\n");
		return (0);
	}
	if (!(meta = (t_helper *)malloc(sizeof(t_helper))))
		return (0);
	meta->mlx = mlx_init();
	meta->win = mlx_new_window(meta->mlx, 1000, 1000, "mlx 42");
	meta->parameters = parameters_init();
	m = get_matrix(av, meta->parameters);
	meta->matrix = m;
	draw_figure(meta);
	mlx_key_hook(meta->win, key_inputs, meta);
	mlx_loop(meta->mlx);
	return (0);
}

t_figure	*parameters_init(void)
{
	t_figure	*new;

	if (!(new = (t_figure *)malloc(sizeof(t_figure))))
		return (NULL);
	new->a = -5.94;
	new->b = -6.82;
	new->t = -5.56;
	new->vert = 400;
	new->hor = 300;
	new->scale = 40;
	return (new);
}

void	draw_figure(t_helper *m)
{
	int i;
	int j;

	i = 0;
	while (m->matrix[i])
	{
		j = 0;
		if (m->matrix[i + 1] != NULL)
		{
			while (m->matrix[i][j])
			{
				if (m->matrix[i][j + 1] != NULL)
				{
					line(m->matrix[i][j]->d_2, m->matrix[i][j + 1]->d_2, m, 0xFF00FF);
					line(m->matrix[i][j]->d_2, m->matrix[i + 1][j]->d_2, m, 0xFF00FF);
				}
				if (m->matrix[i][j + 1] == NULL)
					line(m->matrix[i][j]->d_2, m->matrix[i + 1][j]->d_2, m, 0xFF00FF);
				j++;
			}
		}
		if (m->matrix[i + 1] == NULL)
		{
			while (m->matrix[i][j])
			{
				if (m->matrix[i][j + 1] != NULL)
					line(m->matrix[i][j]->d_2, m->matrix[i][j + 1]->d_2, m, 0xFF00FF);
				j++;
			}
		}
		i++;
	}
}
