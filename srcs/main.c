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

bool	set_up_ncurses(void)
{
	initscr();
	curs_set(0);
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	if (has_colors() == FALSE)
		return (false);
	start_color();
	if (!can_change_color())
		return (false);
	init_all_color_pair();
	return (true);
}

int	clean_up_ncurses(int status)
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
	// fill_start_numbers(&board);
	board.grid[1][0] = 2;
	if (!set_up_ncurses())
		return (clean_up_ncurses(EXIT_FAILURE));
	game_loop(&board);
	return (clean_up_ncurses(EXIT_SUCCESS));
}
