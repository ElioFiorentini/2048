/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 17:18:51 by lud-adam          #+#    #+#             */
/*   Updated: 2026/04/25 17:42:43 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "board.h"

bool	move_left(t_board* board)
{
	size_t x = 1;
	size_t y = 0;
	while (y < board->size)
	{
		while (x < board->size)
		{
			if (board->grid[y][x] != 0 && board->grid[y][x - 1] == 0)
				board->grid[y][x - 1] = board->grid[y][x];
			x++;
		}
		y++;
		x = 1;
	}
	return (true);
}
