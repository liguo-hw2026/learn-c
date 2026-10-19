/*
 * day08_func.c - 第 2 周第 4 天 · 函数：定义、调用、返回、原型（翁恺 V1 第 67–70 讲）
 *
 * ⚠️ 提示骨架：每题的"参考写法"用 #pragma region 折叠（见各 TODO 末尾）。
 *    VS 折叠：Ctrl+M, Ctrl+M 折叠/展开单个；Ctrl+M, Ctrl+O 折叠全部。
 * 方法：先预测后验证（predict-then-verify）。
 *
 * 📺 视频（B站分P，已用 API 核实真实标题）：
 *    P67 初见函数 / P68 函数的定义和使用 / P69 从函数中返回 / P70 函数原型
 *    https://www.bilibili.com/video/BV1XZ4y1S7e1
 * 📄 参考：D1「C 函数 / C 作用域规则 / C 头文件」
 *
 * ✅ TODO ↔ 分P 对照（已复核：全部落在 P67–70 内）：
 *   TODO1  初见函数：把重复代码抽成函数              → P67
 *   TODO2  函数的定义和使用：带参数、有返回值         → P68
 *   TODO3  从函数中返回：多个 return / void 提前返回  → P69
 *   TODO4  函数原型：定义放到 main 之后，前面加声明   → P70
 *   TODO5  计划自测题：递归阶乘 + 改成迭代版          → 综合应用
 *
 * ⚠️ 延后项（不在 P67–70，今日不做）：
 *   ① 参数传递（值传递 vs 地址传递）→ P71
 *   ② 本地变量 / 栈帧与生命周期      → P72
 *   ③ 函数庶事与 main()              → P73
 *   以上三项属 **第 2 周第 5 天**（V1 71–73 讲）。
 *
 * 收工自测（能口述）：① 为什么要写函数（复用/分工/隔离）；
 *      ② 函数原型有什么用、为什么定义能放在调用之后；
 *      ③ 递归和迭代解同一个问题，各自的代价是什么。
 *
 * 🔧 硬件相关性：
 *   - 函数拆分 🟢 高相关：驱动就是一堆小函数（init/read/write/ioctl），
 *     外设寄存器操作必须封装，裸机主循环才清爽
 *   - 函数原型 / 头文件 🟢 高相关：多文件工程 = .c + .h，.h 里放的就是原型，
 *     这是所有 SDK（STM32 HAL、ESP-IDF）的组织方式
 *   - 递归 ⚠️ 谨慎：MCU 栈只有几 KB，递归过深直接爆栈。
 *     嵌入式里能迭代就别递归——这条要记住
 *
 * 说明：本文件顶部**不再**预置工具函数——今天你要自己从头写函数（P67–70）。
 */

#include <stdio.h>
void print_line(void);
int add(int, int);
int max2(int, int);
int is_prime(int);
void show(int);
int fact(int);
int fact_iter(int);

