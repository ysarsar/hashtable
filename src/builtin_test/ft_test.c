/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrxy <mrxy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 06:01:14 by mrxy              #+#    #+#             */
/*   Updated: 2020/11/23 19:02:57 by mrxy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

int		ft_test(char **args)
{
	int		args_len;

	args_len = ft_argslen(args);
	if (args_len == 1)
		return (EXIT_FAILURE);
	if (args_len == 2)
		return (EXIT_SUCCESS);
	//	File test
	if (args[1][0] == '-')
		return (test_file(args));
	else if (ft_strcmp(args[1], "!") == 0)
	{
		if (args_len > 3)
		{
			ft_putstr_fd("42sh: test: ", 2);
			ft_putstr_fd(args[2], 2);
			ft_putendl_fd(": unary operator expected", 2);
			return (2);
		}
		return (EXIT_FAILURE);
	}
	//string and numeric test
	else
		return (test_string(args));
}