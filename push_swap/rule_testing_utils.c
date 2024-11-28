/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rule_testing_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/20 11:00:40 by jilustre      #+#    #+#                 */
/*   Updated: 2024/11/20 14:57:10 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list	*ft_lstnew(int content)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;
	
	if (!lst || !new)
		return ;
	if (*lst)
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

void	print_list(t_list *list)
{
	while (list)
	{
		printf("%d, ", list->content);
		list = list->next;
	}
	printf("NULL\n");
}

void	free_list(t_list *list)
{
	t_list	*tmp;
	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}
}


