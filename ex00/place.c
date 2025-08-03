/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:39:47 by amtan             #+#    #+#             */
/*   Updated: 2025/08/03 23:06:38 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern int *const	g_n;
extern int *const	g_row_flag;
extern int *const	g_col_flag;
extern int *const	g_grid;

int	can_place(int pos, int v)
{
	int	row;
	int	col;
	int	bit;

	row = pos / *g_n;
	col = pos % *g_n;
	bit = 1 << v;
	if ((g_row_flag[row] & bit) || (g_col_flag[col] & bit))
		return (0);
	return (1);
}

void	place(int pos, int v)
{
	int	row;
	int	col;
	int	bit;

	row = pos / *g_n;
	col = pos % *g_n;
	bit = 1 << v;
	g_grid[pos] = v;
	g_row_flag[row] |= bit;
	g_col_flag[col] |= bit;
}

void	unplace(int pos, int v)
{
	int	row;
	int	col;
	int	bit;

	row = pos / *g_n;
	col = pos % *g_n;
	bit = 1 << v;
	g_row_flag[row] &= ~bit;
	g_col_flag[col] &= ~bit;
}
