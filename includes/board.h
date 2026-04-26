/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efiorent <efiorent@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 11:54:05 by efiorent          #+#    #+#             */
/*   Updated: 2026/04/26 16:11:50 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOARD_H
# define BOARD_H

#define KEY_ESCAPE 27
# include <stddef.h>
# include <stdbool.h>

typedef struct s_board
{
	int		grid[5][5];
	size_t	size;
	size_t	empty_case;
}			t_board;

enum e_const
{
	WIN_VALUE = 2048
};

void	init_board(t_board* board, size_t size);
 
int		clean_up_ncurses(int status);
bool	set_up_ncurses(void);
bool	fill_start_numbers(t_board* board);
bool	fill_nb_rd_place(t_board* board);
bool	game_loop(t_board* board);

//GAME LOGIC UTILS

void	reset_pos(int* pos);
bool	check_horizontal_game_over(t_board *board);
void	sort_pos(int* pos);
int		get_index(int* pos);
void	fill_pos(int* pos, int index);
bool	have_pos(int* pos);
bool	reverse_line(int* line, int size);
bool	reverse_column(t_board* board, int c);

//CHECK
bool	is_game_over(t_board* board);

// DEBUG
void print_simple_grid(t_board* board) ;

#endif
