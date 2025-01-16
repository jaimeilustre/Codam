/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/19 11:22:09 by jilustre      #+#    #+#                 */
/*   Updated: 2025/01/16 16:39:39 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "libft/libft.h"

typedef struct s_list
{
	int				content;
	struct s_list	*next;	
}					t_list;

typedef struct s_chunk_data
{
	t_list	**a;
	t_list	**b;
	int		total_elements;
	int		**chunks;
	int		*chunk_count;	
}				t_chunk_data;

t_list	*ft_lstnew(int content);
void	ft_lstadd_front(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst);

void	sa(t_list **a, int output_flag);
void	sb(t_list **b, int output_flag);
void	ss(t_list **a, t_list **b, int output_flag);
void	pa(t_list **a, t_list **b, int output_flag);
void	pb(t_list **a, t_list **b, int output_flag);
void	ra(t_list **a, int output_flag);
void	rb(t_list **b, int output_flag);
void	rr(t_list **a, t_list **b, int output_flag);
void	rra(t_list **a, int output_flag);
void	rrb(t_list **b, int output_flag);
void	rrr(t_list **a, t_list **b, int output_flag);

int		check_valid_int(const char *str);
int		check_duplicate_int(t_list *stack);
void	free_split(char **split_array);
void	parse_arguments_to_int(char *arg, t_list **stack);
void	split_and_parse(char *arg, t_list **stack);
t_list	*parse_arguments(int argc, char **argv);

void	exit_error(t_list **a, t_list **b, int *chunks);

void	rotate_to_top(t_list **a, int index);
int		has_target_in_chunk(t_list *a, int chunk_min, int chunk_max);
int		calculate_distance(int index, int size);
int		find_closest(t_list *a, int chunk_min, int chunk_max);

void	calc_chunks(t_chunk_data *data, int **sorted_values, int *chunk_size);
void	allocate_chunks(t_chunk_data *data, int *sorted_values, int chunk_size);
void	process_chunks(t_chunk_data *data);
void	create_chunks(t_chunk_data *data);

int		ft_lstsize(t_list *lst);
int		find_min(t_list *stack);
int		find_max(t_list *stack);
int		calculate_rotation_cost(t_list *stack, int target);

void	quick_sort(int *array, int left, int right);
int		partition(int *array, int left, int right);
int		*stack_to_sorted_array(t_list *a, int size);

void	rotate_to_best_target(t_list **a, t_list **b, int best_target);
void	push_min_cost_element(t_list **a, t_list **b);
void	push_to_b(t_list **a, t_list **b, int chunk_min, int chunk_max);
void	sort_b_to_a(t_list **a, t_list **b);

int		find_index(t_list *a, int value);
void	sort_two_or_three(t_list **a);
void	sort_four_or_five(t_list **a, t_list **b);
void	sort_small_stack(t_list **a, t_list **b);

void	push_swap(t_list **a, t_list **b, int total_elements);
int		is_sorted(t_list *a);
int		main(int argc, char **argv);

#endif