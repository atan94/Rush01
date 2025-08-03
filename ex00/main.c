/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:46:18 by amtan             #+#    #+#             */
/*   Updated: 2025/08/03 21:11:16 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MAX_N 9

static int s_n;
static int s_top_clues[MAX_N];
static int s_btm_clues[MAX_N];
static int s_left_clues[MAX_N];
static int s_right_clues[MAX_N];
static int s_grid[MAX_N * MAX_N];
static int s_row_flag[MAX_N];
static int s_col_flag[MAX_N];

int *const	g_n = &s_n;
int *const	g_top_clues = s_top_clues;
int *const	g_btm_clues = s_btm_clues;
int *const	g_left_clues = s_left_clues;
int *const	g_right_clues = s_right_clues;
int *const	g_row_flag = s_row_flag;
int *const	g_col_flag = s_col_flag;
int *const	g_grid = s_grid;
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
