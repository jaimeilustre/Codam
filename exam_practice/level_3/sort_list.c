// Assignment name  : sort_list
// Expected files   : sort_list.c
// Allowed functions:
// --------------------------------------------------------------------------------

// Write the following functions:

// t_list	*sort_list(t_list* lst, int (*cmp)(int, int));

// This function must sort the list given as a parameter, using the function
// pointer cmp to select the order to apply, and returns a pointer to the
// first element of the sorted list.

// Duplications must remain.

// Inputs will always be consistent.

// You must use the type t_list described in the file list.h
// that is provided to you. You must include that file
// (#include "list.h"), but you must not turn it in. We will use our own
// to compile your assignment.

// Functions passed as cmp will always return a value different from
// 0 if a and b are in the right order, 0 otherwise.

// For example, the following function used as cmp will sort the list
// in ascending order:

typedef struct s_list
{
	int     	data;
	struct s_list  *next;
}	t_list;

#include <unistd.h>

t_list	*sort_list(t_list *lst, int (*cmp)(int, int))
{
	t_list	*current;
	int		swapped;
	int		tmp;

	if (!lst)
		return (NULL);

	swapped = 1; // Set to 1 to enter the first loop iteration
	while (swapped)
	{
		swapped = 0;  // Reset swap flag
		current = lst;
		while (current->next)
		{
			if (!cmp(current->data, current->next->data))
			{
				tmp = current->data;
				current->data = current->next->data;
				current->next->data = tmp;
				swapped = 1;  // A swap occurred, so we need another pass
			}
			current = current->next;
		}
	}
	return (lst);
}

// #include <stdio.h>
// #include <stdlib.h>

// // Function to create a new node
// t_list *create_node(int data)
// {
//     t_list *new = malloc(sizeof(t_list));
//     if (!new)
//         return NULL;
//     new->data = data;
//     new->next = NULL;
//     return new;
// }

// // Function to print the linked list
// void print_list(t_list *list)
// {
//     while (list)
//     {
//         printf("%d -> ", list->data);
//         list = list->next;
//     }
//     printf("NULL\n");
// }

// // Comparison function for ascending order
// int ascending(int a, int b)
// {
//     return (a <= b);
// }

// // Test function
// int main()
// {
//     // Creating an unsorted linked list: 3 -> 1 -> 4 -> 2 -> NULL
//     t_list *list = create_node(3);
//     list->next = create_node(1);
//     list->next->next = create_node(4);
//     list->next->next->next = create_node(2);

//     printf("Before sorting:\n");
//     print_list(list);

//     // Sorting the list
//     list = sort_list(list, ascending);

//     printf("After sorting:\n");
//     print_list(list);

//     // Free memory
//     t_list *tmp;
//     while (list)
//     {
//         tmp = list;
//         list = list->next;
//         free(tmp);
//     }

//     return 0;
// }
