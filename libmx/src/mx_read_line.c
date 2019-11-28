#include "libmx.h"

int mx_read_line(char **lineptr, int buf_size, char delim, const int fd) { 
    int sz = 0; 
    int char_index; 
    size_t readedbytes = 0; 
    char *buffer = mx_strnew(buf_size); 
    static char *str = NULL; 
    bool flag = false; 
 
    if (str != NULL) { 
        while (*str) { 
            if (*str != delim) { 
                mx_strncat(*lineptr, str++, 1); 
                readedbytes++; 
            } 
            else { 
                flag = true; 
                str++; 
                break; 
            } 
        } 
    } 
    while (!flag && (sz = read(fd, buffer, buf_size)) > 0) { 
        char_index = mx_get_char_index(buffer, delim); 
        if (char_index >= 0) { 
            mx_strncat(*lineptr, buffer, char_index); 
            str = (str ? mx_strcpy(str, buffer + char_index + 1) 
                       : mx_strdup(buffer + char_index + 1)); 
            readedbytes += char_index; 
            break; 
        } 
        else { 
            mx_strcat(*lineptr, buffer); 
            readedbytes += sz; 
        } 
        mx_memset(buffer, 0, buf_size); 
    } 
    mx_strdel(&buffer); 
    return (int)readedbytes; 
}
