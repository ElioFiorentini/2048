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
#define INVERSE_COLORS(print) \
	do {\
		attron(A_REVERSE);\
		(print);\
		attroff(A_REVERSE);\
	} while (0)
#define COLOR(color, print) \
	do {\
		attron(COLOR_PAIR(color));\
		(print);\
		attroff(COLOR_PAIR(color));\
	} while (0)

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

static void	display_cell_border(int x, int y, const size_t CELL_WIDTH, const size_t CELL_HEIGHT)
{
	attron(COLOR_PAIR(BOARD_WALL_COLOR));
	for (size_t i = 0; i < CELL_WIDTH; i++)
	{
		mvaddch(y, x + i, ' ');
		mvaddch(y + CELL_HEIGHT - 1, x + i, ' ');
	}
	for (size_t i = 0; i < CELL_HEIGHT; i++)
	{
		for (size_t j = 0; j < 2; j++)
		{
			mvaddch(y + i, x + j, ' ');
			mvaddch(y + i, x + j + CELL_WIDTH - 2, ' ');
		}
	}
	attroff(COLOR_PAIR(BOARD_WALL_COLOR));
}

static void	display_cell_number(int nb, int x, int y, const size_t CELL_WIDTH, const size_t CELL_HEIGHT)
{
	if (nb <= 0)
		return ;
	size_t len = nbrlen(nb);
	size_t text_width = 3 * len + (len - 1);
	size_t text_size = (text_width + 3 * len > CELL_WIDTH - 4)? 1: 2;
	if (text_size == 2)
		text_width += 3 * len;
	int x_pos = x + CELL_WIDTH / 2;
	int y_pos = y + CELL_HEIGHT / 2;
	if (text_width > CELL_WIDTH - 4 || CELL_HEIGHT - 2 < 5)
		mvprintw(y_pos, x_pos - len / 2, "%d", nb);
	else
		COLOR(COLOR_YELLOW, print_number(x_pos, y_pos, nb, text_size));
}

static size_t	max(size_t size1, size_t size2)
{
	if (size1 > size2)
		return (size1);
	return (size2);
}

void	display_board(t_board *board)
{
	const size_t	H_PADDING = 0;//COLS * 0.3;
	const size_t	V_PADDING = 0;//LINES * 0.10;
	const size_t	CELL_WIDTH = max((COLS - H_PADDING) / board->size + 1, MIN_CELL_WIDTH);
	const size_t	CELL_HEIGHT = max((LINES - V_PADDING) / board->size + 1, MIN_CELL_HEIGHT);
	int	y = V_PADDING / 2;
	for (size_t i = 0; i < board->size; i++)
	{
		int	x = H_PADDING / 2;
		for (size_t j = 0; j < board->size; j++)
		{
			display_cell_border(x, y, CELL_WIDTH, CELL_HEIGHT);
			display_cell_number(board->grid[i][j], x, y, CELL_WIDTH, CELL_HEIGHT);
			x += CELL_WIDTH - 2;
		}
		y += CELL_HEIGHT - 1;
	}
}

int	display_main_menu(t_font *font)
{
	char *logo_str = "2048";
	int xlogo = COLS / 2 - ft_strlen(logo_str) * FONT_WIDTH;
	int ylogo = LINES / 4;

	char *s1 = "4x4 board";
	int x1 = COLS / 2 - ft_strlen(s1) / 2;
	int y1 = LINES - LINES / 3;

	char *s2 = "5x5 board";
	int x2 = COLS / 2 - ft_strlen(s2) / 2;
	int y2 = y1 + 2;

	int selected_choice = 4;
	while (true)
	{
		erase();
		COLOR(COLOR_YELLOW, print(font, xlogo, ylogo, logo_str));
		if (selected_choice == 4)
			INVERSE_COLORS(mvprintw(y1, x1, "%s", s1));
		else
			mvprintw(y1, x1, "%s", s1);
		if (selected_choice == 5)
			INVERSE_COLORS(mvprintw(y2, x2, "%s", s2));
		else
			mvprintw(y2, x2, "%s", s2);
		refresh();
		int k = getch();
		if (k == 'q' || k == KEY_ESCAPE)
			return (ERR);
		if (k == KEY_UP || k == KEY_DOWN)
			selected_choice = (selected_choice + 1) % 2 + 4;
		if (k == '\n' || k == ' ')
			return (selected_choice);
	}
	return (ERR);
}
