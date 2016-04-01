/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 06:13:10 by jmontija          #+#    #+#             */
/*   Updated: 2016/03/30 22:48:53 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_H
# define MINISH_H

# include <stdio.h>
# include "libft.h"
# include "get_next_line.h"
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <termios.h>
# include <term.h>
# include <signal.h>

# define NEW(x)			(ft_strnew(x))
# define LEN(x)			(ft_strlen(x))
# define SDUP(x)		(ft_strdup(x))
# define SUB(a, b, c)	(ft_strsub(a, b, c))
# define JOIN(a, b)		(ft_strjoin(a, b))
# define STRCHR(a, b)	(ft_strchr(a, b))
# define REMOVE(x)		(ft_strdel(x))

typedef int				t_bool;
enum {false, true};
enum {P, S, ii, v, u};
enum {e_opt, namenv, utils};

typedef struct			s_env
{
	char				*name;
	char				*val;
	t_bool				exist;
	struct s_env		*next;
}						t_env;

typedef struct			s_options
{
	t_bool				*on;
	char				**params;
}						t_options;

typedef struct			s_group
{
	char				**cmd;
	char				*order;
	int					*define_cmd;
	int					lvl;
	struct s_options	*options;
	struct s_env		*first;
	struct s_env		*last;
}						t_group;

t_group					*init_grp(void);
void					parse_cmd(int const fd, t_group *grp);
void					exec_env(t_group *grp, int show_env);
void					exec_cmd(t_group *grp, char *path, char **cmd_line);
void					cderr_pwd(t_group *grp, char *path, struct stat s_buf);
char					*child_process(t_group *grp, char *order);
char					*search_exec(t_group *grp, char *cmd);
char					*ft_getenv(t_group *grp, char *tofind);
int						list_to_tab(t_env *env, char ***env_tab);
int						exec_builtin(t_group *grp, char *order);
int						is_env(char *env);
int						insert_env(t_group *grp, char *env);
int						unset_env(t_group *grp, char *todel);
int						manage_opt(t_group *grp);
int						error_opt(char opt, char *what);
void					error_cmd(char *what, char *who);

#endif
