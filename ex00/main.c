/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:46:18 by amtan             #+#    #+#             */
/*   Updated: 2025/08/02 12:07:50 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_puterror(void);

int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		ft_puterror();
		return (1);
	}
	return (0);
}
