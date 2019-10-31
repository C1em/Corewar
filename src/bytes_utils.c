/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 22:37:58 by coremart          #+#    #+#             */
/*   Updated: 2019/10/07 20:55:51 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		read_bytes(t_byte arr[], int index, int nb_bytes)
{
	unsigned int	res;
	int				i;

	res = 0;
	i = 0;
	if (index < 0)
		index = MEM_SIZE + (index % MEM_SIZE);
	while (i < nb_bytes)
	{
		res = (res << 8) + arr[(index + i) % MEM_SIZE];
		i++;
	}
	return (*(int*)&res);
}

void	write_bytes(t_byte arr[], int index, int nb)
{
	if (index < 0)
		index = MEM_SIZE + (index % MEM_SIZE);
	arr[index % MEM_SIZE] = ((t_byte*)&nb)[3];
	arr[(index + 1) % MEM_SIZE] = ((t_byte*)&nb)[2];
	arr[(index + 2) % MEM_SIZE] = ((t_byte*)&nb)[1];
	arr[(index + 3) % MEM_SIZE] = ((t_byte*)&nb)[0];
}
