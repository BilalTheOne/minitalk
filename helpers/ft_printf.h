/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 21:45:06 by bel-barb          #+#    #+#             */
/*   Updated: 2024/03/28 11:48:59 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

int		ft_printf(const char *format, ...);
int		print_char(int c);
int		print_hex(unsigned long n, int c);
int		print_str(char *str);
int		print_num(long n);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);

#endif