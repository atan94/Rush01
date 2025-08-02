/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:09:07 by amtan             #+#    #+#             */
/*   Updated: 2025/08/02 18:09:12 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			setup_game(int *vals, int count);

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
