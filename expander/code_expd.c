/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_expd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 19:16:44 by yiken             #+#    #+#             */
/*   Updated: 2024/06/16 20:03:13 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	cat_code(int code, char *new_str, int *j)
{
	char	c;

	if (code > 9)
	{
		cat_code(code / 10, new_str, j);
		cat_code(code % 10, new_str, j);
	}
	else
	{
		c = '0' + code;
		new_str[(*j)++] = c;
	}
}

void	code_len(int code, int *cntr)
{
	if (code > 9)
	{
		code_len(code / 10, cntr);
		code_len(code % 10, cntr);
	}
	else
		(*cntr)++;
}
