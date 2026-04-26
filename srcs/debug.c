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
#include <stdio.h>

void print_simple_grid(t_board* board) 
{
    for (int i = 0; i < board->size; i++)
    {
        printf("+---+---+---+---+\n");
        
        printf("|");
        for (int j = 0; j < 4; j++)
        {
            if (board->grid[i][j] == 0)
                printf("   |");
            else
                printf(" %d |", board->grid[i][j]);
        }
        printf("\n");
    }
    printf("+---+---+---+---+\n");
}
