#include "examples_common.h"

int main(int argc, char **argv)
{
    FILE *file = fopen("iplist", "r");
    char *strings = malloc(CHARS);
    char *point[COLS];
    char *p;
    int i;
    // 声明首节点和尾节点并分配地址
    ipinfo head, tail;
    head = tail = (ipinfo)malloc(sizeof(ipList));
    tail->next = NULL;

    // 命令行
    if (argc != 2)
    {
        fprintf(stderr, "请使用: ./ssh 命令\n");
        return -1;
    }

    while (fgets(strings, CHARS, file) != NULL) {
        for (i = 0, p = strtok(strings, " "); p != NULL && i < COLS; p = strtok(NULL, " "), i++)
            point[i] = p;
        // 新建临时节点
        ipinfo q = (ipinfo)malloc(sizeof(ipList));
        q->ip=malloc(EVERY);
        q->user=malloc(EVERY);
        q->pawd=malloc(EVERY);
        q->port=malloc(EVERY);
        // 字符串拷贝,要不然还是指向的是strings
        strcpy(q->ip, point[0]);
        strcpy(q->user, point[1]);
        strcpy(q->pawd, point[2]);
        strcpy(q->port, point[3]);
        q->cmd = argv[1];
        q->next = NULL;
        // 新节点赋值给尾节点
        tail->next = q;
        tail = q;
    }

    // 循环节点进行传包
    while (head->next != NULL) {
        head = head->next;
        if (libssh(head) < 0)
        {
            fprintf(stderr, "传包开始失败,请检查\n");
            return -1;
        }
    }

    return 0;
}
