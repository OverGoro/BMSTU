#include "str_io.h"
#include "error.h"

int input_str(FILE *f, size_t n, char *str)
{
    char *pbuf = NULL; // Буфер для предварительного чтения и проверки
    
    pbuf = malloc((n + 2) * sizeof(char));
    if (pbuf == NULL)
        return ERR_MEMORY;

    size_t buf_len;

    // Чтение строки
    if (fgets(pbuf, sizeof(char) * (n + 2), f) == NULL)
        return ERR_IO;
   
    buf_len = strlen(pbuf);
    if (pbuf[buf_len - 1] == '\n')
    {
        pbuf[buf_len - 1] = '\0';
        buf_len--;
    }
    if (!buf_len || buf_len > n)
    {
        return ERR_RANGE;
    }
    strncpy(str, pbuf, n);
    if (pbuf != NULL)
        free(pbuf);
    return ERR_OK;
}

