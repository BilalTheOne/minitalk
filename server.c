/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:51:49 by bel-barb          #+#    #+#             */
/*   Updated: 2024/01/10 11:18:07 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include "libft/libft.h"

char str[] = "00000000";
int indexx = 0;

void reset_str()
{
    indexx = 0;
    int i = 0;
    while (str[i] != '\0')
    {
        str[i] = '0';
        i++;
    }
}
void    handle_sigusr1(int sig)
{
    (void)sig;
    str[indexx++] = '1';
}
void    handle_sigusr2(int sig)
{
    (void)sig;
    str[indexx++] = '0';
}
char binary_to_char(const char *binary) {
    char result = 0;
    while (*binary) {
        result = (result << 1) | (*binary - '0');
        binary++;
    }
    reset_str();
    return result;
}

void    server()
{
    signal(SIGUSR1, handle_sigusr1);
    signal(SIGUSR2, handle_sigusr2);
    reset_str();
    int i = 7;
    // char *str = malloc(8 + 1);
    while (i >= 0)
    {
        pause();
        i--;
    }
    char x = binary_to_char(str);
    write(1, &x, 1);
    // fflush(stdout);
}
#include <fcntl.h>
int main()
{
    
    printf("my pid is %d\n", getpid());
    while (1)
        server();
    // printf("%d %d\n", getpid(), getppid());
}