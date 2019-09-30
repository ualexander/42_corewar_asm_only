/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:02:54 by vsanta            #+#    #+#             */
/*   Updated: 2019/09/30 17:19:20 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "asm.h"

t_asm	*init()
{
	t_asm *asemb;

	asemb = (t_asm*)malloc(sizeof(t_asm));
	asemb->fd = -1;
	asemb->row = 0;
	asemb->parse_line = NULL;
	asemb->magic = COREWAR_EXEC_MAGIC;
	ft_bzero(asemb->prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(asemb->comment, COMMENT_LENGTH + 1);
	return (asemb);
}


int get_arg_type(char *args)
{
	int skip_space_i;
	skip_space_i = ft_skip_chars_i(args, SPACE_SYMBOLS);
	if (args)
}

int parse_unstruction(t_asm *asemb)
{
	int skip_space_i;
	t_op cur_op;

	skip_space_i = ft_skip_chars_i(asemb->parse_line, SPACE_SYMBOLS);
	cur_op = g_op[get_instruction_i_in_str(&(asemb->parse_line[skip_space_i]))];

	

	printf("----- %s | len = %i\n", cur_op.name, skip_space_i + ft_strlen(cur_op.name));
	return (0);
}

int parse_file(t_asm *asemb)
{
	int gnl;
	int line_type;

	line_type = 0;
	while ((gnl = get_next_line(asemb->fd, &(asemb->parse_line))) > 0)
	{
		asemb->row++;
		if (line_type == 0)
			line_type = get_line_type(asemb->parse_line);
		printf("%i - %i\n", line_type, gnl);
		if (line_type == EMPTY_LINE || line_type == COMMENT_LINE)
		{
			line_type = 0;
			continue ;
		}
			
		if (line_type == CMD_NAME_START || line_type == CMD_NAME_PROCCES)
			line_type = parse_command_name(asemb, line_type);
		else if (line_type == CMD_COMMENT_START || line_type == CMD_COMMENT_PROCCES)
			line_type = parse_command_comment(asemb, line_type);
		else if (line_type == INSTRUCTION)
			line_type = parse_unstruction(asemb);
		else
			line_type = 0;
	}

	printf("name = %s\n", asemb->prog_name);
	printf("comment = %s\n", asemb->comment);
	printf("rows = %i\n", asemb->row);
	return (1);
}	


int main(int ac, char **av)
{
	t_asm *asemb;

	asemb = init();

	if (ac != 2)
	{
		printf("%s\n", "AC ERROR");
		return (0);
	}

	//printf("%s\n", ft_strchr(LABEL_CHARS, '9'));

	asemb->fd = open(av[1], O_RDONLY);

	parse_file(asemb);

	// printf("%i\n", 1111 & 14);

	//printf("%s\n", g_type[0]);
	return (1);
}