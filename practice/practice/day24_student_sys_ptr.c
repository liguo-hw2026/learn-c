/*
 * day24_student_sys_ptr.c —— 第 4 周 第 4 天（用指针重写学生成绩管理系统 · 上）
 * 翁恺 P 号：P80、P81、P82、P83（回看指针章：指针与变量 / 指针大小 / 野指针与 NULL / 指针与数组；无新增翁恺讲次）
 * 本日目标：把"学生成绩管理系统"用【指针版】重写，真正把 day10–day13 学的指针 / 动态内存用到小项目里
 * 衔接 day23：严守"谁申请谁释放"约定（malloc 在工厂函数或 main，free 由调用方负责；返回堆内存的接口不让被调函数既 malloc 又 free）
 * 资源：📺 V1 80–83 讲（回看，无新增视频）｜ 📄 D2「qsort」https://zh.cppreference.com/w/c/algorithm/qsort
 * 硬件相关性：🟢 高——嵌入式里学生表 / 传感器列表 / 配置项常用 struct + 动态数组；MCU 内存有限，动态分配后必须确保释放，否则长期运行泄漏宕机
 * 参考：day23_memory_errors2.c（泄漏计数器自检、返回堆内存约定）
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#ifdef _WIN32
#include <windows.h>   // 根治中文控制台输出乱码（day23 已落地）
#endif

// ============ 数据结构 ============
typedef struct {
    int id;
    char name[32];
    float score;
} Student;

// ============ TODO（平铺，解注运行看现象；参考代码在底部折叠区）============
// 【任务】把"学生成绩管理系统"用【指针版】重写，分四步：
//   1) 用 malloc 动态分配 N 个 Student：Student* arr = (Student*)malloc(N * sizeof(Student)); 判空；调用方负责 free
//   2) 函数接口全部改为【指针传参】：输入/输出数组用 Student* + 长度 n，不靠数组语法传整块
//   3) 实现：录入(input) / 按 id 查找(find_by_id) / 打印全部(print) —— 均用指针遍历 arr[i]（等价 *(arr+i)）
//   4) 自测：对比之前"数组版"，【列出至少 3 个指针版的改进点】（如：可动态决定 N / 函数无需知道数组真实大小 / 便于后续接 qsort）
// 【预测】指针版可动态决定 N、函数签名更通用、且 Student* 能直接传给 qsort 的比较函数；free 后无泄漏（用 day23 的 leak_check 验证）
// 【参考代码】（#pragma region 折叠 + 注释，解注或照抄改写；解注前先读一遍想清楚每个指针的指向）
#pragma region day24 参考代码（解注运行看现象）
/*
// —— 工厂函数：分配 N 个 Student 并返回指针（调用方负责 free）——
Student* create_students(int n) {
    Student* p = (Student*)malloc((size_t)n * sizeof(Student));
    if (!p) return NULL;          // 判空（day23 教训：malloc 可能失败）
    return p;                     // 返回堆指针，释放责任交给调用方
}

// —— 录入：指针传参 + 指针遍历 ——
void input_ptr(Student* p, int n) {
    for (int i = 0; i < n; i++) {
        printf("输入 学号 姓名 成绩（第%d个）: ", i + 1);
        scanf("%d %31s %f", &p[i].id, p[i].name, &p[i].score);  // p[i] 等价 *(p+i)
    }
}

// —— 打印：const 指针传参（只读，表明不修改）——
void print_ptr(const Student* p, int n) {
    for (int i = 0; i < n; i++)
        printf("%d\t%s\t%.1f\n", p[i].id, p[i].name, p[i].score);
}

// —— 按 id 查找：返回指向找到元素的指针，找不到返回 NULL ——
Student* find_by_id(const Student* p, int n, int id) {
    for (int i = 0; i < n; i++)
        if (p[i].id == id) return (Student*)&p[i];   // 返回元素地址（强转掉 const）
    return NULL;
}

// —— main 示范（解注整段运行）——
// int main(void) {
// #ifdef _WIN32
//     SetConsoleOutputCP(CP_UTF8);
// #endif
//     int n = 3;
//     Student* st = create_students(n);
//     if (st) {
//         input_ptr(st, n);
//         printf("--- 全部学生 ---\n");
//         print_ptr(st, n);
//         Student* hit = find_by_id(st, n, 2);
//         if (hit) printf("找到 id=2: %s %.1f\n", hit->name, hit->score);
//         else     printf("未找到 id=2\n");
//         free(st);                 // 调用方释放
//     }
//     return 0;
// }
*/
#pragma endregion

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);   // 控制台输出代码页设为 UTF-8，匹配源文件编码 → 中文正常显示
#endif
    // TODO：解注上方参考代码（或自己写指针版）跑通；验证动态分配 + 指针遍历 + free 无泄漏
    // 收工时用 day23 的 leak_check 思路确认 malloc/free 配平（本文件若加计数器可在 free 后打印差值）
    return 0;
}
