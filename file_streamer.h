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

enum file_stream_mode
{
    READ = 'r',
    WRITE = 'w',
    APPEND = 'a'
};

/**
 * @brief Starts a file stream in read mode if the file exists.
 *
 * @param path path to the file.
 * @return FILE* pointer to the file stream.
 */
FILE *stream(const char *path, enum file_stream_mode mode)
{
    // switch to the correct mode
    char *mode_str = NULL;
    switch (mode)
    {
        case READ:
            mode_str = "r";
            break;
        case WRITE:
            mode_str = "w";
            break;
        case APPEND:
            mode_str = "a";
            break;
        default:
            break;
    }

    // open the file
    FILE *_p_file = fopen(path, mode_str);

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
    FILE *file = stream(path, READ);

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

/**
 * @brief Overwrites all the strings in the array to the file.
 * 
 * @param path the path to the file.
 * @param file_lines the struct containing the array of strings and the size of the array.
 */
void write_lines(const char *path, struct file_lines_t file_lines)
{
    // open the file in write mode
    FILE *file = stream(path, WRITE);

    // iterate through the array of strings
    for (uint32_t i = 0; i < file_lines.count; i++)
    {
        // write the string to the file
        fprintf(file, "%s\n", file_lines.lines[i]);
    }

    // close the file stream
    fclose(file);
}

/**
 * @brief Appends all the strings in the array to the file.
 * 
 * @param path the path to the file.
 * @param file_lines the struct containing the array of strings and the size of the array.
 */
void append_lines(const char *path, struct file_lines_t file_lines)
{
    // open the file in append mode
    FILE *file = stream(path, APPEND);

    // iterate through the array of strings
    for (uint32_t i = 0; i < file_lines.count; i++)
    {
        // append the string to the file
        fprintf(file, "%s\n", file_lines.lines[i]);
    }

    // close the file stream
    fclose(file);
}

// function to append a string to the file
void append_line(const char *path, const char *line)
{
    // open the file in append mode
    FILE *file = stream(path, APPEND);
    fprintf(file, "%s\n", line);
    fclose(file);
}

#endif // FILE_STREAMER_H