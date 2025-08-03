/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:46:18 by amtan             #+#    #+#             */
/*   Updated: 2025/08/03 20:00:57 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
