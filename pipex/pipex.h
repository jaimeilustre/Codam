/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/27 15:23:14 by jilustre      #+#    #+#                 */
/*   Updated: 2025/01/17 08:04:12 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include "libft/libft.h"

void	free_array(char **arr);
void	handle_error(const char *cmd, const char *msg);
int		open_input_file(char *filename);
int		open_output_file(char *filename);
char	*get_command_path(char *cmd, char **envp);
char	*search_in_paths(char *cmd, char **envp);
char	*get_path_env(char **envp);
char	*try_paths(char *cmd, char **paths);
void	parse_command(char *cmd, char **envp, char ***args, char **cmd_path);
void	execute_command(char *cmd, char **envp);
void	create_pipe(int pipe_fd[]);
void	first_child(int input_fd, int pipe_fd[], char *cmd, char **envp);
void	second_child(int output_fd, int pipe_fd[], char *cmd, char **envp);
void	open_files(char **argv, int *input_fd, int *output_fd);
pid_t	fork_first_child(int input_fd, int *pipe_fd, char *cmd, char **envp);
pid_t	fork_second_child(int output_fd, int *pipe_fd, char *cmd, char **envp);
void	parent_process_cleanup(int input_fd, int pipe_fd[], int output_fd);
void	wait_for_children(pid_t pid1, pid_t pid2);
void	pipex(char **argv, char **envp);
int		main(int argc, char **argv, char **envp);

#endif
