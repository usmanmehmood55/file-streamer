#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "file_streamer.h"

void main()
{
    // read the file and store it in an array of strings
    struct file_lines_t file_lines = read_lines("data.csv");

    // print the contents of the array
    for (uint32_t i = 0; i < file_lines.count; i++)
    {
        printf("%s\n", file_lines.lines[i]);
    }
}