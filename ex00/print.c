/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:26:30 by amtan             #+#    #+#             */
/*   Updated: 2025/08/03 23:06:51 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

extern int *const	g_n;
extern int *const	g_grid;

void	print_error(void)
{
	write(2, "Error\n", 6);
}

void	print_solution(void)
{
	int		row;
	int		col;
	char	digit;

	row = 0;
	while (row < *g_n)
	{
		col = 0;
		while (col < *g_n)
		{
			digit = g_grid[row * *g_n + col] + '0';
			write(1, &digit, 1);
			if (col < *g_n - 1)
				write(1, " ", 1);
			col++;
		}
		write(1, "\n", 1);
		row++;
	}
}
