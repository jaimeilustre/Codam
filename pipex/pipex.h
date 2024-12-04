/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/27 15:23:14 by jilustre      #+#    #+#                 */
/*   Updated: 2024/12/04 11:16:17 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"

void	free_array(char **arr);
void	handle_error(const char *msg);
int		open_input_file(char *filename);
int		open_output_file(char *filename);
char	*get_command_path(char *cmd, char **envp);
void	execute_command(char *cmd, char **envp);
void	create_pipe(int pipe_fd[]);
void	first_child(int input_fd, int pipe_fd[], char *cmd, char **envp);
void	second_child(int output_fd, int pipe_fd[], char *cmd, char **envp);
void	pipex(char **argv, char **envp);
int		main(int argc, char **argv, char **envp);

#endif
