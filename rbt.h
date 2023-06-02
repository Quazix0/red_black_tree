#ifndef RBT_H_INCLUDED
#define RBT_H_INCLUDED

typedef struct node {
    int key; /// ���祭��
    int color; /// 0 - ����, 1 - ����
    int is_nil; /// ���� �� nil-㧫��
    struct node *left, *right, *parent; /// 㪠��⥫� �� ��⥩ � த�⥫�
} node;

typedef struct rbt {
    node *root; /// 㪠��⥫� �� ��७�
} rbt;

rbt *rbt_init();
/// ���樠������� ��ॢ�, �����頥� 㪠��⥫� �� ����

void free_node(node *n);
/// 㭨�⮦��� 㧥� � ��� �����ॢ��, �᢮������� ᮮ⢥�������� �� ������

void rbt_free(rbt *t);
/// 㭨�⮦��� ��ॢ� � �᢮������� ������

node *rbt_serach (rbt *t, int key);
/// ��室�� ����� � ������� ���箬 � �����頥� 㪠��⥫� �� ����, NULL �᫨ ��������

node *rbt_min (node *t);
/// �����頥� 㪠��⥫� �� ��������� �����

node *rbt_max (node *t);
/// �����頥� 㪠��⥫� �� ���ᨬ���� �����

void rbt_rotate_left (rbt *t, node *x);
/// ����� ��饭�� ����� ����� x

void rbt_rotate_right (rbt *t, node *x);
/// �ࠢ�� ��饭�� ����� ����� x

node *rbt_bst_insert (rbt *t, int key);
/// ��⠢�� ����� ��� ���� ��᭮-����� �-�, �����頥� 㪠��⥫� �� ��⠢����� �����

int rbt_insert (rbt *t, int key);
/// ��⠢�� ����� � ��ॢ�, �����頥� 0 � ��砥 �ᯥ�, -1 �᫨ ����� 㦥 ����

int rbt_delete(rbt *t, int key);
/// 㤠����� ����� ��ॢ�, �����頥� 0 � ��砥 �ᯥ�, -1 �᫨ ����� ���������

void rbt_print(const node *t);
/// �뢮��� � ���᮫� ������ ��ॢ� � ���浪� �����⠭�� � 㪠������ 梥� � த�⥫�

int rbt_draw_node(node *to_draw, int x, int y, int iter);
/// �㭪�� ���ᮢ�� �����ॢ� ��稭�� � ⥪�饣� 㧫�, �����頥� 0 �᫨ 㧥� �������, ���� -1

void rbt_draw(rbt *t);
/// �㭪�� ���ᮢ�� ��ॢ� � ����᪮� ����

void delete_case1(rbt *t, node *n);

void delete_case2(rbt *t, node *n);

void delete_case3(rbt *t, node *n);

void delete_case4(rbt *t, node *n);

void delete_case5(rbt *t, node *n);

void delete_case6(rbt *t, node *n);

node *brother(node *n);

int nil_or_black(node *n);

#endif // RBT_H_INCLUDED
