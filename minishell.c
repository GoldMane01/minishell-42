#include "minishell.h"

char	*get_dir()
{
	char	buffer[1024];
	char	*dir;
	int 	i;

	getcwd(buffer, 1024);
	i = 0;
	while(buffer[i])
		i++;
	dir = malloc(sizeof(char) * (i + 3));
	if (!dir)
		exit(1);
	i = -1;
	while (buffer[++i])
		dir[i] = buffer[i];
	dir[i] = '>';
	dir[i + 1] = ' ';
	dir[i + 2] = '\0';
	return (dir);
}

char	*concat_quote(char *line)
{
	char	*concat_line;

	ft_strlcat(line, "\n", ft_strlen(line) + 2);
	concat_line = ft_strjoin(line, readline("quote> "));
	return(concat_line);
}

void	parse_line(char *line)
{
	while(close_quote(line))
		line = concat_quote(line);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	counter;
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	counter = 0;
	if (n == 0)
		return (0);
	while (counter < (n - 1) && p1[counter] != '\0' && p2[counter] != '\0')
	{
		if (p1[counter] != p2[counter])
			return (p1[counter] - p2[counter]);
		counter++;
	}
	return (p1[counter] - p2[counter]);
}

char	*get_redir_file(char *file, int i, int type)
{
	char	*name;
	int		j;

	if 
	name = malloc(sizeof(char) * (ft_strlen(file) + 1));
	if (!name)
		exit(1);
	j = 0;
	while (file[j])
	{
		name[j] = file[j];
		j++;
	}
	name[j] = '\n';
	return (name);
}

t_redir	*init_redir(char *file, int i, int type)
{
	t_redir	*redir;

	redir = malloc(sizeof(redir));
	if (!redir)
		exit(1);
	redir->name = get_redir_file(file, i, type);
	redir->type = type;
	redir->next = NULL;
	return (redir);
}

t_redir	*create_redir(char *line, int i)
{
	if (line[i] == '<' && line[i + 1] == '<')
		return (init_redir(line, i, INN));
	if (line[i] == '<' && line[i + 1] != '<')
		return (init_redir(line, i, IN));
	if (line[i] == '>' && line[i + 1] == '>')
		return (init_redir(line, i, OUTT));
	if (line[i] == '>' && line[i + 1] != '>')
		return (init_redir(line, i, OUT));
	return (NULL);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	*dir;


	while (1 + 1 == 2)
	{
		dir = get_dir();
		line = NULL;
		line = readline(dir);
		add_history(line);
		parse_line(line);
		create_redir(line, 0);
		free(line);
		free(dir);
	}
}

//1-	cmd
//2-	cmd | cmd | cmd
//3-	</> file cmd | cmd