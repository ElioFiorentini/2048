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

static void	display_cell(int nb, int x, int y)
{
	const size_t CELL_WIDTH = BOARD_CELL_SIZE * 2;
	const size_t CELL_WALL_WIDTH = BOARD_CELL_WALL_SIZE * 2;

	attron(COLOR_PAIR(BOARD_WALL_COLOR));
	// top border
	for (size_t i = 0; i < CELL_WIDTH; i++)
		for (size_t j = 0; j < BOARD_CELL_WALL_SIZE; j++)
			mvaddch(y + j, x + i, ' ');
	// bottom border
	for (size_t i = 0; i < CELL_WIDTH; i++)
		for (size_t j = 0; j < BOARD_CELL_WALL_SIZE; j++)
			mvaddch(y + BOARD_CELL_SIZE - j - 1, x + i, ' ');
	// left border
	for (size_t i = 0; i < BOARD_CELL_SIZE; i++)
		for (size_t j = 0; j < CELL_WALL_WIDTH; j++)
			mvaddch(y + i, x + j, ' ');
	// right border
	for (size_t i = 0; i < BOARD_CELL_SIZE; i++)
		for (size_t j = 0; j < CELL_WALL_WIDTH; j++)
			mvaddch(y + i, x + CELL_WIDTH - j - 1, ' ');
	attroff(COLOR_PAIR(BOARD_WALL_COLOR));
	if (nb > 0)
		mvprintw(y + BOARD_CELL_SIZE / 2, x + BOARD_CELL_SIZE - 1, "%d", nb);
}

void	display_board(t_board *board)
{
	const size_t CELL_WIDTH = BOARD_CELL_SIZE * 2 - BOARD_CELL_WALL_SIZE * 2;
	const size_t CELL_HEIGHT = BOARD_CELL_SIZE - BOARD_CELL_WALL_SIZE;
	int	x = COLS / 2 - (CELL_WIDTH * board->size) / 2;
	int	y = LINES / 2 - (CELL_HEIGHT * board->size) / 2;
	for (size_t j = 0; j < board->size; j++)
		for (size_t i = 0; i < board->size; i++)
			display_cell(board->board[i][j], x + i * CELL_WIDTH, y + j * CELL_HEIGHT);
}
