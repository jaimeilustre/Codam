# Libft
Created my own implemenations of standard C functions found in the standard C library.

## Functions

| File | Description |
| -----| ------------|
| **ft_atoi.c** | Converts a string containing a number to an integer |
| **ft_bzero.c** | Sets n bytes of pointer to zero |
| **ft_calloc.c** | Allocates elements * size bytes using malloc and initializes the allocated space to zero |
| **ft_isalnum.c** | Check c if it is an alphanumeric character \[a-zA-Z0-9\] |
| **ft_isalpha.c** | Check c if it is an alphabetic character \[a-zA-Z\] |
| **ft_isascii.c** | Check c if it is an ASCII character |
| **ft_isdigit.c** | Check c if it is an digit character \[0-9\] |
| **ft_isprint.c** | Check c if it is an printable character |
| **ft_itoa.c** | Converts an integer to a string representation of the given number |
| **ft_lstadd_back_bonus.c** | Appends node to the end of the linked list |
| **ft_lstadd_front_bonus.c**| Appends node to the front of the linked list |
| **ft_lstclear_bonus.c** | Clear the nodes of the linked list |
| **ft_lstdelone_bonus.c** | Clear the given node |
| **ft_lstiter_bonus.c** | Iterate through the linked list and apply the function to each node's content |
| **ft_lstlast_bonus.c** | Return the last node of the linked list |
| **ft_lstmap_bonus.c** | Iterate the linked list and apply function on the content of each node and return the results in a new list |
| **ft_lstnew_bonus.c** | Create new list node |
| **ft_lstsize_bonus.c** | Return the size of the linked list |


## Usage
A make configuration file is present and when `make` is run it will compile the code into binaries and store them into library file called `libft.a`.

Run the `make` command to compile it without the bonus parts.
```
make
```
or `make bonus` to include the bonus part of the assignment.
```
make bonus
```
After the library is contructed you can use it by using the follow command.
```
cc main.c -I libft.a
```
> [!NOTE]
> This project was build in a Linux distrubtion (Ubuntu) and requires make, gcc and ar to be installed.
