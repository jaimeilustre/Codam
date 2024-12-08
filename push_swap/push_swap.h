/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/19 11:22:09 by jilustre      #+#    #+#                 */
/*   Updated: 2024/12/08 11:56:03 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include "libft/libft.h"

typedef struct s_list
{
	int				content;
	struct s_list	*next;	
}					t_list;

t_list *ft_lstnew(int content);
void	ft_lstadd_front(t_list **lst, t_list *new);
t_list *ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst);
int		ft_lstsize(t_list *lst);
int		is_sorted(t_list *stack);

void	sa(t_list **a);
void	sb(t_list **b);
void	ss(t_list **a, t_list **b);
void	pa(t_list **a, t_list **b);
void	pb(t_list **a, t_list **b);
void	ra(t_list **a);
void	rb(t_list **b);
void	rr(t_list **a, t_list **b);
void	rra(t_list **a);
void	rrb(t_list **b);
void	rrr(t_list **a, t_list **b);

int		check_valid_int(const char *str);
int		check_duplicate_int(t_list *stack);
t_list	*parse_arguments(int argc, char **argv);
int		find_min(t_list *stack);
int		find_max(t_list *stack);

void	create_chunks(int total_elements, int **chunks, int *chunk_count);
int		calculator_rotation_cost(t_list *stack, int target);
// int		find_rotation(t_list *stack, int target);
void	push_to_b(t_list **a, t_list **b, int chunk_min, int chunk_max);
void	sort_b_to_a(t_list **a, t_list **b);
void	push_min_cost_element(t_list **a, t_list **b, int chunk_min, int chunk_max);
void	push_swap(t_list **a, t_list **b, int total_elements);
void	sort_small_stack(t_list **a);
int		main(int argc, char **argv);

#endif