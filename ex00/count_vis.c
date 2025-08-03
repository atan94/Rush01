/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_vis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:46:17 by amtan             #+#    #+#             */
/*   Updated: 2025/08/03 23:07:52 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern int *const	g_n;
extern int *const	g_grid;

int	count_vis_row(int row)
{
	int	max;
	int	count;
	int	idx;
	int	value;

	max = 0;
	count = 0;
	idx = 0;
	while (idx < *g_n)
	{
		value = g_grid[row * *g_n + idx];
		if (value > max)
		{
			max = value;
			count++;
		}
		idx++;
	}
	return (count);
}

int	count_vis_row_rev(int row)
{
	int	max;
	int	count;
	int	idx;
	int	value;

	max = 0;
	count = 0;
	idx = *g_n - 1;
	while (idx >= 0)
	{
		value = g_grid[row * *g_n + idx];
		if (value > max)
		{
			max = value;
			count++;
		}
		idx--;
	}
	return (count);
}

int	count_vis_col(int col)
{
	int	max;
	int	count;
	int	idx;
	int	value;

	max = 0;
	count = 0;
	idx = 0;
	while (idx < *g_n)
	{
		value = g_grid[idx * *g_n + col];
		if (value > max)
		{
			max = value;
			count++;
		}
		idx++;
	}
	return (count);
}

int	count_vis_col_rev(int col)
{
	int	max;
	int	count;
	int	idx;
	int	value;

	max = 0;
	count = 0;
	idx = *g_n - 1;
	while (idx >= 0)
	{
		value = g_grid[idx * *g_n + col];
		if (value > max)
		{
			max = value;
			count++;
		}
		idx--;
	}
	return (count);
}
