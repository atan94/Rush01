static void	init_clues(int *vals)
{
	int	i;

	i = 0;
	while (i < g_n)
	{
		g_top[i] = vals[i];
		g_bottom[i] = vals[g_n + i];
		g_left_clue[i] = vals[2 * g_n + i];
		g_right_clue[i] = vals[3 * g_n + i];
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
