/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efiorent <efiorent@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 14:58:04 by efiorent          #+#    #+#             */
/*   Updated: 2026/04/25 15:44:27 by efiorent         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONT_H
# define FONT_H
# define FONT_WIDTH 8
# define FONT_HEIGHT 14

typedef struct s_font
{
	char	chars[127][FONT_HEIGHT][FONT_WIDTH + 1];
}			t_font;

void	load_font(t_font *font);
void	print_char(t_font *font, int x, int y, int c);
void	print(t_font *font, int x, int y, char *str);
void	print_number(int x, int y, int nb, int size);

#endif
