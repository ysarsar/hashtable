/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrxy <mrxy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 18:36:01 by ysarsar           #+#    #+#             */
/*   Updated: 2020/10/30 06:31:19 by mrxy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

void		reset_hits(char **args, t_hash **h_table)
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
		if (!current)
		{
			ft_putstr_fd("42sh: hash: ", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd(": not found", 2);
		}
		while (current)
		{
			if (ft_strcmp(args[i], current->key) == 0)
			{
				current->hits = 0;
				break ;
			}
			current = current->next;
		}
	}
}

void		delete_hashtable(t_hash **h_table, int len)
{
	int		i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		if ((*h_table)->list[i])
			(*h_table)->list[i] = del_list(&(*h_table)->list[i], len);
		i++;
	}
}

void		aff_hashtable(t_hash **h_table)
{
	t_hash	*hashtable;
	t_ht	*current;
	int		i;
	int		c;

	hashtable = *h_table;
	i = -1;
	c = 0;
	while (++i < TABLE_SIZE)
	{
		current = hashtable->list[i];
		while (current)
		{
			if (!c)
				ft_putendl("hits    command");
			printf("   %d    %s\n", current->hits, current->value);
			c++;
			current = current->next;
		}
	}
	if (!c)
		ft_putendl_fd("42sh: hash table empty", 2);
}

t_ht		*del_list(t_ht **list, int len)
{
	t_ht		*current = NULL;
	t_ht		*head = NULL;
	t_ht		*next;

	current = *list;
	if (current && current->hits != 0 && len > 2)
	{

		next = current->next;
		ft_strdel(&current->key);
		ft_strdel(&current->value);
		free(current);
		current = next;
	}
	else if (len == 2)
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
		if (current->next && current->next->hits != 0 && len > 2)
		{
			next = current->next->next;
			ft_strdel(&current->key);
			ft_strdel(&current->value);
			free(current->next);
			current = next;
		}
		else if (len == 2)
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

int			hash_function(char *str)
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
	if (hash_value < 0)
		hash_value = hash_value * (-1);
    return (hash_value);
}

void		del_hash(t_hash **h_table, char **args)
{
	t_hash	*hashtable;
	t_ht	*current;
	int		i;
	int		slot;

	hashtable = *h_table;
	i = 1;
	while (args[++i])
	{
		slot = hash_function(args[i]);
		current = hashtable->list[slot];
		if (delete_list(current, &(hashtable->list[slot]), args[i]) == 0)
		{
			ft_putstr_fd("42sh: hash: ", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd(": not found", 2);
		}
	}
}

int		delete_list(t_ht *list, t_ht **main_head, char *arg)
{
	t_ht	*current;
	t_ht	*prev;

	current = list;
	prev = NULL;

	if (current)
	{

		if (ft_strcmp(arg, current->key) == 0)
		{
			list = current->next;
			free(current->key);
			free(current->value);
			free(current);
			*main_head = list;
			return (1);
		}
		while (current && (ft_strcmp(arg, current->key) != 0))
		{
			prev = current;
			current = current->next;
		}
		if (current == NULL)
			return (0);	
		prev->next = current->next;
		free(current->key);
		free(current->value);
		free(current);
	}
	else
		return (0);
	return (1);
}

void		search_hash(t_hash **h_table, char **args, int len)
{
	t_hash	*hashtable;
	t_ht	*current;
	int		slot;
	int		i;

	hashtable = *h_table;
	i = 1;
	if (len == 3)
	{
		slot = hash_function(args[2]);
		current = hashtable->list[slot];
		if (!current)
		{
			ft_putstr_fd("42sh: hash: ", 2);
			ft_putstr_fd(args[2], 2);
			ft_putendl_fd(": not found", 2);
		}
		while (current)
		{
			if (ft_strcmp(args[2], current->key) == 0)
			{
				ft_putendl(current->value);
				break ;
			}
			current = current->next;
		}
	}
	else
	{
		while (args[++i])
		{
			slot = hash_function(args[i]);
			current = hashtable->list[slot];
			if (!current)
			{
				ft_putstr_fd("42sh: hash: ", 2);
				ft_putstr_fd(args[i], 2);
				ft_putendl_fd(": not found", 2);
			}
			while (current)
			{
				if (ft_strcmp(args[i], current->key) == 0)
				{
					printf("%s     %s\n", args[i], current->value);
					break ;
				}
				current = current->next;
			}
		}
	}
}

t_ht		*hash_p_insert(char *arg, char *path)
{
	t_ht	*entry;

	entry = NULL;
	if (path)
	{
		entry = (t_ht*)ft_memalloc(sizeof(t_ht));
		entry->key = ft_strdup(arg);
		entry->value = ft_strdup(path);
		entry->hits = 0;
		entry->next = NULL;
	}
	return (entry);
}