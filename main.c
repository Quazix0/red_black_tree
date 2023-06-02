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


    printf("��ࠢ����! ���� ���������� � �ணࠬ�� ���㠫���樨 ��᭮-��୮�� ��ॢ�.\n");
    printf("������ ������� � ���᮫�, � �� ������ ���ᮢ�� ��᭮-��୮�� ��ॢ� �� ������ �⠯� ��� ������஢��.\n");
    printf("��� ᯨ᮪ ������:\n"
           "add n - �������� �᫮ n � ��ॢ�;\n"
           "delete n - 㤠���� �᫮ �� ��ॢ�;\n"
           "stop - ��⠭���� ࠡ��� �ணࠬ��.\n");
    printf("������ ������� �������� � ����� ��ப�.\n"
           "���� �ᥫ, �ॢ����� 99, �맮��� �訡�� ���ᮢ��. ��������, ��࠭����� ��������묨 � ��㧭��묨 �᫠��.\n"
           "���⭮�� ���짮�����!\n\n"
           "��������, ��筨� ����:\n");

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
            printf("�訡��. �������⭠� �������.\n");
            exit(-2);
        }

    } while (1);

//    readkey();

    rbt_free(t);
    closegraph();
    return 0;

}