int main(void)
{
    /* ===== TODO 1：初见函数 —— 把重复代码抽成函数 → P67 =====
     * 任务：先写一段"打印一行分隔线"的代码并连续用两次；再把它抽成
     *       void print_line(void) { printf("----------\n"); }
     *       在 main 里调用两次，体会"同一段代码只写一遍"。
     * 预测：调用两次 → 打印两行分隔线，输出与重复写两遍完全一致。
    
    print_line();
    print_line();
    */
#pragma region TODO1 参考（展开看，写自己代码不需要）
    /*
    void print_line(void) {
        printf("----------\n");
    }
    // main 里：
    print_line();
    printf("hello\n");
    print_line();
    */
#pragma endregion

    /* ===== TODO 2：函数的定义和使用 —— 带参数、有返回值 → P68 =====
     * 任务：写两个函数并调用打印：
     *       int add(int a, int b)  → 返回 a+b
     *       int max2(int a, int b) → 返回较大者
     * 预测：add(3,5) → 8；max2(3,5) → 5；max2(5,3) → 5。

    printf("sum is:%d\n", add(3, 5));
    printf("max2 is:%d\n", max2(3, 5));
    printf("max2 is:%d\n", max2(5, 3));
    */
#pragma region TODO2 参考（展开看，写自己代码不需要）
    /*
    int add(int a, int b) { return a + b; }
    int max2(int a, int b) { return (a > b) ? a : b; }
    // main 里：
    printf("add=%d  max=%d\n", add(3, 5), max2(3, 5));
    */
#pragma endregion

    /* ===== TODO 3：从函数中返回 —— 多个 return / void 提前返回 → P69 =====
     * 任务：① int is_prime(int x)：x<2 直接 return 0；找到因子 return 0；循环完 return 1。
     *       ② void show(int x)：若 x<0 则 printf("negative\n") 后 return（提前退出），
     *          否则 printf("x=%d\n", x)。
     * 预测：is_prime(7) → 1；is_prime(9) → 0；is_prime(1) → 0；
     *       show(-5) 只打印 "negative"，不打印 "x=..."。
    int x = 0;
    printf("enter the number:\n");
    scanf("%d",&x);
    show(x);
    if (x >= 0) {
        if (is_prime(x))
            printf("%d is prime.\n", x);
        else
            printf("%d is not prime.\n", x);
    }
    */
#pragma region TODO3 参考（展开看，写自己代码不需要）
    /*
    int is_prime(int x) {
        if (x < 2) return 0;
        for (int i = 2; i * i <= x; i++)
            if (x % i == 0) return 0;
        return 1;
    }
    void show(int x) {
        if (x < 0) { printf("negative\n"); return; }
        printf("x=%d\n", x);
    }
    // main 里：
    printf("%d %d %d\n", is_prime(7), is_prime(9), is_prime(1));
    show(-5);
    */
#pragma endregion

    /* ===== TODO 4：函数原型 —— 定义放到 main 之后 → P70 =====
     * 任务：把 max2 的**定义整体挪到 main 之后**，在 main 之前只留一句声明：
     *       int max2(int a, int b);      ← 这就是函数原型
     *       ① 加上原型 → 编译通过、结果正常
     *       ② 把原型那行注释掉再编译 → 观察 MSVC 报什么错（C4013："未定义；假定返回 int"）
     * 预测：有原型 → 正常输出 5；无原型 → 编译报错/警告，提示找不到 max2 的声明。
     * 要点：原型 = 告诉编译器"这个函数长什么样"，所以定义可以放在后面、甚至放在别的 .c 文件里。
     
    printf("max2 is:%d\n", max2(3, 5));
    printf("max2 is:%d\n", max2(5, 3));
     */
#pragma region TODO4 参考（展开看，写自己代码不需要）
    /*
    int max2(int a, int b);      // ← 函数原型（写在 main 之前）

    int main(void) {
        printf("max=%d\n", max2(3, 5));
        return 0;
    }

    int max2(int a, int b) {     // ← 真正的定义（在 main 之后）
        return (a > b) ? a : b;
    }
    */
#pragma endregion

    /* ===== TODO 5：计划自测题 —— 递归阶乘 + 改成迭代版 =====
     * 任务：① 递归版 int fact(int n)：n<=1 返回 1，否则返回 n*fact(n-1)
     *       ② 再写迭代版 int fact_iter(int n)：for 循环累乘
     *       两个都算 n=5，对比结果。
     * 预测：fact(5) → 120；fact_iter(5) → 120。
     * 思考（口述即可）：递归写着短，但每递归一层就压一帧栈；MCU 栈只有几 KB，
     *       层数一多就爆。同一个问题能写成循环就别写递归。
     
int x = 5;
printf("the fact is:%d\n", fact(x));
printf("the fact is:%d\n", fact_iter(x));
*/
#pragma region TODO5 参考（展开看，写自己代码不需要）
    /*
    int fact(int n) {
        if (n <= 1) return 1;
        return n * fact(n - 1);
    }
    int fact_iter(int n) {
        int r = 1;
        for (int i = 2; i <= n; i++) r *= i;
        return r;
    }
    // main 里：
    printf("fact=%d  iter=%d\n", fact(5), fact_iter(5));
    */
#pragma endregion

    return 0;
}
void print_line(void) {
    printf("------------\n");
}
int add(int a, int b) {
    int sum = 0;
    sum = a + b;
    return sum;
}
int max2(int a, int b) {
    int max = 0;
    if (a > b)
        max = a;
    else if (a < b)
        max = b;
    else
        max = 0;
    return max;
}
int is_prime(int x) {
    if (x < 2)
        return 0;
    else 
        for (int i = 2; i < x; i++) {
            if (x % i == 0) {
                return 0;
            }
        }
    return 1;
}
void show(int x) {
    if (x < 0) {
        printf("negative!\n");
        return;
    }
    else {
        printf("the number is:%d\n", x);
        return;
    }
}
int fact(int x) {
    if (x <= 1)
        return 1;
    return x * fact(x - 1);
}
int fact_iter(int x) {
    int f = 1;
    for (int i = 1; i <= x; i++)
        f = i * f;
    return f;
}