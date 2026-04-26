/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efiorent <efiorent@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 12:05:40 by efiorent          #+#    #+#             */
/*   Updated: 2026/04/26 16:20:35 by lud-adam         ###   ########.fr       */
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
	//nodelay(stdscr, TRUE);
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
	//nodelay(stdscr, FALSE);
	endwin();
	return (status);
}

int	main(void)
{
	t_font	font;
	t_board	board;

	load_font(&font);
	if (!set_up_ncurses())
		return (clean_up_ncurses(EXIT_FAILURE));
	while (true)
	{
		int selected_choice = display_main_menu(&font);
		if (selected_choice != 4 && selected_choice != 5)
			return (clean_up_ncurses(EXIT_SUCCESS));
		init_board(&board, selected_choice);
		fill_start_numbers(&board);
		if (game_loop(&board, &font) != OK)
			return (clean_up_ncurses(EXIT_SUCCESS));
	}
	return (clean_up_ncurses(EXIT_SUCCESS));
}
