#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>
# include <limits.h>
# include <readline/readline.h>
# include "sys/stat.h"
# include "readline/history.h"
# include <termios.h>
# include <fcntl.h>

typedef struct s_type
{
	char *type;
} t_type;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_fds
{
	void			*content;
	struct s_list	*next;
}	t_fds;

typedef struct s_env
{
	char *key;
	int equal;
	char *value;
	struct s_env *next;
} t_env;

int g_signal;

typedef struct s_command
{
	char *args;
	char **args2;
	int *token;
	int pipe;
	int	redirect;
	int	append;
	int	dredirect;
	int	dappend;
	char *file;
	int	fd_out;
	int fd_in;
	int exit_status;
	struct s_command *next;
}   t_command;

typedef void (*command_func)(t_command*, t_env**, int);

typedef struct {
    char* command;
    command_func func;
} command_map;

void 		setup_signals();
char		**ft_split_input(char const *s);
char		**ft_split(char const *s, char c);
char		*ft_strcat(char *dest, char *src);
char		*ft_strcpy(char *dest, char *src);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_malloc(int size, int free);
int			ft_putstr_fd(char *s, int fd);
int			ft_putchar_fd(char c, int fd);
char		*ft_strchr(const char *s, int c);
void		ft_lstadd_back(t_env **lst, t_env *new_env);
t_command	*parsing(char *line, t_env *head);
t_list		*ft_lstnew(void *content);
char		*ft_strtok(char *str, char delim);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
char*		execute(t_env **head, t_command *cmd);
char		*ft_strdup(char *s1);
char* 		construct_command(char *path, char *arg);
void		env(t_command *cmd, t_env **head, int n);
void		env_sorting(t_env *head, t_command *cmd);
int			ft_strcmp(const char *s1, const char *s2);
void		pwd(t_command *cmd, t_env **head, int n);
void		cd(t_command *cmd, t_env **head, int n);
int			check_args(char **s);
void		echo_built(t_command *cmd, t_env **head, int i);
void		export_built(t_command *cmd, t_env **head, int n);
void		update_env_var(t_env *head, char *key, char *new_value, int equal);
char		*get_env_value(t_env *head, char *key);
char		**make_tree(char *s);
void		add_to_env(t_env **head, char *key, char *value, int equal);
void 		unset(t_command *cmd, t_env **head, int n);
void		delete_env_var(t_env **head, char *key);
void		parse_line(char *str);
char		*check_command(char **path_split, char **av);
void		add_back(t_list **lst, t_list *new_env);
__int128	ft_atoi(const char *str);
char		*ft_itoa(int n);
char		**env_to_array(t_env *head);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isalnum_v2(int c);
char		*ft_strttok(char *str, char *delims);
char		*expand(char *s, t_env *head);
char		**ft_split_with_quotes(char const *s, char c, int **token);
int			count_words_2(char const *s, char c);
char 		*before_and_after(char *s);
void 		heredocu(char *done, int *fd, t_env *head, int exp);
void		exit_bult(t_command *cmd, t_env **head, int n);
void		*exit_status();
int			have_slash(char *s);
void		status_a(int status);
void		true_v1(t_command *cmd, t_env **head, int n);
t_command	*ft_lstlast(t_command *lst);
int			pipe_with_gc(int pipefd[2]);
int			open_with_gc(const char *pathname, int flags, int per, int true_v1);
void		*ft_fds();
void		error_exit(char **args, char *msg, int exit_code);
int			folder(char *command);

#endif
