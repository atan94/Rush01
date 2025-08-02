#include <unistd.h> // for write() function

#define MAX_N 9 // macro to define the maximum size of the grid
		// MAX_N is set to 9 because the maximum grid size is 9x9 (for a 4x4 clues input)

static int	g_n; // size of the grid (number of rows/columns)
		// g_n is determined by the number of clues provided in the input
		// it is the number of clues divided by 4 (since there are 4 edges: top, bottom, left, right)

static int	g_top_clues[MAX_N]; // clues for the top edge of the grid
static int	g_btm_clues[MAX_N];
static int	g_left_clues[MAX_N];
static int	g_left_clues[MAX_N];

static int	g_grid[MAX_N * MAX_N]; // grid to hold the heights of the towers
		// g_grid is a 1D array representing a 2D grid of size g_n x g_n
		// each element represents the height of the tower at that position in the grid

		static int	g_row_flag[MAX_N]; // flags to keep track of which heights have been placed in each row
		// g_row_flag is a bitmask for each row, where each bit represents whether a tower of that height has been placed in that row
		// e.g., if g_row_flag[0] = 5 (binary 101), it means towers of height 1 and 3 have been placed in row 0
static int	g_col_flag[MAX_N];

static void	print_error(void) // print "Error" to the standard output
{
	write(1, "Error\n", 6);
}

static void	print_solution(void)
		// print the solution grid to the standard output
{
	int row;
	int col;
	char digit;

	row = 0;
	while (row < g_n) // iterate through each row in the grid
	{
		col = 0;
		while (col < g_n) // iterate through each column in the current row
		{
			digit = g_grid[row * g_n + col] + '0';
				// convert the height of the tower at the current position to a character (digit)
			write(1, &digit, 1);
				// write the character to the standard output
			if (col < g_n - 1) // if not the last column, write a space after the digit
				write(1, " ", 1);
			col++;
		}
		write(1, "\n", 1); // write a newline after each row
		row++;
	}
}

static int	count_vis_row(int row)
		// count the number of visible towers in a given row
{
	int max;   // the maximum height of the towers seen so far in the row row
	int count; // the number of visible towers in the row row
	int idx;   // the index of the current column in the row row
	int value; // the height of the tower at the current position in the row row

	max = 0;
	count = 0;
	idx = 0;
	while (idx < g_n) // iterate through each column in the row row
	{
		value = g_grid[row * g_n + idx];
			// get the height of the tower at the current position in the row row
		if (value > max)
			// if the height of the tower at the current position is greater than the maximum height seen so far
		{
			max = value; // update the maximum height seen so far
			count++;     // increment the count of visible towers
		}
		idx++; // move to the next column in the row row
	}
	return (count); // return the number of visible towers in the row row
}

static int	count_vis_row_rev(int row)
		// count the number of visible towers in a given row from the right side
{
	int max;
	int count;
	int idx;
	int value;

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
		idx--; // move to the previous column in the row row
	}
	return (count);
}

static int	count_vis_col(int col)
		// count the number of visible towers in a given column
{
	int max;
	int count;
	int idx;
	int value;

	max = 0;
	count = 0;
	idx = 0;
	while (idx < g_n)
	{
		value = g_grid[idx * g_n + col];
		{
			max = value;
			count++;
		}
		idx++;
	}
	return (count);
}

static int	count_vis_col_rev(int col)
		// count the number of visible towers in a given column from the bottom side
{
	int max;
	int count;
	int idx;
	int value;

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
		idx--; // move to the previous row in the column col
	}
	return (count);
}

static int	check_row(int row) // check if the row is valid
// (i.e., if the number of visible towers from the left and right matches the clues)
{
	return (count_vis_row(row) == g_left_clues[row]
		&& count_vis_row_rev(row) == g_left_clues[row]);
		// check if the number of visible towers from the left and right matches the clues
}

static int	check_col(int col)
{
	return (count_vis_col(col) == g_top_clues[col]
		&& count_vis_col_rev(col) == g_btm_clues[col]);
		// check if the number of visible towers from the top and bottom matches the clues
}

static int	solve(int pos);

