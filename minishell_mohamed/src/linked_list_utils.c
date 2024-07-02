/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:28:39 by messkely          #+#    #+#             */
/*   Updated: 2024/07/02 03:41:23 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_broom(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

t_prompt	*ft_lstnew(char *data)
{
	t_prompt	*new;
	int			i;

	new = malloc(sizeof(t_prompt));
	if (!new)
		return (exit(1), NULL);
	data = ft_strtrim(data, " ");
	data = add_space_in_red(data);
	new->argv = process_token(data, ' ');
	free(data);
	i = 0;
	while (new->argv[i])
	{
		new->argv[i] = rm_escape_char(new->argv[i]);
		i++;
	}
	new->argv = rm_red_args(new->argv, ft_arglen(new->argv), new);
	new->next = NULL;
	return (new);
}

t_prompt	*ft_last_node(t_prompt *head)
{
	t_prompt	*last;

	last = NULL;
	if (!head)
		return (NULL);
	while (head != NULL)
	{
		last = head;
		head = head->next;
	}
	return (last);
}

void	ft_add_back(t_prompt **head, t_prompt *new)
{
	t_prompt	*last;

	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	last = ft_last_node(*head);
	last->next = new;
}

void	free_list(t_prompt *head)
{
	t_prompt	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		ft_broom(tmp->argv);
		ft_broom(tmp->file);
		free(tmp);
	}
}
