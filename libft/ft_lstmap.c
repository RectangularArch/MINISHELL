/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilverb <csilverb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 21:04:05 by csilverb          #+#    #+#             */
/*   Updated: 2021/04/29 16:56:20 by csilverb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*new;

	if (!lst)
		return (NULL);
	res = ft_lstnew((f)(lst->content));
	new = res;
	lst = lst->next;
	while (lst)
	{
		res->next = ft_lstnew((f)(lst->content));
		if (!(res->next))
		{
			ft_lstclear(&res, (del));
			return (NULL);
		}
		res = res->next;
		lst = lst->next;
	}
	return (new);
}
