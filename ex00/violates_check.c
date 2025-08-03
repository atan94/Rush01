/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   violates_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:43:51 by amtan             #+#    #+#             */
/*   Updated: 2025/08/03 23:05:58 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern int *const	g_n;
extern int *const	g_top_clues;
extern int *const	g_btm_clues;
extern int *const	g_left_clues;
extern int *const	g_right_clues;

int			count_vis_row(int row);
int			count_vis_row_rev(int row);
int			count_vis_col(int col);
int			count_vis_col_rev(int col);

static int	check_row(int row)
{
	return (count_vis_row(row) == g_left_clues[row]
		&& count_vis_row_rev(row) == g_right_clues[row]);
}

static int	check_col(int col)
{
	return (count_vis_col(col) == g_top_clues[col]
		&& count_vis_col_rev(col) == g_btm_clues[col]);
}

int	violates(int pos)
{
	int	row;
	int	col;

	row = pos / *g_n;
	col = pos % *g_n;
	if (col == *g_n - 1 && !check_row(row))
		return (1);
	if (row == *g_n - 1 && !check_col(col))
		return (1);
	return (0);
}
