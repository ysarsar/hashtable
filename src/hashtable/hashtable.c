/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrxy <mrxy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 17:57:11 by ysarsar           #+#    #+#             */
/*   Updated: 2020/10/30 06:34:32 by mrxy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

t_hash			*ht_create(void)
{
	t_hash		*hashtable;
	int			i;

	// allocate table;
	hashtable = (t_hash*)ft_memalloc(sizeof(t_hash));

	// allocate table list
	hashtable->list = (t_ht**)ft_memalloc(sizeof(t_ht*) * TABLE_SIZE);
	// set each to null (needed for proper operation)
	i = -1;
	while (++i < TABLE_SIZE)
		hashtable->list[i] = NULL;
	return (hashtable);
}

t_ht		*ht_insert(char *str, char **tabs)
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

char		*ft_hashtable(char **args, char **tabs, t_hash **h_table)
{
	unsigned	int	slot;
	t_ht		*current;
	t_ht		*prev;
	t_hash		*hashtable;

	hashtable = *h_table;
	slot = hash_function(args[0]);

	// try to lookup an entry set
	current = hashtable->list[slot];

	// no entry means slot empty, insert immediately
	if (current == NULL)
	{
		hashtable->list[slot] = ht_insert(args[0], tabs);
		if (hashtable->list[slot])
			return (hashtable->list[slot]->value);
		return (NULL);
	}

	// walk trough each entry until either the end is reached or a matching key is found
	while (current)
	{
		// check key
		if (ft_strcmp(current->key, args[0]) == 0)
		{
			// increment hits
			hashtable->list[slot]->hits += 1;
			return (hashtable->list[slot]->value);
		}
		// walk to next
		prev = current;
		current = current->next;
	}
	prev->next = ht_insert(args[0], tabs);
	return (hashtable->list[slot]->value);
}

void		ft_hash(char **args, t_hash **h_table) // must continue this func!!!!!!!!!!!
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
		{
			ft_putstr_fd("42sh: hash: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putendl_fd(": invalid option", 2);
			ft_putendl_fd("42sh: usage: hash [-lr] [-p pathname] [-dt] [name ...]", 2);
		}
	}
	else
		aff_hashtable(h_table);
}