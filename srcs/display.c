/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efiorent <efiorent@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 12:55:03 by efiorent          #+#    #+#             */
/*   Updated: 2026/04/25 14:29:58 by efiorent         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "board.h"
#include "display.h"
#include "font.h"
#include "libft.h"
#include <ncurses.h>
#include <stddef.h>

#define INIT_COLORS(color) init_pair(color, COLOR_WHITE, color);

void	init_all_color_pair()
{
	INIT_COLORS(COLOR_BLACK);
	INIT_COLORS(COLOR_RED);
	INIT_COLORS(COLOR_GREEN);
	INIT_COLORS(COLOR_YELLOW);
	INIT_COLORS(COLOR_BLUE);
	INIT_COLORS(COLOR_MAGENTA);
	INIT_COLORS(COLOR_CYAN);
	INIT_COLORS(COLOR_WHITE);
}

static void	display_cell_border(int x, int y)
{
	const size_t CELL_SIZE = (COLS > 100) ? CELL_SIZE_L: CELL_SIZE_S;
	const size_t CELL_WIDTH = CELL_SIZE * 2;
	const size_t CELL_WALL_WIDTH = CELL_WALL_SIZE * 2;

	attron(COLOR_PAIR(BOARD_WALL_COLOR));
	// top border
	for (size_t i = 0; i < CELL_WIDTH; i++)
		for (size_t j = 0; j < CELL_WALL_SIZE; j++)
			mvaddch(y + j, x + i, ' ');
	// bottom border
	for (size_t i = 0; i < CELL_WIDTH; i++)
		for (size_t j = 0; j < CELL_WALL_SIZE; j++)
			mvaddch(y + CELL_SIZE - j - 1, x + i, ' ');
	// left border
	for (size_t i = 0; i < CELL_SIZE; i++)
		for (size_t j = 0; j < CELL_WALL_WIDTH; j++)
			mvaddch(y + i, x + j, ' ');
	// right border
	for (size_t i = 0; i < CELL_SIZE; i++)
		for (size_t j = 0; j < CELL_WALL_WIDTH; j++)
			mvaddch(y + i, x + CELL_WIDTH - j - 1, ' ');
	attroff(COLOR_PAIR(BOARD_WALL_COLOR));
}

static void	display_cell_number(int nb, int x, int y, int size)
{
	if (nb <= 0)
		return ;
	const size_t CELL_SIZE = (COLS > 100) ? CELL_SIZE_L: CELL_SIZE_S;
	int len = 0;
	for (int tmp_nb = nb; tmp_nb != 0; tmp_nb /= 10)
		len++;
	int x_pos = x + CELL_SIZE - 1;
	int y_pos = y + CELL_SIZE / 2;
	if (COLS < 100)
		mvprintw(y_pos, x + CELL_SIZE - (len + 1) / 2, "%d", nb);
	else
	{
		attron(COLOR_PAIR(COLOR_YELLOW));
		print_number(x_pos, y_pos, nb, size);
		attroff(COLOR_PAIR(BOARD_WALL_COLOR));
	}
}

void	display_board(t_board *board)
{
	const size_t	CELL_SIZE = (COLS > 100) ? CELL_SIZE_L: CELL_SIZE_S;
	const size_t	CELL_WIDTH = CELL_SIZE * 2 - CELL_WALL_SIZE * 2;
	const size_t	CELL_HEIGHT = CELL_SIZE - CELL_WALL_SIZE;
	int	x = COLS / 2 - (CELL_WIDTH * board->size) / 2;
	int	y = LINES / 2 - (CELL_HEIGHT * board->size) / 2;
	for (size_t j = 0; j < board->size; j++)
		for (size_t i = 0; i < board->size; i++)
			display_cell_border(x + i * CELL_WIDTH, y + j * CELL_HEIGHT);
	for (size_t j = 0; j < board->size; j++)
		for (size_t i = 0; i < board->size; i++)
		{
			int size = (board->grid[i][j] >= 1000)? 1: 2;
			display_cell_number(board->grid[i][j], x + i * CELL_WIDTH, y + j * CELL_HEIGHT, size);
		}
}

int	display_main_menu(t_font *font)
{
	erase();
	int	x = COLS / 2 - ft_strlen("2048") * FONT_WIDTH;
	int	y = LINES / 4;
	attron(COLOR_PAIR(COLOR_YELLOW));
	print(font, x, y, "2048");
	attroff(COLOR_PAIR(COLOR_YELLOW));
	char *s = "Press any key to continue...";
	x = COLS / 2 - ft_strlen(s) / 2;
	y = LINES - y;
	mvprintw(y, x, "%s", s);
	refresh();
	int k = getch();
	if (k == 'q' || k == KEY_ESCAPE)
		return (ERR);
	return (OK);
}