static int	can_place(int pos, int v)
		// check if a tower of height v can be placed at position pos
{
	int row;
	int col;
	int bit;

	row = pos / g_n; // pos is the current position in the grid,
		// and g_n is the size of the grid (number of rows/columns)
	col = pos % g_n;
	bit = 1 << v;
		// shift the 1 bit left by v places to represent the height of the tower to try to place
	if ((g_row_flag[row] & bit) || (g_col_flag[col] & bit))
		// & compares bits at each place and returns a 1 only if both bits are 1 (i.e.,
		// a tower of that height has already been placed in that row/col)
		return (0);
			// failed to place the tower of height v at position pos
	return (1);
		// succeeded to place the tower of height v at position pos
}

static void	place(int pos, int v) // place a tower of height v at position pos
{
	int row;
	int col;
	int bit;

	row = pos / g_n; // pos is the current position in the grid,
		// and g_n is the size of the grid (number of rows/columns)
	col = pos % g_n;
	bit = 1 << v;
		// shift the 1 bit left by v places to represent the height of the tower to place
	g_grid[pos] = v;
		// place the tower of height v at position pos in the grid
	g_row_flag[row] |= bit;
		// | compares bits at each place and returns a 1 if either bit is 1 (i.e.,
		// a tower of that height has been placed in that row/col)
	g_col_flag[col] |= bit;
}

static void	unplace(int pos, int v)
		// unplace a tower of height v at position pos
		// (i.e., backtrack/undo the placement)
{
	int	row;
	int	col;
	int	bit;

	row = pos / g_n;
	col = pos % g_n;
	bit = 1 << v;
		// shift the 1 bit left by v places to represent the height of the tower to unplace
	g_row_flag[row] &= ~bit;
		// & compares bits at each place and returns a 1 only if both bits are 1; ~bit flips the bits,
		// so this effectively removes the tower of height v from the row and column flags
	g_col_flag[col] &= ~bit;
}

static int	violates(int pos)
		// check if placing a tower at position pos violates any of the clues
{
	int row;
	int col;

	row = pos / g_n;
	col = pos % g_n;
	if (col == g_n - 1 && !check_row(row)) // if we are at the end of a row, check if the row is valid
	// (i.e., if the number of visible towers from the left and right matches the clues)
		return (1); // row is not valid
	if (row == g_n - 1 && !check_col(col)) // if we are at the end of a column, check if the column is valid
		// (i.e., if the number of visible towers from the top and bottom matches the clues)
		return (1); // column is not valid
	return (0); // no violations found, so we can continue solving
}

static int	try_value(int pos, int v)
		// try to place a tower of height v at position pos
{
	if (v > g_n)
		return (0); // tried all heights 1...g_n,
			none worked --> this path is a dead end --> backtrack
	if (can_place(pos, v))
		// check if a tower of height v can be placed at position pos (i.e.,
		no tower of height v has been placed in the same row or column)
	{
		place(pos, v); // if you can place it,
			// then place the tower of height v at position pos
		if (!violates(pos) && solve(pos + 1))
			// if placing the tower of height v at position pos does not violate any clues,
			then try to solve the next position (i.e.,
			move to the next cell in the grid)
			return (1);
				// if the next deeper position was successfully solved,
				// then return 1 to indicate success
		unplace(pos, v);
			// if placing the tower of height v at position pos did not lead to a solution,
			// then unplace it (backtrack/undo the placement)
	}
	return (try_value(pos, v + 1));
		// if you cannot place the tower of height v at position pos,
		// then try the next height (i.e., try placing a tower of height v
		//+ 1 at position pos)
}

static int	solve(int pos) // solve the puzzle starting from position pos
{
	// Think of this backtracking approach as walking through a maze
	if (pos == g_n * g_n)
		// End of the maze: Yay I made it all the way through an found an exit (solution)!
		return (1);
	return (try_value(pos, 1));
		// Begin the maze: Start trying values at this cell
		// (i.e. start at pos = 0, and start trying from tower height = 1)
}

