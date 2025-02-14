/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:54:48 by quenalla          #+#    #+#             */
/*   Updated: 2025/01/16 22:47:12 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void(*del)(void *))
{
	t_list	*index_list;
	t_list	*noeud;
	void	*set;

	if (!lst || !f || !del)
		return (NULL);
	index_list = NULL;
	while (lst)
	{
		set = f(lst->content);
		noeud = ft_lstnew(set);
		if (!noeud)
		{
			del(set);
			ft_lstclear(&index_list, del);
			return (NULL);
		}
		ft_lstadd_back(&index_list, noeud);
		lst = lst->next;
	}
	return (index_list);
}
