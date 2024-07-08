/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:28:39 by messkely          #+#    #+#             */
/*   Updated: 2024/07/08 13:39:46 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_broom(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

t_smplcmd	*ft_lstnew(char *data, char **arr, t_smplcmd **pmp)
{
	t_smplcmd	*new;
	int			i;

	new = malloc(sizeof(t_smplcmd));
	if (!new)
	{
		ft_broom(arr);
		free_list(pmp);
		exit(1);
	}
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

t_smplcmd	*ft_last_node(t_smplcmd *head)
{
	t_smplcmd	*last;

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

void	ft_add_back(t_smplcmd **head, t_smplcmd *new)
{
	t_smplcmd	*last;

	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	last = ft_last_node(*head);
	last->next = new;
}

void	free_list(t_smplcmd **cmdlst)
{
	t_smplcmd	*head;
	t_smplcmd	*tmp;

	head = *cmdlst;
	while (head)
	{
		tmp = head;
		head = head->next;
		ft_broom(tmp->argv);
		ft_broom(tmp->reds);
		free(tmp);
	}
	*cmdlst = NULL;
}
