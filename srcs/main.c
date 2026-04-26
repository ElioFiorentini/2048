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
#include "font.h"
#include <ncurses.h>
#include <stdlib.h>

bool	set_up_ncurses(void)
{
	initscr();
	set_escdelay(25);
	curs_set(0);
	noecho();
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
	echo();
	keypad(stdscr, FALSE);
	endwin();
	return (status);
}

int	main(void)
{
	t_board	board;
	t_font	font;

	init_board(&board, 4);
	// load_font(&font);
	fill_start_numbers(&board);
	// board.grid[1][2] = 32;
	// board.grid[1][3] = 128;
	// if (!set_up_ncurses())
	// 	return (clean_up_ncurses(EXIT_FAILURE));
	// if (display_main_menu(&font) == ERR)
	// 	return (clean_up_ncurses(EXIT_SUCCESS));
	game_loop(&board);
	return (clean_up_ncurses(EXIT_SUCCESS));
}
