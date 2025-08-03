/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:08:36 by amtan             #+#    #+#             */
/*   Updated: 2025/08/03 23:05:21 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern int *const	g_n;
extern int *const	g_top_clues;
extern int *const	g_btm_clues;
extern int *const	g_left_clues;
extern int *const	g_right_clues;
extern int *const	g_row_flag;
extern int *const	g_col_flag;
extern int *const	g_grid;

int	init_clues(int *vals)
{
	int	i;

	i = 0;
	while (i < *g_n)
	{
		g_top_clues[i] = vals[i];
		g_btm_clues[i] = vals[*g_n + i];
		g_left_clues[i] = vals[2 * *g_n + i];
		g_right_clues[i] = vals[3 * *g_n + i];
		if (g_top_clues[i] > *g_n || g_btm_clues[i] > *g_n
			|| g_left_clues[i] > *g_n || g_right_clues[i] > *g_n)
			return (-1);
		else if ((g_top_clues[i] + g_btm_clues[i] < 3 || g_left_clues[i]
				+ g_right_clues[i] < 3) && *g_n > 1)
			return (-1);
		i++;
	}
	return (0);
}

void	init_grid(void)
{
	int	i;

	i = 0;
	while (i < *g_n * *g_n)
	{
		g_grid[i] = 0;
		i++;
	}
}

void	init_flags(void)
{
	int	i;

	i = 0;
	while (i < *g_n)
	{
		g_row_flag[i] = 0;
		g_col_flag[i] = 0;
		i++;
	}
}
