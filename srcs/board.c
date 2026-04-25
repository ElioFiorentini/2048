/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efiorent <efiorent@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 12:11:26 by efiorent          #+#    #+#             */
/*   Updated: 2026/04/25 12:31:46 by efiorent         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "board.h"
#include <assert.h>
#include <stddef.h>

void	init_board(t_board *board, size_t size)
{
	assert((size >= 4 && size <= 5) && "Invalid board size");
	board->size = size;
	for (size_t i = 0; i < size; i++)
		for (size_t j = 0; j < size; j++)
			board->board[i][j] = 0;
}
