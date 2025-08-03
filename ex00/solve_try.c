/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_try.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:18:02 by amtan             #+#    #+#             */
/*   Updated: 2025/08/03 21:14:28 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern int *const	g_n;

int			can_place(int pos, int v);
void		place(int pos, int v);
void		unplace(int pos, int v);
int			solve(int pos);
int			violates(int pos);

static int	try_value(int pos, int v)
{
	if (v > *g_n)
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

int	solve(int pos)
{
	if (pos == (*g_n) * (*g_n))
		return (1);
	return (try_value(pos, 1));
}
