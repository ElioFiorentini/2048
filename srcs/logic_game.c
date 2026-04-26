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
static bool add_line(int *line, int size);
static bool add_column(t_board *board, int c);
static bool	reverse_line(int* line, int size);
static bool	reverse_column(t_board *board, int c);

bool	move_side(t_board* board, bool move_right)
{
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
		add_line(board->grid[y], board->size);
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
			}
			x++;
		}
		if (move_right == true)
			reverse_line(board->grid[y], board->size);
		y++;
		reset_pos(pos);
		x = 0;
	}
	return (true);
}

bool	move_verticality(t_board* board, bool move_bottom)
{
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
		add_column(board,  x);
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
			}
			y++;
		}
		if (move_bottom == true)
			reverse_column(board, x);
		x++;
		reset_pos(pos);
		y = 0;
	}
	return (true);
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

static bool add_line(int *line, int size)
{
	int i = 1;	
	while (i < size)
	{
		if (line[i] == line[i - 1])
		{
			line[i - 1] *= 2;
			if (line[i - 1] == 2048)
				printf("Victory !\n");
			line[i] = 0;
		}
		i++;
	}
	return (true);
}

static bool add_column(t_board *board, int c)
{
	size_t i = 1;	

	while (i < board->size)
	{
		if (board->grid[i][c] == board->grid[i - 1][c])
		{
			board->grid[i - 1][c] *= 2;
			if (board->grid[i - 1][c] == 2048)
				printf("Victory !\n");
			board->grid[i][c] = 0;
		}
		i++;
	}
	return (true);
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
			move_side(board, false);
		else if (c == 'd')
			move_side(board, true);
		else if (c == 'w')
			move_verticality(board, false);
		else if (c == 's')
			move_verticality(board, true);
		else if (c == 'q')
			running = false;
		fill_nb_rd_place(board);
			// return (clean_up_ncurses(EXIT_SUCCESS));

		while (c != '\n' && c != EOF)
			c = getchar();

		printf("\n");
	}
	return (false);
}
