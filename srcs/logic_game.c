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
#include "display.h"

#include <stdlib.h>
#include <ncurses.h>

bool	move_left(t_board* board)
{
	size_t x = 0;
	mvprintw(1, 1, "here\n");
	refresh();
	size_t y = 0;
	int old_x, old_y = 0;
	while (y < board->size)
	{
		while (x < board->size)
		{
			if (board->grid[x][y] == 0)
			{
				old_x = x;
				old_y = y;
			}
			else
			{
				board->grid[old_x][old_y] = board->grid[x][y];
				board->grid[x][y] = 0;
				old_x = x;
				old_y = y;
			}
			x++;
		}
		old_x = 0;
		old_y = 0;
		y++;
		x = 0;
	}
	return (true);
}

bool	game_loop(t_board* board)
{
	erase();
	display_board(board);
	while (1)
	{
		int k = getch();
		if (k != ERR)
		{
			if (k == KEY_LEFT)
				move_left(board);
			// if (fill_nb_rd_place(board) == false)
			// 	return (clean_up_ncurses(EXIT_SUCCESS));
            while (getch() != ERR)
                ;
        }
		erase();
		display_board(board);
		refresh();
	}
	refresh();
	erase();
}
