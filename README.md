# File Streamer

A simple C library made to read a file and store its lines in a string array.

## Background

Reading and printing lines of a file is easy, but storing it in an easily accessible array is not, since C does not allow declaration of an array with a variable size in run-time. This library is made to solve this problem by creating a string array using pointers and dynamically allocating memory for it.

## Usage
File can be read by the following function:

```c
struct file_lines_t read_lines(const char *path)
```

Whereas the struct contains the array of lines and the number of lines in the file.

```c
struct file_lines_t
{
    char **lines;
    uint32_t count;
};
```

## To Do
- Think of a better name for this repo
- Add support for automatic delimiter detection