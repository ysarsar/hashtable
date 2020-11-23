/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrxy <mrxy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:46:34 by mrxy              #+#    #+#             */
/*   Updated: 2020/11/23 19:05:00 by mrxy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

int		test_string(char **args)
{
	int		args_len;

	args_len = ft_argslen(args);
	if (args_len == 4)
	{
		if (ft_strcmp(args[2], "=") == 0)
			return (ft_equal(args[1], args[3]));
		else if (ft_strcmp(args[2], "!=") == 0)
			return (ft_not_equal(args[1], args[3]));
		else if (ft_strcmp(args[2], "-eq") == 0)
			return (ft_integer_equal(args[1], args[3]));
		else if (ft_strcmp(args[2], "-ne") == 0)
			return (ft_integer_not_equal(args[1], args[3]));
		else if (ft_strcmp(args[2], "-ge") == 0)
			return (ft_integer_ge(args[1], args[3]));
		else if (ft_strcmp(args[2], "-lt") == 0)
			return (ft_integer_lt(args[1], args[3]));
		else if (ft_strcmp(args[2], "-le") == 0)
			return (ft_integer_le(args[1], args[3]));
		
	}
	else if (args_len < 4)
	{
		ft_putstr_fd("42sh: test: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": unary operator expected", 2);
	}
	else
		ft_putendl_fd("42sh: test: too many arguments", 2);
	return (2);
}

int		ft_equal(char *str1, char *str2)
{
	if (ft_strcmp(str1, str2) == 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int		ft_not_equal(char *str1, char *str2)
{
	if (ft_strcmp(str1, str2) != 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int		ft_integer_equal(char *s1, char *s2)
{
	int		num1;
	int		num2;

	if (!ft_is_numeric(s1) || !ft_is_numeric(s2))
	{
		ft_putstr_fd("42sh: test: ", 2);
		if (!ft_is_numeric(s2))
			ft_putstr_fd(s2, 2);
		else
			ft_putstr_fd(s1, 2);
		ft_putendl_fd(": integer expression expected", 2);
		return (EXIT_FAILURE);
	}
	num1 = ft_atoi(s1);
	num2 = ft_atoi(s2);
	if (num1 == num2)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int		ft_integer_not_equal(char *s1, char *s2)
{
	int		num1;
	int		num2;

	if (!ft_is_numeric(s1) || !ft_is_numeric(s2))
	{
		ft_putstr_fd("42sh: test: ", 2);
		if (!ft_is_numeric(s1))
			ft_putstr_fd(s1, 2);
		else
			ft_putstr_fd(s2, 2);
		ft_putendl_fd(": integer expression expected", 2);
		return (EXIT_FAILURE);
	}
	num1 = ft_atoi(s1);
	num2 = ft_atoi(s2);
	if (num1 != num2)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int		ft_integer_ge(char *s1, char *s2)
{
	int		num1;
	int		num2;

	if (!ft_is_numeric(s1) || !ft_is_numeric(s2))
	{
		ft_putstr_fd("42sh: test: ", 2);
		if (!ft_is_numeric(s1))
			ft_putstr_fd(s1, 2);
		else
			ft_putstr_fd(s2, 2);
		ft_putendl_fd(": integer expression expected", 2);
		return (EXIT_FAILURE);
	}
	num1 = ft_atoi(s1);
	num2 = ft_atoi(s2);
	if (num1 >= num2)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int		ft_integer_lt(char *s1, char *s2)
{
	int		num1;
	int		num2;

	if (!ft_is_numeric(s1) || !ft_is_numeric(s2))
	{
		ft_putstr_fd("42sh: test: ", 2);
		if (!ft_is_numeric(s1))
			ft_putstr_fd(s1, 2);
		else
			ft_putstr_fd(s2, 2);
		ft_putendl_fd(": integer expression expected", 2);
		return (EXIT_FAILURE);
	}
	num1 = ft_atoi(s1);
	num2 = ft_atoi(s2);
	if (num1 < num2)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int		ft_integer_le(char *s1, char *s2)
{
	int		num1;
	int		num2;

	if (!ft_is_numeric(s1) || !ft_is_numeric(s2))
	{
		ft_putstr_fd("42sh: test: ", 2);
		if (!ft_is_numeric(s1))
			ft_putstr_fd(s1, 2);
		else
			ft_putstr_fd(s2, 2);
		ft_putendl_fd(": integer expression expected", 2);
		return (EXIT_FAILURE);
	}
	num1 = ft_atoi(s1);
	num2 = ft_atoi(s2);
	if (num1 <= num2)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
