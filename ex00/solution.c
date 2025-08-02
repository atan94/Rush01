#include <unistd.h>

#define MAX_N 9

static int	g_n;
static int	g_top[MAX_N];
static int	g_bottom[MAX_N];
static int	g_left_clue[MAX_N];
static int	g_right_clue[MAX_N];
static int	g_grid[MAX_N * MAX_N];
static int	g_row_flag[MAX_N];
static int	g_col_flag[MAX_N];

static void	print_error(void)
{
	write(1, "Error\n", 6);
}

static void	print_solution(void)
{
	int		row;
	int		col;
	char	digit;

	row = 0;
	while (row < g_n)
	{
		col = 0;
		while (col < g_n)
		{
			digit = g_grid[row * g_n + col] + '0';
			write(1, &digit, 1);
			if (col < g_n - 1)
				write(1, " ", 1);
			col++;
		}
		write(1, "\n", 1);
		row++;
	}
}

static int	count_vis_row(int row)
{
	int	max;
	int	count;
	int	idx;
	int	value;

	max = 0;
	count = 0;
	idx = 0;
	while (idx < g_n)
	{
		value = g_grid[row * g_n + idx];
		if (value > max)
		{
			max = value;
			count++;
		}
		idx++;
	}
	return (count);
}

static int	count_vis_row_rev(int row)
{
	int	max;
	int	count;
	int	idx;
	int	value;

	max = 0;
	count = 0;
	idx = g_n - 1;
	while (idx >= 0)
	{
		value = g_grid[row * g_n + idx];
		if (value > max)
		{
			max = value;
			count++;
		}
		idx--;
	}
	return (count);
}

static int	count_vis_col(int col)
{
	int	max;
	int	count;
	int	idx;
	int	value;

	max = 0;
	count = 0;
	idx = 0;
	while (idx < g_n)
	{
		value = g_grid[idx * g_n + col];
		if (value > max)
		{
			max = value;
			count++;
		}
		idx++;
	}
	return (count);
}

static int	count_vis_col_rev(int col)
{
	int	max;
	int	count;
	int	idx;
	int	value;

	max = 0;
	count = 0;
	idx = g_n - 1;
	while (idx >= 0)
	{
		value = g_grid[idx * g_n + col];
		if (value > max)
		{
			max = value;
			count++;
		}
		idx--;
	}
	return (count);
}

static int	check_row(int row)
{
	return (count_vis_row(row) == g_left_clue[row]
		&& count_vis_row_rev(row) == g_right_clue[row]);
}

static int	check_col(int col)
{
	return (count_vis_col(col) == g_top[col]
		&& count_vis_col_rev(col) == g_bottom[col]);
}

static int	solve(int pos);

static int	can_place(int pos, int v)
{
	int	row;
	int	col;
	int	bit;

	row = pos / g_n;
	col = pos % g_n;
	bit = 1 << v;
	if ((g_row_flag[row] & bit) || (g_col_flag[col] & bit))
		return (0);
	return (1);
}

static void	place(int pos, int v)
{
	int	row;
	int	col;
	int	bit;

	row = pos / g_n;
	col = pos % g_n;
	bit = 1 << v;
	g_grid[pos] = v;
	g_row_flag[row] |= bit;
	g_col_flag[col] |= bit;
}

static void	unplace(int pos, int v)
{
	int	row;
	int	col;
	int	bit;

	row = pos / g_n;
	col = pos % g_n;
	bit = 1 << v;
	g_row_flag[row] &= ~bit;
	g_col_flag[col] &= ~bit;
}

static int	violates(int pos)
{
	int	row;
	int	col;

	row = pos / g_n;
	col = pos % g_n;
	if (col == g_n - 1 && !check_row(row))
		return (1);
	if (row == g_n - 1 && !check_col(col))
		return (1);
	return (0);
}

static int	try_value(int pos, int v)
{
	if (v > g_n)
		return (0);
	if (can_place(pos, v))
	{
		place(pos, v);
		if (!violates(pos) && solve(pos + 1))
			return (1);
		unplace(pos, v);
	}
	return (try_value(pos, v + 1));
}

static int	solve(int pos)
{
	if (pos == g_n * g_n)
		return (1);
	return (try_value(pos, 1));
}

static int	valid_args(int argc, char **argv, int *vals, int *count)
{
	char	*s;

	if (argc != 2)
		return (-1);
	s = argv[1];
	while (*s)
	{
		if (*s == ' ')
			s++;
		else if (*s < '1' || *s > '9' || *count >= 4 * MAX_N)
			return (-1);
		else
		{
			vals[*count] = *s - '0';
			(*count)++;
			s++;
			if (*s && *s != ' ')
				return (-1);
		}
	}
	if ((*count) % 4)
		return (-1);
	return (0);
}

static int	init_clues(int *vals)
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
	return (0);
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
	if (init_clues(vals))
		return (-1);
	init_grid();
	init_flags();
	return (0);
}

static int	valid_input(int argc, char **argv)
{
	int	vals[4 * MAX_N]; // array to hold all the values of the clues
	int	count; // to count how many integers (digits) were provided as input

	count = 0;
	if (valid_args(argc, argv, vals, &count) != 0)
		return (-1);
	if (setup_game(vals, count) != 0)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	int	result;

	result = valid_input(argc, argv); // returns 0 if input is valid; and -1 if input is invalid
	if (result) // if input is invalid
	{
		print_error();
		return (0);
	}
	if (solve(0)) // a recursive function; returns 1 to mean that a solution was successfully found; the input 0 means: start solving from position 0 (top left of the grid)
		print_solution(); // print the solution if solve() successfully found a solution)
	else
		print_error();
	return (0);
}
