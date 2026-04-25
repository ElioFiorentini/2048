/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efiorent <efiorent@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 13:10:12 by efiorent          #+#    #+#             */
/*   Updated: 2026/04/25 14:04:33 by efiorent         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H
# include "board.h"
# include <ncurses.h>
# ifndef BOARD_CELL_SIZE
#  define BOARD_CELL_SIZE 10
# endif
# ifndef BOARD_CELL_WALL_SIZE
#  define BOARD_CELL_WALL_SIZE 1
# endif
# define BOARD_WALL_COLOR COLOR_BLUE
# define BOARD_NUMBER_COLOR COLOR_YELLOW

void	init_all_color_pair();
void	display_board(t_board *board);

#endif
