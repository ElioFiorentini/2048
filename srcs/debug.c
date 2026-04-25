/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 15:11:08 by lud-adam          #+#    #+#             */
/*   Updated: 2026/04/25 15:15:57 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "board.h"

#include "libft.h"

bool	print_board(t_board *board)
{
	size_t y = 0;
	size_t x = 0;
	while (y < board->size - 1)
	{
		while (x < board->size - 1)
		{
			ft_putnbr_fd(board->grid[y][x], 1);
			x++;
		}
		y++;
	}
	return (true);
}
