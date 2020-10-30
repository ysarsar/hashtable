/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrxy <mrxy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 02:15:49 by mrxy              #+#    #+#             */
/*   Updated: 2020/10/30 06:24:53 by mrxy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

void		l_flag(t_hash **h_table, char **args)
{
	t_hash	*hashtable;
	t_ht	*current;
	int		i;
	int		c;
	int		slot;

	hashtable = *h_table;
	i = -1;
	c = 1;
	slot = -1;
	while (args[++c])
	{
		slot = hash_function(args[c]);
		current = hashtable->list[slot];
		while (current)
		{
			if (ft_strcmp(args[c], current->key) == 0)
				break ;
			current = current->next;
		}
		if (!current)
		{
			ft_putstr_fd("42sh: hash: ", 2);
			ft_putstr_fd(args[c], 2);
			ft_putstr_fd(": not found\n", 2);
		}
	}
	c = 0;
	while (++i < TABLE_SIZE && slot == -1)
	{
		current = hashtable->list[i];
		if (current)
		{
			while (current)
			{
				ft_putstr("builtin hash -p ");
				ft_putstr(current->value);
				ft_putchar(' ');
				ft_putstr(current->key);
				ft_putchar('\n');
				c++;
				current = current->next;
			}
		}
	}
	if (!c && slot == -1)
		ft_putendl_fd("42sh: hash table empty", 2);
}

void		d_flag(t_hash **h_table, char **args)
{
	int		len;

	len = ft_argslen(args);
	if (len > 2)
		del_hash(h_table, args);
	else if (len == 2)
		aff_hashtable(h_table);
}

void		t_flag(t_hash **h_table, char **args)
{
	int		len;

	len = ft_argslen(args);
	if (len > 2)
		search_hash(h_table, args, len);
	else
		ft_putendl_fd("42sh: hash: -t: option requires an argument", 2);
}

void		p_flag(t_hash **h_table, char **args)
{
	int		i;
	int		len;
	int		slot;
	char	path[4096];
	t_hash	*hashtable;
	t_ht	*current;

	len = ft_argslen(args);
	i = 2;
	if (len == 2)
	{
		ft_putendl_fd("42sh: hash: -p: option requires an argument", 2);
		ft_putendl_fd("42sh: usage: hash [-lr] [-p pathname] [-dt] [name ...]", 2);
	}
	else
	{
		ft_strcpy(path, args[2]);
		hashtable = *h_table;
		if (!args[3])
			return (aff_hashtable(h_table));
		while (args[++i])
		{
			slot = hash_function(args[i]);
			current = hashtable->list[slot];
			if (!current)
				hashtable->list[slot] = hash_p_insert(args[i], path);
			else
			{
				while (current)
				{
					if (ft_strcmp(args[i], current->key) == 0)
					{
						free(current->value);
						current->value = ft_strdup(path);
						current->hits = 0;
					}
					current = current->next;
				}
			}
		}
	}
}














