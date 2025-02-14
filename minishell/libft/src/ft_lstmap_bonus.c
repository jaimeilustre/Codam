/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboon <jboon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:55:17 by jboon             #+#    #+#             */
/*   Updated: 2024/12/02 17:38:56 by jboon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static t_list	*create_node(void *content, void (*del)(void *))
{
	t_list	*node;

	node = ft_lstnew(content);
	if (node == NULL)
		del(content);
	return (node);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*start;

	if (lst == NULL)
		return (NULL);
	start = create_node(f(lst->content), del);
	if (start == NULL)
		return (NULL);
	new = start;
	lst = lst->next;
	while (lst != NULL)
	{
		new->next = create_node(f(lst->content), del);
		new = new->next;
		if (new == NULL)
		{
			ft_lstclear(&start, del);
			return (NULL);
		}
		lst = lst->next;
	}
	return (start);
}
