/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrxy <mrxy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 22:55:49 by ysarsar           #+#    #+#             */
/*   Updated: 2020/11/23 18:50:41 by mrxy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include "../libft/libft.h"
# include <stdio.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "ft_readline.h"
//test builtin includes
# include <sys/types.h>
# include <sys/stat.h>
# include <stdint.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/sysmacros.h>

# define TABLE_SIZE 1000

typedef	struct				s_ht
{
	char					*value;
	char					*key;
	int						hits;
	struct	s_ht			*next;
}							t_ht;

typedef	struct				s_hash
{
	t_ht					**list;
}							t_hash;

typedef struct				s_env
{
	char					*data;
	struct s_env			*next;
}							t_env;

typedef	struct				s_pipe_variable
{
	int						pip[2];
	int						cmd_nbr;
	int						tmp;
	int						pid;
	char					*tty;
}							t_pipe_variable;

typedef	struct				s_quote_var
{
	int						j;
	char					c;
}							t_quote_var;

typedef	struct				s_token_v
{
	int						k;
	char					*str;
}							t_token_v;

typedef	enum				e_type
{
	WORD,
	SEPARATEUR,
	PIPE,
	R_FD,
	L_FD,
	REDIR_IN,
	REDIR_OUT,
	APPEND_OUT,
	AGGREGATION_OUT,
	AGGREGATION_IN,
	HEREDOC
}							t_type;

typedef	struct				s_redirection
{
	char					*left;
	char					*right;
	t_type					type;
	struct s_redirection	*next;
}							t_redirection;

typedef	struct				s_token
{
	char					*value;
	t_type					type;
}							t_token;

typedef struct				s_parse
{
	char					*cmd;
	t_redirection			*redirection;
	struct s_parse			*pipe;
	struct s_parse			*sep;
}							t_parse;

void						sh_loop(t_env **envp);

void						free_ast(t_parse **ast);

int							ft_next_token(char **line, t_token **tok,
										int mode, t_his **his);

int							ft_separators(t_token **tok, char *str, int i);
int							ft_redirection(char *str,
											t_token **tok, int i, int *redir);
int							ft_is_numeric(char *str);
int							ft_check_fd(t_token_v v,
										char **tmp, t_token **token, int mode);
int							ft_check_word(t_token **token, char **tmp);
int							ft_quotes(char **cmd,
										int i, char **tmp_token, t_his **his);

t_parse						*ft_parse_tree(char **line, t_his **his);

void						ft_word_type(t_parse **ast, t_token **token);
int							ft_separateur_type(t_parse **ast,
											t_parse *current, t_token *token);
int							ft_pipe_type(t_parse **ast, t_token *token);
int							ft_redirection_type(t_parse **ast, t_token *token);

int							check_syntax(t_parse *ast);

int							sh_execute(t_parse **ast, t_env **envp, char *tty, t_hash **h_table);

int							execute_simple_cmd(char *cmd,
											char **tabs, t_env **envp, t_hash **h_table);
char						*valid_path(char *cmd_name, char **tabs);

int							ft_env(t_env *envp);
int							ft_setenv(t_env **envp, char **args);
int							ft_unsetenv(t_env **envp, char **args);
int							ft_cd(char **args, t_env *envp);
int							ft_echo(char **args);

int							ft_cd_glob(char *home, char **args,
										t_env *envp, char *var);
void						ft_env_cwd(t_env *envp);
void						ft_env_owd(char *cwd, t_env *envp);
int							ft_cd_glob(char *home, char **args,
										t_env *envp, char *var);

void						ft_add_variable(t_env **envp, char **args, int c);
int							delete_var(t_env **env, char *arg);
void						list_push(char *var, t_env **envp);

int							execute_redirection(t_redirection
											*redirection, char *tty);
void						ft_reset_fd(char *tty, int file_d);
int							ft_redir_inout(t_redirection *redirect, int fd);
int							ft_redir_append(t_redirection *redir, int fd);
int							ft_agg_digit(t_redirection *redir,
										int fd, int left);
int							ft_agg_close(t_redirection *redir,
										int fd, int left);
int							ft_agg_word(t_redirection *redir, int fd, int left);
char						*ft_document(char *redir_right);

int							execute_pipe(t_parse *ast, t_env **envp,
										char **tabs, char *tty, t_hash **h_table);

char						**ft_expantions(char **args, t_env **envp);

char						*ft_var_name(char *str);
char						*ft_search_env(char *str, t_env *envp);
char						*ft_change_arg(char *key, char *str, char *var);
void						change_home(t_env **envp, char **arg);
char						**line_error(char *str);
int							ft_is_a_user(char **str, char *key);

char						*free_tabs(char **arg);
void						exec_error(char *str, int c);
int							ft_argslen(char **args);
int							ft_datalen(char *data);
int							print_error(int c);
int							redirect_error(t_redirection *redirect);
void						listpush(char *var, t_env **envp);
void						free_str(char *ptr, char *tmp);
char						*ft_changedir(char *str, char *cwd);
int							is_white(char c);
int							free_tabs2(char **args, char **arr);
int							is_special(char c);

// hash function
t_hash			*ht_create(void);
char			*ft_hashtable(char **args, char **tabs, t_hash **h_table);
void			ft_hash(char **args, t_hash **h_table);
void			reset_hits(char **args, t_hash **h_table);
void			delete_hashtable(t_hash **h_table, int len);
void			aff_hashtable(t_hash **h_table);
t_ht			*del_list(t_ht **list, int len);
int				hash_function(char *str);
t_ht			*ht_insert(char *str, char **tabs);
void			l_flag(t_hash **h_table, char **args);
void			del_hash(t_hash **h_table, char **args);
int				delete_list(t_ht *list, t_ht **main_head, char *arg);
void			d_flag(t_hash **h_table, char **args);
void			t_flag(t_hash **h_table, char **args);
void			p_flag(t_hash **h_table, char **args);
void			search_hash(t_hash **h_table, char **args, int len);
t_ht			*hash_p_insert(char *arg, char *path);
void			ft_hash_error(char *str);
void			l_flag_error(char *str);
void			l_flag_print(char *value, char *key);
void			l_flag_mini(char *str, t_ht *current);
void			l_flag_valid(t_hash *hashtable, int slot);
void			p_flag_mini(char **args, t_hash **h_table);
void			p_flag_free(t_ht **h_list, char *str, char *path);
int				free_node(t_ht **list);
void			del_list_mini(t_ht **list, int len);
void			search_hash_mini(t_hash **h_table, char **args);

/* Test functions */

int				ft_test(char **args);

//file test
int				test_file(char **args);
int				block_special(char *pathname);
int				character_special(char *pathname);
int				is_dir(char *pathname);
int				file_exist(char *pathname);
int				ft_setgid(char *pathname);
int				is_symlink(char *pathname);
int				is_fifo(char *pathname);
int				is_file(char *pathname);
int				readable_by_owner(char *pathname);
int				is_socket(char *pathname);
int				file_not_empty(char *pathname);
int				ft_setuid(char *pathname);
int				writeable_by_owner(char *pathname);
int				executable_by_owner(char *pathname);

//string and integer test
int				test_string(char **args);
int				ft_equal(char *str1, char *str2);
int				ft_not_equal(char *str1, char *str2);
int				ft_integer_equal(char *s1, char *s2);
int				ft_integer_not_equal(char *s1, char *s2);
int				ft_integer_ge(char *s1, char *s2);
int				ft_integer_lt(char *s1, char *s2);
int				ft_integer_le(char *s1, char *s2);

#endif
