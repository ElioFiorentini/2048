/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_game_over.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 16:02:33 by lud-adam          #+#    #+#             */
/*   Updated: 2026/04/26 16:17:13 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "board.h"

bool	check_vertical_game_over(t_board* board);
bool	check_horizontal_game_over(t_board* board);

bool	is_game_over(t_board* board)
{
	if (board->empty_case == 0)
	{
		if (check_horizontal_game_over(board) == true && check_vertical_game_over(board) == true)
			return (true);
	}
	return (false);
}

bool	check_horizontal_game_over(t_board* board)
{
	for (size_t i = 0; i < board->size; i++)
	{
		for (size_t j = 0; j < board->size - 1; j++)
		{
			if (board->grid[i][j] == board->grid[i][j + 1])
				return (false);
		}
	}
	return (true);
}

bool	check_vertical_game_over(t_board* board)
{
	for (size_t i = 0; i < board->size - 1; i++)
	{
		for (size_t j = 0; j < board->size; j++)
		{
			if (board->grid[i][j] == board->grid[i + 1][j])
				return (false);
		}
	}
	return (true);
}
