/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efiorent <efiorent@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 11:54:05 by efiorent          #+#    #+#             */
/*   Updated: 2026/04/25 17:23:44 by lud-adam         ###   ########.fr       */
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

void	init_board(t_board *board, size_t size);
 
int		clean_up_ncurses(int status);
bool	set_up_ncurses(void);
bool	fill_start_numbers(t_board* board);
bool	fill_nb_rd_place(t_board* board);
bool	game_loop(t_board* board);


// DEBUG
void print_simple_grid(t_board* board) ;

#endif
