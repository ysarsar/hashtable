/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrxy <mrxy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 04:06:48 by ysarsar           #+#    #+#             */
/*   Updated: 2020/10/24 23:40:12 by mrxy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

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

static	int		hash_function(char *str)
{
	int		i;
    int		p;
    int		p_pow;
    int		hash_value;

    i = -1;
    hash_value = 0;
    p_pow = 1;
    p = 31;
    while (str[++i])
    {
        hash_value = (hash_value + (str[i] - 'a' + 1) * p_pow) % TABLE_SIZE;
        p_pow = (p_pow * p) % TABLE_SIZE; 
    }
    return (hash_value);
}

static	t_ht	*ht_insert(char *str, char **tabs)
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

static	void	aff_hashtable(t_hash **h_table)
{
	t_hash	*hashtable;
	t_ht	*current;
	int		i;
	int		c;

	hashtable = *h_table;
	i = 0;
	c = 0;
	while (++i < TABLE_SIZE)
	{
		current = hashtable->list[i];
		if (current)
		{
			while (current)
			{
				if (!c)
					printf("hits    command\n");
				printf("   %d    %s\n", current->hits, current->value);
				c++;
				current = current->next;
			}
		}
	}
	if (!c)
		ft_putendl_fd("21sh: hash table empty", 2);
}

static	t_ht	*del_list(t_ht **list)// seg heeere !!!!!!!
{
	t_ht		*current = NULL;
	t_ht		*head = NULL;
	t_ht		*next;

	current = *list;
	if (current && current->hits != 0)
	{

		next = current->next;
		ft_strdel(&current->key);
		ft_strdel(&current->value);
		free(current);
		current = next;
	}
	head = current;
	while (current)
	{
		if (current->next && current->next->hits != 0)
		{
			next = current->next->next;
			ft_strdel(&current->key);
			ft_strdel(&current->value);
			free(current->next);
			current = next;
		}
		current = current->next;
	}
	return (head);
}

static	void	delete_hashtable(t_hash **h_table) //seg heeeere !!!!!
{
	int		i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		if ((*h_table)->list[i])
			(*h_table)->list[i] = del_list(&(*h_table)->list[i]);
		i++;
	}
}

static	void	reset_hits(char **args, t_hash **h_table)
{
	t_hash		*hashtable;
	t_ht		*current;
	int			i;
	int			slot;

	hashtable = *h_table;
	i = 1;
	while (args[++i])
	{
		slot = hash_function(args[i]);
		current = hashtable->list[slot];
		while (current)
		{
			if (ft_strcmp(args[i], current->key) == 0)
			{
				current->hits = 0;
				break ;
			}
			current = current->next;
		}
		if (!current)
			printf("42sh: hash: %s: not found\n", args[i]);
	}
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
			delete_hashtable(h_table);
		}
	}
	else
		aff_hashtable(h_table);
}