static int	valid_args(int argc, char **argv, int *vals, int *count)
		// validate the command line arguments and fill the vals array with the clues
{
	char *s;

	if (argc != 2)
		// check if the number of arguments is correct (should be exactly 2: the program name and the clues)
		return (-1);
	s = argv[1]; // get the clues from the command line arguments
	while (*s)   // iterate through the clues string
	{
		if (*s == ' ') // if the current character is a space, skip it
			s++;
		else if (*s < '1' || *s > '9' || *count >= 4 * MAX_N)
			// if the current character is not a digit between '1' and '9',
			// or if we have already filled the vals array with the maximum number of clues
			return (-1);                                      // invalid input
		else
		{
			vals[*count] = *s - '0';
				// convert the character to an integer (digit) and store it in the vals array
			(*count)++;              // increment the count of clues
			s++;
				// move to the next character in the clues string
			if (*s && *s != ' ')     // if the next character is not a space,
			// then we have an invalid input
			// (i.e., more than one digit without a space in between)
				return (-1);
		}
	}
	if ((*count) % 4) // if the number of clues is not a multiple of 4
	// (i.e., not enough clues to fill all 4 edges of the grid)
		return (-1);  // invalid input
	return (0);       // valid input
}

static int	init_clues(int *vals) // initialize the clues from the vals array
{
	int i;

	i = 0;
	while (i < g_n)
		// loop through the number of clues (g_n) and fill them into the global arrays
	{
		g_top_clues[i] = vals[i];
		g_btm_clues[i] = vals[g_n + i];
		g_left[i] = vals[2 * g_n + i];
		g_right[i] = vals[3 * g_n + i];
		if (g_top_clues[i] > g_n || g_btm_clues[i] > g_n || g_left[i] > g_n
			|| g_right[i] > g_n)
			// check if any clue is greater than the size of the grid (g_n)
			return (-1);
				// invalid input
		else if ((g_top_clues[i] + g_btm_clues[i] < 3 || g_left[i] + g_right[i] < 3)
			&& g_n > 1)
			// check if the sum of the top and bottom clues or the left and right clues is less than 3,
			// which is not possible for a grid larger than 1x1
			return (-1);
				// invalid input
		i++;
			// if the clues are valid, move to the next clue
	}
	return (0);
		// return 0 to indicate that the clues were successfully initialized
}

static void	init_grid(void) // initialize the grid and flags
{
	int i;

	i = 0;
	while (i < g_n * g_n) // loop through the grid size
	// (g_n * g_n) and initialize the grid with 0s (no towers placed yet)
	{
		g_grid[i] = 0;
		i++;
	}
}

static void	init_flags(void)
		// initialize the row and column flags; flags are used to keep track of which heights have been placed in each row and column
{
	int i;

	i = 0;
	while (i < g_n)
		// loop through the number of rows/columns (g_n) and initialize the flags with 0s (no towers placed yet)
	{
		g_row_flag[i] = 0;
		g_col_flag[i] = 0;
		i++;
	}
}

int	setup_game(int *vals, int count)
		// setup the game by initializing the global variables and checking the clues
{
	g_n = count / 4;
		// calculate the size of the grid (g_n) based on the number of clues provided
	if (g_n < 1)
		// check if the grid size is valid (should be at least 1)
		return (-1);      // invalid input
	if (init_clues(vals)) // initialize the clues from the vals array; returns
		-1 if the clues are invalid
		return (-1);      // invalid input
	init_grid();          // initialize the grid with 0s (no towers placed yet)
	init_flags();
		// initialize the row and column flags with 0s (no towers placed yet)
	return (0);
		// return 0 to indicate that the game was successfully set up
}

static int	valid_input(int argc, char **argv)
{
	int vals[4 * MAX_N]; // array to hold all the values of the clues
	int count;
		// to count how many integers (digits) were provided as input
	count = 0;
	if (valid_args(argc, argv, vals, &count) != 0)
		// validate the command line arguments and fill the vals array with the clues;
		// returns -1 if the input is invalid
		return (-1); // invalid input
	if (setup_game(vals, count) != 0)
		// setup the game by initializing the global variables and checking the clues;
		// returns -1 if the clues are invalid
		return (-1); // invalid input
	return (0); // input is valid
}

int	main(int argc, char **argv)
{
	int	result;

	result = valid_input(argc, argv); // returns 0 if input is valid; and
		-1 if input is invalid
	if (result)                       // if input is invalid
	{
		print_error(); // print "Error" to the standard output
		return (0);
			// exit the program with a return code of 0 (indicating successful termination,
			// even though it was due to an error)
	}
	if (solve(0))
		// a recursive function; returns 1 to mean that a solution was successfully found; the input 0 means: start solving from position 0 (top left of the grid)
		print_solution();
			// print the solution if solve() successfully found a solution)
	else
		print_error();
	return (0);
}
