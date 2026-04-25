/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efiorent <efiorent@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 11:54:05 by efiorent          #+#    #+#             */
/*   Updated: 2026/04/25 12:22:48 by efiorent         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOARD_H
# define BOARD_H
# include <stddef.h>

typedef struct s_board
{
	int		board[5][5];
	size_t	size;
}			t_board;

void	init_board(t_board *board, size_t size);

#endif
