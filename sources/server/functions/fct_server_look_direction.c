/*
** EPITECH PROJECT, 2018
** salut
** File description:
** les bros
*/

#include "struct.h"
#include "fcts.h"

void print_lines_left(int fd, t_env *e, int nbr_of_lines)
{
        int i = nbr_of_lines * -1;
        vec_t case_pos = e->pos_ia[fd];
        vec_t atm_pos = case_pos;

        for (int x = 1; x < nbr_of_lines; x++) {
		case_pos.x -= 1;
                atm_pos = case_pos;
                for (i = x * -1; i <= x; i++) {
                        atm_pos.y = case_pos.y - i;
                        print_case(fd, e, atm_pos);
                }
        }
}

void print_lines_right(int fd, t_env *e, int nbr_of_lines)
{
        int i = nbr_of_lines * -1;
	vec_t case_pos = e->pos_ia[fd];
	vec_t atm_pos = case_pos;

	for (int x = 1; x < nbr_of_lines; x++) {
		case_pos.x += 1;
		atm_pos = case_pos;
		for (i = x * -1; i <= x; i++) {
			atm_pos.y = case_pos.y - i;
			print_case(fd, e, atm_pos);
		}
	}
}

void print_lines_up(int fd, t_env *e, int nbr_of_lines)
{
 	int i = nbr_of_lines * -1;
	vec_t case_pos = e->pos_ia[fd];
	vec_t atm_pos = case_pos;

	for (int x = 1; x < nbr_of_lines; x++) {
		case_pos.y -= 1;
		atm_pos = case_pos;
		for (i = x * -1; i <= x; i++) {
			atm_pos.x = case_pos.x - i;
			print_case(fd, e, atm_pos);
		}
	}
}

void print_lines_down(int fd, t_env *e, int nbr_of_lines)
{
 	int i = nbr_of_lines * -1;
	vec_t case_pos = e->pos_ia[fd];
	vec_t atm_pos = case_pos;

	for (int x = 1; x < nbr_of_lines; x++) {
		case_pos.y += 1;
		atm_pos = case_pos;
		for (i = x * -1; i <= x; i++) {
			atm_pos.x = case_pos.x - i;
			print_case(fd, e, atm_pos);
		}
	}
}
