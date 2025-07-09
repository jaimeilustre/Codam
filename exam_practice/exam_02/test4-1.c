/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test4-1.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/30 16:03:00 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/07/04 10:53:04 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

typedef struct s_node
{
	int	data;
	struct s_node *left;
	struct s_node *right;
} t_node;

/*Creating a new node*/
t_node	*new_node(int data)
{
	t_node *new = malloc(sizeof(t_node));
	if (!new)
		exit(1);
	new->data = data;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

/*Inserting a value into the Binary Search Tree*/
void insert_node(t_node **root, int data)
{
	if (!*root)
		*root = new_node(data);
	else if (data < (*root)->data)
		insert_node(&(*root)->left, data);
	else
		insert_node(&(*root)->right, data);
}

/*Searching a value in the Binary Search Tree*/
int	search(t_node *root, int data)
{
	if (!root)
		return (0);
	if (root->data == data)
		return (1);
	else if (data < root->data)
		return (search(root->left, data));
	else
		return (search(root->right, data));
}

/*Measures the height of the tree by asking each node what its height is*/
int	maxDepth(t_node *root)
{
	if (!root)
		return (0);
	int left = maxDepth(root->left);
	int	right = maxDepth(root->right);
	return (left > right ? left : right) + 1;
}

void	inorder(t_node *root)
{
	if (!root)
		return ;
	inorder(root->left);
	printf("%d ", root->data);
	inorder(root->right);
}

void	mirror(t_node *root)
{
	if (!root)
		return ;
	t_node *temp = root->left;
	root->left = root->right;
	root->right = temp;
	mirror(root->left);
	mirror(root->right);
}

int	countNodes(t_node *root)
{
	if (!root)
		return (0);
	return (1 + countNodes(root->left) + countNodes(root->right));
}

void	freeTree(t_node *root)
{
	if (!root)
		return ;
	freeTree(root->left);
	freeTree(root->right);
	free(root);
}

// int main(void)
// {
// 	t_node *root = NULL;
	
// 	int nbs[] = {8, 3, 10, 1, 6, 14, 4};
// 	for (int i = 0; i < 7; i++)
// 		insert_node(&root, nbs[i]);
		
// 	printf("Inorder traversal: ");
//     inorder(root);  // should print sorted: 1 3 4 6 8 10 14
//     printf("\n");

//     printf("Search for 6: %d\n", search(root, 6));  // should be 1
//     printf("Search for 99: %d\n", search(root, 99)); // should be 0

//     printf("Tree depth: %d\n", maxDepth(root));  // should be 4
//     printf("Node count: %d\n", countNodes(root)); // should be 7

//     mirror(root);
//     printf("Mirrored inorder: ");
//     inorder(root);  // now prints in reverse
	
// 	freeTree(root);
// 	return (0);
// }

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <list of integers>\n", argv[0]);
		return (1);
	}

	t_node *root = NULL;
	for (int i = 1; i < argc; i++)
		insert_node(&root, atoi(argv[i]));
	
	printf("Inorder traversal: ");
	inorder(root);
	printf("\n");

	printf("Search for 6: %d\n", search(root, 6));
	printf("Search for 99: %d\n", search(root, 99));
	printf("Tree depth: %d\n", maxDepth(root));
	printf("Node count: %d\n", countNodes(root));

	mirror(root);
	printf("Mirrored inorder: ");
	inorder(root);
	printf("\n");

	freeTree(root);
	return (0);
}

