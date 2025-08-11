/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estettle <estettle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:06:06 by estettle          #+#    #+#             */
/*   Updated: 2024/10/11 16:18:26 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// libraries
# include <stdlib.h>	// for malloc() and free()
# include <unistd.h> 	// for read()
# include <stdio.h>		// for the EOF macro

// prototypes
char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);

// buffer size default value
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 999
# endif

#endif
