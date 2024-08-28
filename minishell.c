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

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	*dir;

	while (1 + 1 == 2)
	{
		dir = get_dir();
		line = NULL;
		line = readline(dir);
		parse_line(line);
		free(line);
		free(dir);
	}
}

//1-	cmd
//2-	cmd | cmd | cmd
//3-	</> file cmd | cmd