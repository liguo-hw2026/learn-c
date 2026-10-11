// day02：数据类型、变量、运算符与表达式
// 翁恺 C 语言 第 11-19 讲
//
// 练习目标：
//   1. 用 sizeof 打印各类型在本机上的真实字节数
//   2. 验证 char c = 200 打印出来是什么、为什么
//   3. 验证整数溢出与浮点精度
//
// TODO: 下面的内容由你自己补充完成，不要直接抄答案
//       先预测输出结果 -> 再运行验证 -> 预测错了就把原因写进注释

#include <stdio.h>

int main(void)
{
    // 练习 1：sizeof 六种基本类型（sizeof 返回 size_t，用 %zu 打印）
    // TODO: 补齐 char / short / int / long / float / double
    printf("char   : %zu\n", sizeof(char));

    // 练习 2：char c = 200 打印出来是什么？先预测再验证
    char c = 200;
    printf("char c = 200 -> %d\n", c);

    // 练习 3：整数溢出（int 最大值加 1 会怎样）
    // TODO: 用 limits.h 里的 INT_MAX 试试

    // 练习 4：浮点精度（0.1 加 10 次等于 1.0 吗）
    // TODO

    return 0;
}
