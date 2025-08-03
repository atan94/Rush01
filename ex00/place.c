/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:39:47 by amtan             #+#    #+#             */
/*   Updated: 2025/08/03 20:00:55 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MAX_N 9

extern int *const g_n;
extern int *const g_row_flag[MAX_N];
extern int *const g_col_flag[MAX_N];
extern int *const g_grid[MAX_N * MAX_N];

int	can_place(int pos, int v)
{
	int	row;
	int	col;
	int	bit;

	// maybe we can check if the cell is already occupied here
	row = pos / *g_n;
	col = pos % *g_n;
	bit = 1 << v;
	if ((*g_row_flag[row] & bit) || (*g_col_flag[col] & bit))
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
	*g_grid[pos] = v;
	*g_row_flag[row] |= bit;
	*g_col_flag[col] |= bit;
}

void	unplace(int pos, int v)
{
	int	row;
	int	col;
	int	bit;

	row = pos / *g_n;
	col = pos % *g_n;
	bit = 1 << v;
	*g_row_flag[row] &= ~bit;
	*g_col_flag[col] &= ~bit;
}
