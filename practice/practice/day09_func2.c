/*
 * day09_func2.c - 第 2 周第 5 天 · 函数（下）：参数传递 / 本地变量 / 函数庶事·main / 头文件保护
 *                 （翁恺 V1 第 71–73 讲）
 *
 * ⚠️ 提示骨架：每题的"参考写法"用 #pragma region 折叠（见各 TODO 末尾）。
 *    VS 折叠：Ctrl+M, Ctrl+M 折叠/展开单个；Ctrl+M, Ctrl+O 折叠全部。
 * 方法：先预测后验证（predict-then-verify）。
 *
 * 📺 视频（B站分P，已用 API 核实真实标题 2026-10-19）：
 *    P71 7.2.2 参数传递
 *    P72 7.2.3 本地变量
 *    P73 7.2.4 函数庶事：一些有关函数的细节问题，main()是什么
 *    https://www.bilibili.com/video/BV1XZ4y1S7e1
 * 📄 参考：D1「C 函数 / C 作用域规则 / C 头文件」
 *
 * ✅ TODO ↔ 分P 对照（已复核：全部落在 P71–73 内）：
 *   TODO1  参数传递（值传递：形参是实参的拷贝）        → P71
 *   TODO2  本地变量（作用域 + 生命周期）               → P72
 *   TODO3  函数庶事·main()是什么（argc / argv）        → P73
 *   TODO4  函数庶事·头文件保护（多文件工程）           → P73 / D1
 *
 * ⚠️ 与计划原文的对齐说明（以真实分 P 为准，不超纲）：
 *   - 计划第 5 天写的「递归三要素」其实属于 P67–70，已在第 2 周第 4 天 TODO5
 *     （递归阶乘 + 迭代版）收尾，本日不重复。
 *   - 计划第 5 天写的「多文件工程与头文件保护」属 P73「函数庶事」+ D1 延伸，
 *     保留为 TODO4（嵌入式工程常态：.h 放原型，是所有 HAL 的组织方式）。
 *
 * 收工自测（能口述）：① 为什么 swap(int,int) 交换不了 main 里的变量（传值=传副本）；
 *      ② 本地变量为什么每次调用重新初始化、退出就消失（存在栈上）；
 *      ③ main 的 argc / argv 分别表示什么，argv[0] 是什么；
 *      ④ 头文件 #ifndef/#define/#endif 守卫是干什么的；
 *      ⑤ 复习（第 2 周第 4 天）：递归过深会怎样（栈溢出）。
 *
 * 🔧 硬件相关性：
 *   - 参数传递 🟢 高相关：HAL 库函数全是值传递或传指针（W3 才学指针）；
 *     理解"传副本"才能看懂为什么有些 API 要你传变量的地址。
 *   - 本地变量 / 栈 🟢 高相关：MCU 栈只有几 KB，所有本地变量都挤在栈上，
 *     递归/大数组会吃掉它 → 栈溢出 → hardfault。这条和递归爆栈是同一根源。
 *   - 头文件保护 🟢 高相关：你以后写的每个驱动 .h 都必须有 include guard，
 *     否则被多处 #include 就重定义报错。今天就要养成。
 */

#include <stdio.h>
#include "mymath.h"   // TODO4：多文件 + 头文件保护（见 mymath.h / mymath.c）

void swap(int, int);
void foo(void);

//int main(void)
//{
//    /* ===== TODO 1：参数传递（值传递）→ P71 =====
//     * 任务：先看 swap 的定义（文件尾）。在 main 里调用 swap(x, y)，
//     *      观察调用前后 x、y 是否真的被交换。
//     * 预测：swap 之后，x 仍是 3、y 仍是 5 —— 没交换。
//     *       原因：C 是传值调用，swap 拿到的是 x、y 的"副本"，
//     *       它交换的是副本，main 里的原变量纹丝不动。
//     
//    int x = 3, y = 5;
//    swap(x, y);
//    printf("after swap: x=%d y=%d\n", x, y);   // 预测 x=3 y=5
//    */
//    /* ===== TODO 2：本地变量（作用域 + 生命周期）→ P72 =====
//     * 任务：看 foo 的定义（文件尾，里面有自己的本地变量 x）。
//     *      在 main 里也定义一个 x=99，先调一次 foo，再打印 main 的 x，再调一次 foo。
//     * 预测：main 的 x 始终是 99（和 foo 的 x 互不干扰）；
//     *       foo 每调用一次都从 10 重新开始 → 两次都打印 11（不是 12，说明不累积）。
//     
//    int x = 99;
//    foo();
//    printf("main x=%d\n", x);   // 预测 99
//    foo();                      // 预测再次 11
//    */
//    /* ===== TODO 4：头文件保护（多文件）→ P73 / D1 =====
//     * 任务：square 的声明在 mymath.h、实现在 mymath.c（已随工程链接）。
//     *       这里直接调用它，体会"声明放 .h、实现放 .c"。
//     * 预测：square(6) = 36
//    printf("square(6) = %d\n", square(6));
//    */
//    return 0;
//}
#pragma region TODO3 参考（main 换签名：argc/argv - 展开看，写自己代码不需要）
    
    // ⚠️ 做 TODO3 时：把上面的 int main(void){...} 整段注释掉，
    //    换成下面这个带参数的 main，再编译运行。
    int main(int argc, char *argv[])
    {
        // argc = 命令行参数个数（含程序名本身，argv[0]）
        // argv = 参数字符串数组
        printf("argc = %d\n", argc);
        for (int i = 0; i < argc; i++)
        {
            printf("argv[%d] = %s\n", i, argv[i]);
        }
        return 0;
    }
    // 怎么传参运行：VS 里 右键项目 → 属性 → 配置属性 → 调试 → 命令参数，填 `hello world`
    // 预测：argc=3, argv[0]=程序名, argv[1]="hello", argv[2]="world"
 
#pragma endregion

// ---- 以下为各 TODO 的函数定义（全部激活，main 里解注调用即可测试）----

void swap(int a, int b)
{
    // 交换的是 a、b 这两个"副本"，对 main 里的原变量没有影响
    int t = a; a = b; b = t;
}

void foo(void)
{
    int x = 10;      // foo 的本地变量，每次进入 foo 都重新创建并初始化为 10
    x++;
    printf("foo  x=%d\n", x);
}
