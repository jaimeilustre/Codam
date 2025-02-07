// Assignment name  : ft_list_remove_if
// Expected files   : ft_list_remove_if.c
// Allowed functions: free
// --------------------------------------------------------------------------------

// Write a function called ft_list_remove_if that removes from the
// passed list any element the data of which is "equal" to the reference data.

// It will be declared as follows :

// void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)());

// cmp takes two void* and returns 0 when both parameters are equal.

// You have to use the ft_list.h file, which will contain:

// $>cat ft_list.h
// typedef struct      s_list
// {
//     struct s_list   *next;
//     void            *data;
// }                   t_list;

typedef struct      s_list
{
    struct s_list   *next;
    void            *data;
}                   t_list;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(void *, void *))
{
    t_list *current;
    t_list *prev;
    t_list *temp;

    while (*begin_list && !cmp((*begin_list)->data, data_ref))
    {
        temp = *begin_list;
        *begin_list = (*begin_list)->next;
        free(temp);
    }

    prev = *begin_list;
    if (!prev)
        return;
    current = prev->next;
    
    while (current)
    {
        if (!cmp(current->data, data_ref))
        {
            prev->next = current->next;
            free(current);
            current = prev->next;
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }
}

// // Helper function to create a new node
// t_list *create_node(void *data)
// {
//     t_list *new = malloc(sizeof(t_list));
//     if (!new)
//         return NULL;
//     new->data = data;
//     new->next = NULL;
//     return new;
// }

// // Helper function to print the list
// void print_list(t_list *list)
// {
//     while (list)
//     {
//         printf("%s -> ", (char *)list->data);
//         list = list->next;
//     }
//     printf("NULL\n");
// }

// // Comparison function (strcmp-style)
// int cmp(void *a, void *b)
// {
//     return strcmp((char *)a, (char *)b);
// }

// // Test function
// int main()
// {
//     // Creating a linked list: "apple" -> "banana" -> "cherry" -> "banana" -> NULL
//     t_list *list = create_node("apple");
//     list->next = create_node("banana");
//     list->next->next = create_node("cherry");
//     list->next->next->next = create_node("banana");

//     printf("Before removal:\n");
//     print_list(list);

//     // Remove all occurrences of "banana"
//     ft_list_remove_if(&list, "banana", cmp);

//     printf("After removal:\n");
//     print_list(list);

//     // Free remaining nodes
//     while (list)
//     {
//         t_list *tmp = list;
//         list = list->next;
//         free(tmp);
//     }

//     return 0;
// }
