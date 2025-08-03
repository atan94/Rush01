/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:09:07 by amtan             #+#    #+#             */
/*   Updated: 2025/08/03 21:11:07 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MAX_N 9

extern int *const	g_n;

int			init_clues(int *vals);
void		init_grid(void);
void		init_flags(void);

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

static int	setup_game(int *vals, int count)
{
	*g_n = count / 4;
	if (*g_n < 1)
		return (-1);
	if (init_clues(vals))
		return (-1);
	init_grid();
	init_flags();
	return (0);
}

int	valid_input(int argc, char **argv)
{
	int	vals[4 * MAX_N];
	int	count;

	count = 0;
	if (valid_args(argc, argv, vals, &count) != 0)
		return (-1);
	if (setup_game(vals, count) != 0)
		return (-1);
	return (0);
}
