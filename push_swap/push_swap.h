/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/19 11:22:09 by jilustre      #+#    #+#                 */
/*   Updated: 2024/11/20 16:41:52 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stdlib.h>
#include <stdio.h>
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

void	print_list(t_list *list);
void	free_list(t_list *list);

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

#endif