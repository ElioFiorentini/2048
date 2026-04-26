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

#include <stdbool.h>
#include <stdlib.h>
#include <ncurses.h>

static void	fill_pos(int *pos, int index);
static int	get_index(int* pos);
static void sort_pos(int* pos);
static bool	have_pos(int *pos);
static void	reset_pos(int* pos);
static bool add_line(t_board *board, int l);
static bool add_column(t_board *board, int c);
static bool	reverse_line(int* line, int size);
static bool	reverse_column(t_board *board, int c);
static bool	tighten_side_grid(t_board* board, bool move_right);
static bool	tighten_verticality_grid(t_board* board, bool move_bottom);

bool	check_horizontal_game_over(t_board *board)
{
	for (size_t i = 0; i < board->size; i++)
	{
		for (size_t j = 0; j < board->size; j++)
		{
			if (board->grid[i][j] == board->grid[i][j + 1])
				return (false);
		}
	}
	return (true);
}

bool	check_vertical_game_over(t_board *board)
{
	for (size_t i = 0; i < board->size; i++)
	{
		for (size_t j = 0; j < board->size; j++)
		{
			if (board->grid[i][j] == board->grid[i + 1][j])
				return (false);
		}
	}
	return (true);
}

bool	is_game_over(t_board *board)
{
	if (board->empty_case == 0)
	{
		if (check_horizontal_game_over(board) == true && check_vertical_game_over(board) == true)
			return (true);
	}
	return (false);
}

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
	int pos[3];
	pos[0] = -1;
	pos[1] = -1;
	pos[2] = -1;
	size_t x = 0;
	size_t y = 0;

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
	int pos[3];
	pos[0] = -1;
	pos[1] = -1;
	pos[2] = -1;
	size_t x = 0;
	size_t y = 0;

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

static void	fill_pos(int* pos, int index)
{
	for (int i = 0; i < 3; i++)
	{
		if (pos[i] == -1)
		{
			pos[i] = index;
			sort_pos(pos);
			break ;
		}
	}
}

static int get_index(int* pos)
{
	for (int i = 0; i < 3; i++)
	{
		if (pos[i] != -1)
		{
			int index = pos[i];
			pos[i] = -1;
			return (index);
		}
	}
	return (0);
}

static void sort_pos(int* pos)
{
	int i = 1;

	while (i < 3)
	{
		if (pos[i - 1] > pos[i])
		{
			int temp = pos[i];
			pos[i] = pos[i - 1];
			pos[i - 1] = temp;
		}
		i++;
	}
}

static bool	have_pos(int *pos)
{
	int i = 0;

	while (i < 3)
	{
		if (pos[i] != -1)
			return (true);
		i++;
	}
	return (false);
}

static void	reset_pos(int* pos)
{
	int i = 0;

	while (i < 3)
	{
		pos[i] = -1;
		i++;
	}
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
			if (board->grid[i - 1][c] == 2048)
				printf("Victory !\n");
			board->grid[i][c] = 0;
			res = true;
		}
		i++;
	}
	return (res);
}

static bool	reverse_column(t_board *board, int c)
{
	size_t i = 0;
	while (i < board->size / 2) 
	{
		int temp = board->grid[i][c];
		board->grid[i][c] = board->grid[board->size - i - 1][c];
		board->grid[board->size - i - 1][c] = temp;
		i++;
	}
	return (true);
}

static bool	reverse_line(int* line, int size)
{
	int i = 0;
	while (i < size / 2) 
	{
		int temp = line[i];
		line[i] = line[size - i - 1];
		line[size - i - 1] = temp;
		i++;
	}
	return (true);
}

// bool	game_loop(t_board* board)
// {
// 	bool	running = true;
// 	erase();
// 	display_board(board);
// 	while (running)
// 	{
// 		int k = getch();
// 		while (k != ERR)
// 		{
// 			if (k == KEY_LEFT)
// 				move_left(board);
// 			if (k == 'q' || k == KEY_ESCAPE)
// 			{
// 				running = false;
// 				break;
// 			}
// 			// if (fill_nb_rd_place(board) == false)
// 			// 	return (clean_up_ncurses(EXIT_SUCCESS));
// 			k = getch();
// 		}
// 		// erase();
// 		// refresh();
// 		// display_board(board);
// 		print_simple_grid(board->grid);
// 	}
// 	// refresh();
// 	// erase();
// 	return (false);
// }

bool	game_loop(t_board *board)
{
	int		c;
	bool	running;

	running = true;
	while (running)
	{
		print_simple_grid(board);
		printf("after print grid\n");
		printf("Commande (a=left, d=right, w=up, s=down, q=quit) : ");
		c = getchar();

		if (c == 'a')
		{
			if (move_side(board, false) == true)
				fill_nb_rd_place(board);
		}
		else if (c == 'd')
		{
			if (move_side(board, true) == true)
				fill_nb_rd_place(board);

		}
		else if (c == 'w')
		{
			if (move_verticality(board, false) == true)
				fill_nb_rd_place(board);
		}
		else if (c == 's')
		{
			if (move_verticality(board, true) == true)
				fill_nb_rd_place(board);
		}
		else if (c == 'q')
			running = false;
			// return (clean_up_ncurses(EXIT_SUCCESS));
		if (is_game_over(board) == true)
		{
			printf("Game over\n");
			return (false);
		}
		while (c != '\n' && c != EOF)
			c = getchar();

		printf("\n");
	}
	return (false);
}
