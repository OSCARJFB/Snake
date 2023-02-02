/*
    Writen by: Oscar Bergström
    https://github.com/OSCARJFB
*/

#ifndef SNAKEDEBUGLOGGER_H
#define SNAKEDEBUGLOGGER_H
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void _LogDebug(char *logRow, ...)
{
    char append_to_file[strlen(logRow)];
    char text_stream[strlen(logRow)];
    int stream_reader = 0, isArgs = 0;

    FILE *DEBUG_FILE = fopen("debug.log", "a");

    va_list arg_ptr;
    va_start(arg_ptr, logRow);

    for (int i = 0; i < strlen(logRow); ++i)
    {
        if (i + 1 < strlen(logRow) && logRow[i] == '%')
        {
            strcpy(append_to_file, text_stream);
            fprintf(DEBUG_FILE, "%s", append_to_file);
            stream_reader = 0;
            isArgs = 1; 

            switch (logRow[i++ + 1])
            {
            case 's':
                fprintf(DEBUG_FILE, "%s", va_arg(arg_ptr, char *));
                break;
            case 'c':
                fprintf(DEBUG_FILE, "%c", va_arg(arg_ptr, int));
                break;
            case 'd':
                fprintf(DEBUG_FILE, "%d", va_arg(arg_ptr, int));
                break;
            default:
                continue;
            }
        }
        else
        {
            text_stream[stream_reader++] = logRow[i];
            text_stream[stream_reader] = '\0';
        }
    }

    va_end(arg_ptr);
    if(!isArgs)
    {
        fprintf(DEBUG_FILE, "%s", logRow);
    }
    fprintf(DEBUG_FILE, "\n");
    fclose(DEBUG_FILE);
    DEBUG_FILE = NULL; 
}

#endif // SNAKEDEBUGLOGGER_H