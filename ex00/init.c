/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:08:36 by amtan             #+#    #+#             */
/*   Updated: 2025/08/02 18:08:37 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	init_clues(int *vals)
{
	int	i;

	i = 0;
	while (i < g_n)
	{
		g_top[i] = vals[i];
		g_bottom[i] = vals[g_n + i];
		g_left[i] = vals[2 * g_n + i];
		g_right[i] = vals[3 * g_n + i];
		if (g_top[i] > g_n || g_bottom[i] > g_n || g_left[i] > g_n
			|| g_right[i] > g_n)
			return (-1);
		else if ((g_top[i] + g_bottom[i] < 3 || g_left[i] + g_right[i] < 3)
			&& g_n > 1)
			return (-1);
		i++;
	}
}

static void	init_grid(void)
{
	int	i;

	i = 0;
	while (i < g_n * g_n)
	{
		g_grid[i] = 0;
		i++;
	}
}

static void	init_flags(void)
{
	int	i;

	i = 0;
	while (i < g_n)
	{
		g_row_flag[i] = 0;
		g_col_flag[i] = 0;
		i++;
	}
}

int	setup_game(int *vals, int count)
{
	g_n = count / 4;
	if (g_n < 1)
		return (-1);
	init_clues(vals);
	init_grid();
	init_flags();
	return (0);
}
