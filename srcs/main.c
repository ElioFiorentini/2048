/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efiorent <efiorent@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 12:05:40 by efiorent          #+#    #+#             */
/*   Updated: 2026/04/25 17:56:22 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "board.h"
#include "display.h"

#include <ncurses.h>
#include <stdlib.h>

static bool	set_up_ncurses(void)
{
	initscr();
	curs_set(0);
	nodelay(stdscr, TRUE);
	if (has_colors() == FALSE)
		return (false);
	start_color();
	if (!can_change_color())
		return (false);
	init_all_color_pair();
	return (true);
}

static int	clean_up_ncurses(int status)
{
	curs_set(1);
	nodelay(stdscr, FALSE);
	endwin();
	return (status);
}

int	main(void)
{
	t_board	board;

	init_board(&board, 4);
	fill_start_numbers(&board);
	if (!set_up_ncurses())
		return (clean_up_ncurses(EXIT_FAILURE));
	erase();
	display_board(&board);
	while (1)
	{
		int k = getch();
		if (k != ERR)
        {
			if (k == KEY_LEFT)
				move_left(&board);
			if (fill_nb_rd_place(&board) == false)
				return (clean_up_ncurses(EXIT_SUCCESS));
            while (getch() != ERR)
                ;
        }
		erase();
		display_board(&board);
		mvprintw(1, 1, "%d\n", (int)board.empty_case);
		refresh();
	}
	erase();
	return (clean_up_ncurses(EXIT_SUCCESS));
}
