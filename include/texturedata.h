/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturedata.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:20:38 by nrey              #+#    #+#             */
/*   Updated: 2025/10/07 14:20:59 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTUREDATA_H
# define TEXTUREDATA_H

typedef struct s_texturedata
{
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texturedata;

#endif
