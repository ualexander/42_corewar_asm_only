/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 17:56:13 by vsanta            #+#    #+#             */
/*   Updated: 2019/09/29 18:18:07 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"
# include "op.h"

#ifndef ASM_H
# define ASM_H

#define LINE_EMPTY 10
#define LINE_COMMENT 20
#define CMD_NAME_START 30
#define CMD_NAME_PROCCES 31
#define LINE_CMD_COMMENT 40
#define LINE_INST 50
#define LINE_INST_LABEL 60

#define CMD_BRACKETS '"'
#define SPACE_SYMBOLS " \t"
#define CMD_NUMBERS 16

int get_line_type(char *line);

typedef struct		s_asm
{
	int				fd;
	char			*parse_line;
 	unsigned int	magic;
 	char			prog_name[PROG_NAME_LENGTH + 1];
 	unsigned int	prog_size;
 	char			comment[COMMENT_LENGTH + 1];
}					t_asm;

typedef enum
{
	COMMAND,
	STRING,
	LABEL,
	OPERATOR,
	REGISTER,
	DIRECT,
	DIRECT_LABEL,
	INDIRECT,
	INDIRECT_LABEL,
	SEPARATOR,
	NEW_LINE,
	END
}	t_type;

static char				*g_type[] = {
	"COMMAND",
	"STRING",
	"LABEL",
	"OPERATOR",
	"REGISTER",
	"DIRECT",
	"DIRECT_LABEL",
	"INDIRECT",
	"INDIRECT_LABEL",
	"SEPARATOR",
	"NEW_LINE",
	"END"
};

typedef struct	s_op
{
	char		*name;
	char		code;
	char		args_num;
	char		args_types_code;
	char		args_types[3];
	char		t_dir_size;
}				t_op;

static t_op		g_op[16] = {
	{"live", 1, 1, 0, {T_DIR, 0, 0}, 4},
	{"ld", 2, 2, 1, {T_DIR | T_IND, T_REG, 0}, 4},
	{"st", 3, 2, 1, {T_REG, T_REG | T_IND, 0}, 4},
	{"add", 4, 3, 1, {T_REG, T_REG, T_REG}, 4},
	{"sub", 5, 3, 1, {T_REG, T_REG, T_REG}, 4},
	{"and", 6, 3, 1, {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG}, 4},
	{"or", 7, 3, 1, {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG}, 4},
	{"xor", 8, 3, 1, {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG}, 4},
	{"zjmp", 9, 1, 0, {T_DIR, 0, 0}, 2},
	{"ldi", 10, 3, 1, {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG}, 2},
	{"sti", 11, 3, 1, {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR}, 2},
	{"fork", 12, 1, 0, {T_DIR, 0, 0}, 2},
	{"lld", 13, 2, 1, {T_DIR | T_IND, T_REG, 0}, 4},
	{"lldi", 14, 3, 1, {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG}, 2},
	{"lfork", 15, 1, 0, {T_DIR, 0, 0}, 2},
	{"aff", 16, 1, 1, {T_REG, 0, 0}, 4}
};		

#endif
