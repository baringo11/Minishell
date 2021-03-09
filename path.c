#include "minishell.h"

/*
** Function ft_get_path() first saves in a variable the content of the
** environment $PATH. Then split all the paths contained in that
** variable and check every one of them searching for the command that
** needs to be executed. If the command is founded on one of those paths
** the complete path of the command is saved in s->command_path variable.
** Other than that, s->command_path remains pointing to NULL.
*/

void	ft_get_path(t_minishell *s)
{
	char	**paths;
	char	*complete_path;
	char	*temp;

	s->path = ft_get_env_var_content(s, "PATH");
	//ft_get_env_path(s);
	paths = ft_split(s->path, ':');
	temp = ft_check_dir(s, paths);
	complete_path = ft_strjoin(temp, "/");
	paths = ft_free_matrix(paths);
	s->command_path = ft_strjoin(complete_path, s->tokens[0]);
	complete_path = ft_free_ptr(complete_path);
}

/*
** Function ft_check_dir() opens, one by one, the directories where the
** executable commands could be founded (those included on $PATH evironment
** variable), and search there for the actual command thar should be executed.
** When the comand is founded, this function returns the appropiate path.
** Other than that, returns NULL pointer.
*/

char	*ft_check_dir(t_minishell *s, char **paths)
{
	DIR				*dir;
	struct dirent	*sd;

	while (*paths)
	{
		dir = opendir(*paths);
		while ((sd = readdir(dir)))
		{
			if (!(ft_strncmp(sd->d_name, s->tokens[0], (strlen(s->tokens[0]) + 1))))
			{
				closedir(dir);
				return(*paths);
			}
		}
		closedir(dir);
		*paths++;
	}
	return (NULL);
}

// void	ft_get_env_path(t_minishell *s)
// {
// 	int		i;
// 	int		j;
// 	j = 0;
// 	while ((s->env)[j])
// 	{
// 		if (!ft_strncmp("PATH=", (s->env)[j], 5))
// 		{
// 			if (!(s->path = malloc(ft_strlen((s->env)[j]) + 1)))
// 				ft_print_error(s);
// 			i = 0;
// 			while (((s->env)[j])[i + 5] != '\0')
// 			{
// 				s->path[i] = ((s->env)[j])[i + 5];
// 				i++;
// 			}
// 			s->path[i] = '\0';
// 			break ;
// 		}
// 		else
// 			j++;
// 	}
// }
