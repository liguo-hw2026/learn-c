/*
 * day20 指针 vs 数组：三个区别（下）（第 4 周 第 4 天）
 * ---------------------------------------------------------------------------
 * 资源（已 B站 API 核对真实分 P 标题，2026-10-30）：
 *   📺 V1 翁恺《C语言》BV1XZ4y1S7e1：
 *        P83 9.1.4 指针与数组：为什么数组传进函数后的 sizeof 不对了
 *        P84 9.1.5 指针与 const：指针本身和所指的变量都可能 const
 *        P85 9.2.1 指针运算
 *      ⚠️ 计划原文把本日资源标为「V1 85 讲」，但本日核心是「三个区别·下」：
 *         sizeof(a) vs sizeof(p) 与 能否整体赋值 → 真实落在 P83（传参退化）+ P84（const 决定指针可否被改/改指向）；
 *         P85（指针运算）已在 day19 覆盖，本日仅作相邻复习，不重复 drill。
 *   📄 D1 菜鸟教程·C 指针的算术运算 / 指向指针的指针  https://www.runoob.com/cprogramming/c-pointer-arithmetic.html
 *
 * TODO ↔ 分 P 对照（锚定翁恺真实分 P，无翁恺 P 号的知识点不杜撰）：
 *   TODO1  sizeof(a) vs sizeof(p)          —— P83 指针与数组（数组 vs 指针的 sizeof 语义）
 *   TODO2  能否整体赋值（a=b 非法 / p=q 合法）—— P83 + P84（const 决定指针可否被改）
 *   TODO3  函数内 sizeof 退化              —— P83（"传进函数后 sizeof 不对了"实体证据）
 *   TODO4  const 指针三形态               —— P84 指针与 const
 *   三个区别总览：① 能否 ++（day19 上篇已 drill）② sizeof 语义（本日）③ 能否整体赋值（本日）
 *
 * 格式约定（2026-10 定）：
 *   【任务】【预测】平铺可见、不折叠；【参考代码】用 #pragma region 折叠，置于 /* *\/ 内防误编译。
 *   本文件统一 C89 风格（for 循环外置 i），匹配 MSVC 默认模式，参考代码解注即可跑。
 *   自己敲代码跑，不要只看参考。
 */

#include <stdio.h>

/* TODO3 需要的辅助函数：定义成"总是编译"的活函数（参考代码里调用它）。
   若暂不调用，MSVC /W3 下不会报错，只是未被引用。 */
void g(int arr[])
{
    printf("in g: sizeof(arr)=%zu\n", sizeof(arr));
}

int main(void)
{
    /* ===================== TODO1 sizeof(a) vs sizeof(p) ===================== */
    /* 【任务】
     * 定义 int a[5] = {10,20,30,40,50}; int *p = a;
     * 打印 sizeof(a) 与 sizeof(p)，看二者分别是多少字节、差几倍。
     */
    /* 【预测】
     * sizeof(a) = 5 * sizeof(int) = 20 字节（数组总大小，编译器记得 a 是 5 个 int）；
     * sizeof(p) = 8 字节（64 位下指针本身的尺寸，与指向什么无关）。
     * 关键：sizeof 是编译期运算符，对"数组名"取的是数组对象大小，对"指针变量"取的是地址变量的大小。
     */
    #pragma region TODO1 参考代码
    /*
    {
        int a[5] = {10, 20, 30, 40, 50};
        int *p = a;
        printf("sizeof(a)=%zu, sizeof(p)=%zu\n", sizeof(a), sizeof(p));
    }
    */
    #pragma endregion

    /* ===================== TODO2 能否整体赋值 ===================== */
    /* 【任务】
     * 试：int a[5], b[5]; 然后写 b = a;（取消注释看编译器报什么错）；
     * 再试：int *p = a, *q = b; p = q;（这行应合法，p 改为指向 b）。
     */
    /* 【预测】
     * b = a; 编译失败：数组名是"不可修改的左值"，不能整体赋值/不能互相拷贝地址；
     * p = q; 合法：指针变量可以重新指向别处（这正是它和数组名的第一大区别）。
     * 想拷贝数组内容要用 memcpy 或循环逐元素赋值，不能 b = a。
     */
    #pragma region TODO2 参考代码
    /*
    {
        int a[5] = {1,2,3,4,5};
        int b[5] = {0};
        // b = a;            // 取消注释 → 编译报错（数组不可整体赋值）
        int *p = a, *q = b;
        p = q;               // 合法：p 改指 b
        printf("p points to b[0]=%d\n", *p);
    }
    */
    #pragma endregion

    /* ===================== TODO3 函数内 sizeof 退化（P83 核心证据） ===================== */
    /* 【任务】
     * 在 main 里 int a[5]; 先打印 sizeof(a)，再调用上面定义的 g(a)，对比两处输出。
     */
    /* 【预测】
     * main 里 sizeof(a) = 20（数组本体）；
     * g 里 sizeof(arr) = 8（arr 本质是指针参数，数组早已退化为指针，sizeof 拿到指针大小）。
     * 这就是 P83 标题"传进函数后 sizeof 不对了"的实体证据——函数里再也拿不到数组元素个数。
     * ⚠️ 所以任何"数组当参数"的函数，都要额外传一个长度 n，不能靠 sizeof 算长度。
     */
    #pragma region TODO3 参考代码
    /*
    {
        int a[5] = {10,20,30,40,50};
        printf("in main: sizeof(a)=%zu\n", sizeof(a));
        g(a);
    }
    */
    #pragma endregion

    /* ===================== TODO4 const 指针三形态（P84） ===================== */
    /* 【任务】
     * 逐个试下面三行的"改动"是否会编译报错（取消注释观察）：
     *   const int *p1 = &x;   *p1 = 5;     // 所指内容不可改，指针本身可改
     *   int * const p2 = &x;  p2 = &y;     // 指针本身不可改，所指内容可改
     *   const int * const p3 = &x; *p3=5; p3=&y; // 都不可改
     */
    /* 【预测】
     * *p1 = 5; 报错（指向 const int，内容只读）；p1 = &y; 合法。
     * p2 = &y; 报错（p2 是 const 指针，指向固定）；*p2 = 5; 合法。
     * p3 两处改动都报错（双 const）。
     * 助记：const 在 * 左边 → 所指内容不可改；const 在 * 右边 → 指针本身不可改。
     */
    #pragma region TODO4 参考代码
    /*
    {
        int x = 10, y = 20;
        const int *p1 = &x;   // *p1 只读
        // *p1 = 5;          // 报错
        p1 = &y;              // 合法
        int * const p2 = &x;  // p2 指向固定
        *p2 = 5;              // 合法
        // p2 = &y;          // 报错
        const int * const p3 = &x;
        // *p3 = 5;          // 报错
        // p3 = &y;          // 报错
    }
    */
    #pragma endregion

    return 0;
}
