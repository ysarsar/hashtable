/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_file_tools2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrxy <mrxy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 15:44:30 by mrxy              #+#    #+#             */
/*   Updated: 2020/11/24 15:45:03 by mrxy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

int		is_file(char *pathname)
{
	struct	stat	sb;

	if (lstat(pathname, &sb) == -1)
		return (EXIT_FAILURE);
	if (S_ISREG(sb.st_mode))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int		ft_setgid(char *pathname)
{
	struct	stat	sb;

	if (lstat(pathname, &sb) == -1)
		return (EXIT_FAILURE);
	if (sb.st_mode & S_ISGID)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int		is_symlink(char *pathname)
{
	struct	stat	sb;

	if (lstat(pathname, &sb) == -1)
		return (EXIT_FAILURE);
	if (S_ISLNK(sb.st_mode))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int		is_fifo(char *pathname)
{
	struct	stat	sb;

	if (lstat(pathname, &sb) == -1)
		return (EXIT_FAILURE);
	if (S_ISFIFO(sb.st_mode))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int		readable_by_owner(char *pathname)
{
	struct	stat	sb;

	if (lstat(pathname, &sb) == -1)
		return (EXIT_FAILURE);
	if (S_IRUSR & sb.st_mode)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
