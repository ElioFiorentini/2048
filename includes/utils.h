/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efiorent <efiorent@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 18:17:42 by efiorent          #+#    #+#             */
/*   Updated: 2026/04/26 18:19:29 by efiorent         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#ifndef UTILS_H
# define UTILS_H
# include <stddef.h>

void	*ft_memset(void *pointer, int value, size_t count);
size_t	ft_strlen(const char *str);
size_t	max(size_t size1, size_t size2);

#endif
