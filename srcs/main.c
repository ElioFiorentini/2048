/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efiorent <efiorent@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 12:05:40 by efiorent          #+#    #+#             */
/*   Updated: 2026/04/25 14:00:50 by efiorent         ###   ########lyon.fr   */
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
	endwin();
	return (status);
}

int	main(void)
{
	t_board	board;

	init_board(&board, 4);
	if (!set_up_ncurses())
		return (clean_up_ncurses(EXIT_FAILURE));
	erase();
	display_board(&board);
	refresh();
	getch();
	return (clean_up_ncurses(EXIT_SUCCESS));
}
