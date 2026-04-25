/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efiorent <efiorent@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 11:54:05 by efiorent          #+#    #+#             */
/*   Updated: 2026/04/25 15:25:27 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOARD_H
# define BOARD_H

# include <stddef.h>
# include <stdbool.h>

typedef struct s_board
{
	int		grid[5][5];
	size_t	size;
}			t_board;

void	init_board(t_board *board, size_t size);
bool	fill_start_numbers(t_board* board);

// DEBUG
bool	print_board(t_board *board);

#endif
