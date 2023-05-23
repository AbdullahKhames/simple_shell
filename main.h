#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;


/**
 * struct shelldata - struct that contains all relevant data on runtime
 * @av: argument vector
 * @_environ: environment variable
 * @pid: process ID of the shell
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 */
typedef struct shelldata
{
	char **av;
	char **_environ;
	char *pid;
	char *input;
	char **args;
	int status;
	int counter;

} shelldata_t;

/**
 * struct sepo_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct sepo_list_s
{
	char separator;
	struct sepo_list_s *next;
} sepo_list;

/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_varo;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(shelldata_t *datash);
} builtin_t;


/* utils_error1.c */
char *strcat_cd(shelldata_t *, char *, char *, char *);
char *error_get_cd(shelldata_t *datash);
char *error_not_found(shelldata_t *datash);
char *error_exit_shell(shelldata_t *datash);

/* aux_error2.c */
char *error_get_alias(char **args);
char *error_env(shelldata_t *datash);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path_126(shelldata_t *datash);

/* aux_help.c */
void utils_help_env(void);
void utils_help_setenv(void);
void utils_help_unsetenv(void);
void utils_help_general(void);
void utils_help_exit(void);

/* aux_help2.c */
void utils_help(void);
void utils_help_alias(void);
void utils_help_cd(void);


/* aux_lists.c */
sepo_list *add_sepo_node_end(sepo_list **head, char sep);
void free_sepo_list(sepo_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);

/* aux_lists2.c */
r_varo *add_rvaro_node(r_varo **head, int lvar, char *var, int lval);
void free_rvaro_list(r_varo **head);


/* aux_mem.c */
void _memcpyo(void *newptr, const void *ptr, unsigned int size);
void *_realloco(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdpo(char **ptr, unsigned int old_size, unsigned int new_size);

/* aux_stdlib.c */
int get_leno(int n);
char *utils_itoa(int n);
int _atoio(char *s);


/* aux_str functions */
char *_strcato(char *dest, const char *src);
char *_strcpyo(char *dest, char *src);
int _strcmpo(char *s1, char *s2);
char *_strchro(char *s, char c);
int _strspno(char *s, char *accept);


/* aux_str2.c */
char *_strdupo(const char *s);
int _strleno(const char *s);
int cmp_charso(char str[], const char *delim);
char *_strtoko(char str[], const char *delim);
int _isdigito(const char *s);

/* aux_str3.c */
void rev_stringo(char *s);

/* cd.c */
void cd_doto(shelldata_t *datash);
void cd_too(shelldata_t *datash);
void cd_previouso(shelldata_t *datash);
void cd_to_homeo(shelldata_t *datash);

/* cd_shell.c */
int cd_shello(shelldata_t *datash);




/* get_help.c */
int get_help(shelldata_t *datash);


/* error_getter.c */
int error_getter(shelldata_t *datash, int eval);

/* errors_checker.c */
int char_repeat(char *inp, int i);
int sep_errors(char *input, int i, char last);
int check_first(char *input, int *i);
void error_print_syntax(shelldata_t *datash, char *input, int i, int bool);
int error_check_syntax(shelldata_t *datash, char *input);

/* execute_cmd.c */
int check_current_dir(char *path, int *i);
char *locate_comand(char *cmd, char **_environ);
int check_executable(shelldata_t *datash);
int check_permissions(char *dir, shelldata_t *datash);
int exec_command(shelldata_t *datash);

/* cmp_env.c */
int env_cmp(const char *nenv, const char *name);
char *_getenv(const char *name, char **_environ);
int _env(shelldata_t *datash);

/* set_env.c */
char *copy_info(char *name, char *value);
void set_env(char *name, char *value, shelldata_t *datash);
int _setenv(shelldata_t *datash);
int _unsetenv(shelldata_t *datash);

/* line_executor */
int line_executor(shelldata_t *datash);

/* shell_exiter.c */
int shell_exiter(shelldata_t *datash);

/* get_builtin */
int (*get_builtin(char *cmd))(shelldata_t *datash);

/* line_bringer.c */
void line_bringer(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

/* get_sigint.c */
void get_sigint(int signal);

/* line_reader.c */
char *line_reader(int *read);

/* main.c */
void data_free(shelldata_t *shelldata);
void data_set(shelldata_t *shelldata, char **av);

/* env_checker.c */
void env_checker(r_varo **h, char *in, shelldata_t *data);
int vars_checker(r_varo **h, char *in, char *st, shelldata_t *data);
char *input_replace(r_varo **head, char *input, char *new_input, int nlen);
char *vars_replace(char *input, shelldata_t *shelldata);


/* shell_loop.c */
char *comment_remover(char *in);
void shell_looper(shelldata_t *shelldata);

/* char_swapper.c */
char *char_swapper(char *src, int bool);
void add_nodes(sepo_list **head_s, line_list **head_l, char *input);
void go_next(sepo_list **list_s, line_list **list_l, shelldata_t *datash);
int split_commands(shelldata_t *datash, char *input);
char **split_line(char *input);
#endif

