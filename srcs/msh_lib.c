/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 03:52:12 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/01 17:28:56 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	error_cmd(char *what, char *who)
{
	ft_putstr("fsh: ");
	ft_putstr(what);
	ft_putstr(" -> ");
	ft_putendl(who);
}

int		error_opt(char opt, char *what)
{
	ft_putstr("fsh: '-");
	ft_putchar(opt);
	ft_putchar('\'');
	ft_putendl(what);
	ft_putendl("usage: env [-iv] [-P altpath] [-S string] \
[-u name] [name=value ...] [utility [argument ...]]");
	return (-1);
}

void	cderr_pwd(t_group *grp, char *path, struct stat s_buf)
{
	mode_t		val;
	char		buf[1024];
	char		*old_pwd;
	char		*pwd;
	char		*dir_name;

	dir_name = ft_strrchr(path, '/');
	dir_name[0] == '/' ? dir_name = dir_name + 1 : 0;
	val = (s_buf.st_mode & ~S_IFMT);
	if (access(path, F_OK) != 0)
		error_cmd("unknown directory", dir_name);
	else if (!S_ISDIR(s_buf.st_mode) && !S_ISLNK(s_buf.st_mode))
		error_cmd("this is not a directory", dir_name);
	else if (!(val & S_IXUSR))
		error_cmd("Permission denied", dir_name);
	else if (chdir(path) == 0)
	{
		old_pwd = JOIN("OLDPWD=", ft_getenv(grp, "PWD"));
		pwd = JOIN("PWD=", getcwd(buf, 1024));
		insert_env(grp, pwd);
		!old_pwd ? (old_pwd = JOIN("OLDPWD=", ft_getenv(grp, "PWD"))) : 0;
		insert_env(grp, old_pwd);
	}
	else
		error_cmd("what the fuck you are doing ?", dir_name);
}

int		list_to_tab(t_env *env, char ***env_tab)
{
	char	*tmp;
	int		pos;

	pos = 0;
	while (env != NULL)
	{
		tmp = JOIN(env->name, "=");
		(*env_tab)[pos] = JOIN(tmp, env->val);
		pos++;
		env = env->next;
	}
	return (pos);
}
