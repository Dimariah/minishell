/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:51:11 by messkely          #+#    #+#             */
/*   Updated: 2024/07/02 01:11:12 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libftt/libft.h"

typedef struct s_prompt
{
	char			**argv;
	char			**file;
	struct s_prompt	*next;
}	t_prompt;

int			check_syntax(char *input);
void		ft_error(char *s, char c);

char		*rm_escape_char(char *s);
char		**process_token(char *s, char token);

t_prompt	*ft_lstnew(char *content);
void		ft_add_back(t_prompt **head, t_prompt *new);
char		**rm_red_args(char **args, int n, t_prompt *pmp);
int			ft_arglen(char **args);
char		*add_space_in_red(char *s);
void		toggle_quotes(char c, int *single_quote, int *double_quote);

void		ft_broom(char **arr);
void		free_list(t_prompt *head);

#endif