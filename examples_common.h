/*
Copyright 2009 Aris Adamantiadis

This file is part of the SSH Library

You are free to copy this file, modify it in any way, consider it being public
domain. This does not apply to the rest of the library though, but it is
allowed to cut-and-paste working code from this file to any license of
program.
The goal is to show the API in action. It's not a reference on how terminal
clients must be made or how a client should react.
*/
#ifndef EXAMPLES_COMMON_H_
#define EXAMPLES_COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <libssh/libssh.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>

#define COLS 4
#define CHARS 50
#define EVERY 20

typedef struct iplist
{
    char *ip;
    char *user;
    char *pawd;
    char *port;
    char *cmd;
    ssh_session session;
    ssh_channel channel;
    struct iplist *next;
}*ipinfo, ipList;

// 执行命令
int libssh(ipinfo iplist);

// ssh连接创建
ssh_session connect_ssh(char *ip,char *user,char *port,char *pawd);

// 验证
int authenticate_console(ssh_session session,char *password);

// knownhosts
int verify_knownhost(ssh_session session);

#endif /* EXAMPLES_COMMON_H_ */
