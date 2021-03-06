/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_iter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 19:21:23 by vsanta            #+#    #+#             */
/*   Updated: 2019/08/25 19:21:25 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_iter(t_lst *lst, void (*f)(void *data))
{
	while (lst)
	{
		f(lst->data);
		lst = lst->next;
	}
}
