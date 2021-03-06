/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 17:57:11 by ysarsar           #+#    #+#             */
/*   Updated: 2020/11/01 06:25:33 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

t_hash			*ht_create(void)
{
	t_hash		*hashtable;
	int			i;

	hashtable = (t_hash*)ft_memalloc(sizeof(t_hash));
	hashtable->list = (t_ht**)ft_memalloc(sizeof(t_ht*) * TABLE_SIZE);
	i = -1;
	while (++i < TABLE_SIZE)
		hashtable->list[i] = NULL;
	return (hashtable);
}

t_ht			*ht_insert(char *str, char **tabs)
{
	t_ht	*entry;
	char	*path;

	path = valid_path(str, tabs);
	entry = NULL;
	if (path)
	{
		entry = (t_ht*)ft_memalloc(sizeof(t_ht));
		entry->key = ft_strdup(str);
		entry->value = path;
		entry->hits = 1;
		entry->next = NULL;
	}
	return (entry);
}

char			*ft_hashtable(char **args, char **tabs, t_hash **h_table)
{
	unsigned	int	slot;
	t_ht			*current;
	t_ht			*prev;
	t_hash			*hashtable;

	hashtable = *h_table;
	slot = hash_function(args[0]);
	current = hashtable->list[slot];
	if (current == NULL)
	{
		hashtable->list[slot] = ht_insert(args[0], tabs);
		if (hashtable->list[slot])
			return (hashtable->list[slot]->value);
		return (NULL);
	}
	while (current)
	{
		if (ft_strcmp(current->key, args[0]) == 0 &&
			++hashtable->list[slot]->hits)
			return (hashtable->list[slot]->value);
		prev = current;
		current = current->next;
	}
	prev->next = ht_insert(args[0], tabs);
	return (hashtable->list[slot]->value);
}

void			ft_hash(char **args, t_hash **h_table)
{
	int			len;

	len = ft_argslen(args);
	if (len > 1)
	{
		if (ft_strcmp(args[1], "-r") == 0)
		{
			reset_hits(args, h_table);
			delete_hashtable(h_table, len);
		}
		else if (ft_strcmp(args[1], "-l") == 0)
			l_flag(h_table, args);
		else if (ft_strcmp(args[1], "-d") == 0)
			d_flag(h_table, args);
		else if (ft_strcmp(args[1], "-t") == 0)
			t_flag(h_table, args);
		else if (ft_strcmp(args[1], "-p") == 0)
			p_flag(h_table, args);
		else if (args[1][0] == '-')
			ft_hash_error(args[1]);
	}
	else
		aff_hashtable(h_table);
}
