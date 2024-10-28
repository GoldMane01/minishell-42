#include "minishell.h"

static int	check_strequal(char *ptr, const char *needle, size_t len)
{
	int	count;

	count = 0;
	while (*needle != '\0' && len > 0)
	{
		if (*ptr != *needle)
			return (0);
		len--;
		ptr++;
		needle++;
		count++;
	}
	if (len == 0 && *needle != '\0')
		return (0);
	return (1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*ptr;

	ptr = (char *)haystack;
	if (*needle == '\0')
		return (ptr);
	while (len > 0 && *haystack != '\0')
	{
		if (*haystack == *needle)
		{
			ptr = (char *)haystack;
			if (check_strequal(ptr, needle, len))
				return (ptr);
		}
		haystack++;
		len--;
	}
	return (0);
}

int	check_access(char *path, char *command)
{
	char	*ptr;
	char	**cmdsplit;

	cmdsplit = ft_split(command, ' ');
	ptr = malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(cmdsplit[0]) + 1));
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, path, ft_strlen(path) + 1);
	ft_strlcat(ptr, cmdsplit[0], ft_strlen(path) + ft_strlen(cmdsplit[0]) + 1);
	if (access(ptr, F_OK) != 0)
		return (0);
	return (1);
}

char	**find_paths(char *envp[])
{
	char	**paths;

	while (*envp != NULL)
	{
		if (ft_strnstr(*envp, "PATH", 5))
			break ;
		envp++;
	}
	paths = ft_split(*envp, ':');
	return (paths);
}

char	*get_path(char *path, char *command)
{
	char	*ptr;
	char	**cmdsplit;

	cmdsplit = ft_split(command, ' ');
	ptr = malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(cmdsplit[0]) + 1));
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, path, ft_strlen(path) + 1);
	ft_strlcat(ptr, cmdsplit[0], ft_strlen(path) + ft_strlen(cmdsplit[0]) + 1);
	return (ptr);
}

char	*check_paths(char **allpaths, char *command)
{
	char	*path;

	path = NULL;
	while (*allpaths)
	{
		if (check_access(*allpaths, command))
		{
			path = get_path(*allpaths, command);
			break ;
		}
		allpaths++;
	}
	return (path);
}

char	*cmdpath(t_cmd *cmd, char **env)
{
	char	**allpaths;
	char	*path;
	char	*command;

	allpaths = find_paths(env);
	*allpaths += 5;
	command = malloc(sizeof(char) * (ft_strlen(cmd->cmd[0]) + 2));
	if (!command)
		return (NULL);
	ft_strlcpy(command, "/", 2);
	ft_strlcat(command, cmd->cmd[0], ft_strlen(cmd->cmd[0]) + ft_strlen(command) + 1);
	path = check_paths(allpaths, command);
	return (path);
}

void	read_input(int link[], t_redir *fdin)
{
	char	buffer[4096];
	int		bytes;
	int		fd;

	dup2(link[1], STDOUT_FILENO);
	if (fdin)
	{
		if (access(fdin->name, R_OK) != 0)
			exit(1);
		fd = open(fdin->name, O_RDONLY);
		bytes = read(fd, buffer, 4095);
		buffer[bytes] = '\0';
		write(STDOUT_FILENO, buffer, bytes);
	}
}

void	execute(t_cmd *cmd, t_redir *fdin, t_redir *fdout, int fd[])
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		read_input(fd, fdin);
	}
}

void	pipex(t_cmd **cmd, t_redir *fdin, t_redir *fdout, char **env)
{
	char	*path;
	int		fd[2];
	t_cmd	*node;

	node = *cmd;
	path = cmdpath(*cmd, env);
	if (pipe(fd) == -1)
		exit(1);
	//while (node)
	//{
		execute(node, fdin, fdout, fd);
		node = node->next;
	//}
	close(fd[0]);
	close(fd[1]);
}