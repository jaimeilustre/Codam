#include <stdio.h>
#include <stdlib.h>

typedef struct s_list
{
    struct s_list *next;
    void *data;
} t_list;

// Function to reverse the linked list
t_list *reverse_list(t_list *lst)
{
    t_list *prev = NULL;
    t_list *current = lst;
    t_list *next = NULL;

    while (current)
    {
        next = current->next; // Store next node
        current->next = prev; // Reverse the link
        prev = current;       // Move prev to current
        current = next;       // Move to next node
    }
    return prev; // New head of the reversed list
}

// Function to create a new node
t_list *create_node(void *data)
{
    t_list *new_node = (t_list *)malloc(sizeof(t_list));
    if (!new_node)
        return NULL;
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Function to print the linked list
void print_list(t_list *head)
{
    t_list *temp = head;
    while (temp)
    {
        printf("%d -> ", *(int *)temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Example usage
int main()
{
    int a = 1, b = 2, c = 3, d = 4;
    t_list *head = create_node(&a);
    head->next = create_node(&b);
    head->next->next = create_node(&c);
    head->next->next->next = create_node(&d);

    printf("Original list:\n");
    print_list(head);

    head = reverse_list(head);

    printf("Reversed list:\n");
    print_list(head);

    return 0;
}
