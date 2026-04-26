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
# include "font.h"
# include <ncurses.h>
# define MIN_CELL_WIDTH 8
# define MIN_CELL_HEIGHT 3
# define BOARD_WALL_COLOR COLOR_BLUE
# define BOARD_NUMBER_COLOR COLOR_YELLOW

void	init_all_color_pair();
void	display_board(t_board *board);
int		display_main_menu(t_font *font);

#endif
