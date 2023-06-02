#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <string.h>
#include "rbt.h"

int main()
{
    rbt *t = rbt_init();
    int gd = CUSTOM, gm = CUSTOM_MODE(1200, 800);
    initgraph(&gd, &gm, "");
    char command[10] = "stop";

    settextstyle(10, 0, 8);
    setbkcolor(LIGHTGRAY);
    setfillstyle(1, BLACK);
    setcolor(BLACK);
    setlinestyle(0, 0, 3);


    printf("Здравствуйте! Добро пожаловать в программу визуализации красно-чёрного дерева.\n");
    printf("Вводите команды в консоль, и вы получите отрисовку красно-чёрного дерева на каждом этапе его балансировки.\n");
    printf("Вот список команд:\n"
           "add n - добавить число n в дерево;\n"
           "delete n - удалить число из дерева;\n"
           "stop - остановка работы программы.\n");
    printf("Каждая команда вводится с новой строки.\n"
           "Ввод чисел, превышающих 99, вызовет ошибки отрисовки. Пожалуйста, ограничтесь однозначными и двузначными числами.\n"
           "Приятного пользования!\n\n"
           "Пожалуйста, начните ввод:\n");

    do {
        scanf("%s", command);
        if (!strcmp(command, "add"))
        {
            int to_add;
            scanf("%d", &to_add);
            rbt_insert(t, to_add);
        }
        else if (!strcmp(command, "delete"))
        {
            int to_del;
            scanf("%d", &to_del);
            rbt_delete(t, to_del);
        }
        else if (!strcmp(command, "stop")) break;
        else
        {
            printf("Ошибка. Неизвестная команда.\n");
            exit(-2);
        }

    } while (1);

//    readkey();

    rbt_free(t);
    closegraph();
    return 0;

}
