/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:51:49 by bel-barb          #+#    #+#             */
/*   Updated: 2024/01/09 22:00:58 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

char str[] = "00000000";
int indexx = 0;

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
    return result;
}

void    server()
{
    signal(SIGUSR1, handle_sigusr1);
    signal(SIGUSR2, handle_sigusr2);
    int i = 7;
    // char *str = malloc(8 + 1);
    while (i >= 0)
    {
        pause();
        i--;
    }
    char x = binary_to_char(str);
    printf("%c", x);
}
int main()
{
    // int id = fork();
    printf("my pid is %d\n", getpid());
    int i = 0;
    while (i < 5)
    {
        server();
        i++;
    }
    // printf("%d %d\n", getpid(), getppid());
}