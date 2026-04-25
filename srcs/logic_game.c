/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 13:51:51 by lud-adam          #+#    #+#             */
/*   Updated: 2026/04/25 15:17:10 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "board.h"

#include <stdlib.h>
#include <time.h>

static int gen_number();

bool	fill_start_numbers(t_board* board)
{
	srand(time(0));

	int i = 0;
	int nb = gen_number(2, 4, 2);
	
	while (i < 2)
	{
		while (1)
		{
			int x = gen_number(0, board->size - 1, 1);
			int y = gen_number(0, board->size - 1, 1);
			if (board->grid[x][y] == 0)
			{
				board->grid[x][y] = nb;
				i++;
				break ;
			}
		}
	}
	return (true);
}

int gen_number(int min_nb, int max_nb, int modulo)
{
	int res = 0;

	while (1)
	{
		res = rand() % (max_nb + 1 - min_nb) + min_nb;
		if (res != 0 && res % modulo == 0)
			break ;
	}
	return (res);
}
