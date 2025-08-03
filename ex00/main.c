/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:46:18 by amtan             #+#    #+#             */
/*   Updated: 2025/08/03 21:30:11 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MAX_N 9

static int	g_s_n;
static int	g_s_top_clues[MAX_N];
static int	g_s_btm_clues[MAX_N];
static int	g_s_left_clues[MAX_N];
static int	g_s_right_clues[MAX_N];
static int	g_s_grid[MAX_N * MAX_N];
static int	g_s_row_flag[MAX_N];
static int	g_s_col_flag[MAX_N];

int *const	g_n = &g_s_n;
int *const	g_top_clues = g_s_top_clues;
int *const	g_btm_clues = g_s_btm_clues;
int *const	g_left_clues = g_s_left_clues;
int *const	g_right_clues = g_s_right_clues;
int *const	g_row_flag = g_s_row_flag;
int *const	g_col_flag = g_s_col_flag;
int *const	g_grid = g_s_grid;
int		valid_input(int argc, char **argv);
void	print_error(void);
int		solve(int pos);
void	print_solution(void);

int	main(int argc, char **argv)
{
	int	result;

	result = valid_input(argc, argv);
	if (result)
	{
		print_error();
		return (0);
	}
	if (solve(0))
		print_solution();
	else
		print_error();
	return (0);
}
