/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 17:18:51 by lud-adam          #+#    #+#             */
/*   Updated: 2026/04/26 16:17:34 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "board.h"
#include "display.h"
#include "libft.h"

#include <stdbool.h>
#include <stdlib.h>
#include <ncurses.h>

static bool	tighten_side_grid(t_board* board, bool move_right);
static bool add_line(t_board *board, int l);

bool	move_side(t_board* board, bool move_right)
{
	bool	res = false;

	res = tighten_side_grid(board, move_right);
	for (size_t i  = 0; i < board->size; i++)
	{
		if (add_line(board, i) == true)
			res = true;
	}
	if (res == true)
		tighten_side_grid(board, move_right);
	else
		res = tighten_side_grid(board, move_right);
	return (res);
}

static bool	tighten_side_grid(t_board* board, bool move_right)
{
	bool		res = false;
	int			pos[board->size];
	size_t		x = 0;
	size_t		y = 0;

	ft_memset(pos, -1, sizeof(int) * board->size);
	while (y < board->size)
	{
		if (move_right == true)
			reverse_line(board->grid[y], board->size);
		while (x < board->size)
		{
			if (board->grid[y][x] == 0)
				fill_pos(pos, x);		
			else if (board->grid[y][x] != 0 && have_pos(pos) == true)
			{
				int old_x = get_index(pos);
				board->grid[y][old_x] = board->grid[y][x];
				board->grid[y][x] = 0;
				fill_pos(pos, x);
				res = true;
			}
			x++;
		}
		if (move_right == true)
			reverse_line(board->grid[y], board->size);
		y++;
		reset_pos(pos);
		x = 0;
	}
	return (res);
}

static bool	tighten_verticality_grid(t_board* board, bool move_bottom);
static bool add_column(t_board *board, int c);

bool	move_verticality(t_board* board, bool move_bottom)
{
	bool	res = false;

	res = tighten_verticality_grid(board, move_bottom);
	for (size_t i  = 0; i < board->size; i++)
	{
		if (add_column(board, i) == true)
			res = true;
	}
	if (res == true)
		tighten_verticality_grid(board, move_bottom);
	else
		res = tighten_verticality_grid(board, move_bottom);
	return (res);
	
}

static bool	tighten_verticality_grid(t_board* board, bool move_bottom)
{
	bool		res = false;
	int			pos[board->size];
	size_t		x = 0;
	size_t		y = 0;

	ft_memset(pos, -1, sizeof(int) * board->size);
	while (x < board->size)
	{
		if (move_bottom == true)
			reverse_column(board, x);
		while (y < board->size)
		{
			if (board->grid[y][x] == 0)
				fill_pos(pos, y);		
			else if (board->grid[y][x] != 0 && have_pos(pos) == true)
			{
				int old_y = get_index(pos);
				board->grid[old_y][x] = board->grid[y][x];
				board->grid[y][x] = 0;
				fill_pos(pos, y);
				res = true;
			}
			y++;
		}
		if (move_bottom == true)
			reverse_column(board, x);
		x++;
		reset_pos(pos);
		y = 0;
	}
	return (res);
	
}

static bool add_line(t_board *board, int l)
{
	size_t i = 1;	
	bool	res = false;

	while (i < board->size)
	{
		if (board->grid[l][i] != 0 && board->grid[l][i] == board->grid[l][i - 1])
		{
			board->empty_case++;
			board->grid[l][i - 1] *= 2;
			if (board->grid[l][i - 1] == 2048)
				printf("Victory !\n");
			board->grid[l][i] = 0;
			res = true;
		}
		i++;
	}
	return (res);
}

static bool add_column(t_board *board, int c)
{
	size_t i = 1;	
	bool	res = false;

	while (i < board->size)
	{
		if (board->grid[i][c] != 0 && board->grid[i][c] == board->grid[i - 1][c])
		{
			board->empty_case++;
			board->grid[i - 1][c] *= 2;
			// if (board->grid[i - 1][c] == 2048)
				// printf("Victory !\n");
			board->grid[i][c] = 0;
			res = true;
		}
		i++;
	}
	return (res);
}

bool	game_loop(t_board *board)
{
	int		c;
	bool	running;

	running = true;
	while (running)
	{
		erase();
		display_board(board);
		refresh();
		c = getch();

		if (c == 'a' || c == KEY_LEFT)
		{
			if (move_side(board, false) == true)
				fill_nb_rd_place(board);
		}
		else if (c == 'd' || c == KEY_RIGHT)
		{
			if (move_side(board, true) == true)
				fill_nb_rd_place(board);

		}
		else if (c == 'w' || c == KEY_UP)
		{
			if (move_verticality(board, false) == true)
				fill_nb_rd_place(board);
		}
		else if (c == 's' || c == KEY_DOWN)
		{
			if (move_verticality(board, true) == true)
				fill_nb_rd_place(board);
		}
		else if (c == 'q' || c == KEY_ESCAPE)
			running = false;
		if (is_game_over(board) == true)
		{
			erase();
			display_board(board);
			mvprintw(LINES / 2, COLS / 2, "Game Over !");
			refresh();
			while (c != '\n' && c != EOF && c != 'q' && c != KEY_ESCAPE)
				c = getch();
			return (false);
		}
	}
	return (false);
}
