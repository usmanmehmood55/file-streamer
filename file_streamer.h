#ifndef FILE_STREAMER_H
#define FILE_STREAMER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

struct file_lines_t
{
    char **lines;
    uint32_t count;
};

/**
 * @brief Starts a file stream if the file exists and is readable.
 *
 * @param path path to the file.
 * @return FILE* pointer to the file stream.
 */
FILE *stream_file(const char *path)
{
    // open the file in read mode
    FILE *_p_file = fopen(path, "r");

    // check if the file was opened successfully
    if (_p_file == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    return _p_file;
}

/**
 * @brief Counts the number of lines in a file.
 *
 * @param file pointer to the file stream
 * @return uint32_t number of lines in the file
 */
uint32_t file_lines_count(FILE *file)
{
    // variable to store the line count
    uint32_t lines = 0;

    // iterate through every character in the file
    for (char c = 0; (c = fgetc(file)) != EOF;)
    {
        // if the character is a newline, increment the line counter
        if (c == '\n')
            lines++;
    }

    // reset the file pointer to the beginning of the file
    rewind(file);

    return ++lines;
}

/**
 * @brief Reads the contents of a file stream into an array of strings.
 *
 * @param file pointer to the file stream to read from.
 * @return char** pointer to the array of strings.
 */
char **file_lines_to_array(FILE *file)
{
    // get the number of lines in the file
    uint32_t lines_count = file_lines_count(file);

    // pointer to array, by allocating memory the size of that array
    char **lines = malloc(lines_count * sizeof(char *));

    // variable to store a single line of 50 characters
    char this_line[50];

    // stream the file until the end
    for (uint32_t line_number = 0; fgets(this_line, sizeof(this_line), file); line_number++)
    {
        // if the last character is a newline, remove it
        if (this_line[strlen(this_line) - 1] == '\n')
            this_line[strlen(this_line) - 1] = '\0';

        // copy the memory contents of this_line to the memory of current index
        lines[line_number] = malloc(sizeof(this_line));
        strcpy(lines[line_number], this_line);
    }

    // reset the file pointer to the beginning of the file
    rewind(file);

    // close the file stream
    fclose(file);

    return lines;
}

/**
 * @brief Reads the file and returns a struct containing an array of strings
 * and the size of the array.
 *
 * @param path the path to the file.
 * @return struct file_lines_t containing pointer the array of strings and the size of the array.
 */
struct file_lines_t read_lines(const char *path)
{

    // initialize file stream
    FILE *file = stream_file(path);

    // get the number of lines in the file
    uint32_t lines_count = file_lines_count(file);

    // pointer to array, by allocating memory the size of that array
    char **lines = malloc(lines_count * sizeof(char *));

    // variable to store a single line of 50 characters
    char this_line[50];

    // stream the file until the end
    for (uint32_t line_number = 0; fgets(this_line, sizeof(this_line), file); line_number++)
    {
        // if the last character is a newline, remove it
        if (this_line[strlen(this_line) - 1] == '\n')
            this_line[strlen(this_line) - 1] = '\0';

        // copy the memory contents of this_line to the memory of current index
        lines[line_number] = malloc(sizeof(this_line));
        strcpy(lines[line_number], this_line);
    }

    // reset the file pointer to the beginning of the file
    rewind(file);

    // close the file stream
    fclose(file);

    // create a file_lines_t struct and return it
    struct file_lines_t file_lines;
    file_lines.lines = lines;
    file_lines.count = lines_count;
    return file_lines;
}

#endif // FILE_STREAMER_H