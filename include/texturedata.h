#ifndef TEXTUREDATA_H
# define TEXTUREDATA_H

typedef struct s_texturedata
{
    char    *data;
    int     width;
    int     height;
    int     bpp;
    int     line_len;
    int     endian;
}   t_texturedata;

#endif
