/*
 * day25_student_sys_ptr_qsort.c —— 第 4 周 第 5 天（用指针重写学生成绩管理系统 · 下）
 * 翁恺 P 号：P84、P85、P86（回看指针章：指针与 const / 指针运算 / 动态内存；无新增翁恺讲次）
 * 本日目标：在 day24 指针版框架上，加 qsort 排序（按学号 / 姓名 / 成绩）+ 按姓名查找 + 结果写文件
 * 资源：📺 V1 84–86 讲（回看，无新增视频）｜ 📄 D2「qsort」https://zh.cppreference.com/w/c/algorithm/qsort
 * 硬件相关性：🟢 高——嵌入式里"对一组传感器读数 / 配置项排序、按标识查找、导出到文件 / Flash"是日常操作；
 *            qsort 是标准库现成工具，会写比较函数 = 会把它接到任意自定义结构上（与 day24「Student* + 长度」接口一脉相承）
 * 参考：day24_student_sys_ptr.c（指针版框架：Student 定义 / create_students / input_ptr / print_ptr / find_by_id，本日复用其逻辑）
 */

#define _CRT_SECURE_NO_WARNINGS   // ⚠️ 必须在 include 之前定义，才能压掉 scanf 的 C4996 弃用警告
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>   // 根治中文控制台输出乱码（day23 已落地）
#endif

// ============ 数据结构（与 day24 同，复用，结构体正式教学见第 5 周）============
typedef struct {
    int id;
    char name[32];
    float score;
} Student;

// ============ 📌【前置知识补给 · 函数指针最小前置】（正式系统教学见第 5 周 · 函数指针）============
// 本日要用 qsort，它的比较函数参数是【函数指针】。先建立直觉，不用一次吃透：
//   - 你已经懂"指针可以指向 int / char / Student"——存的是某块数据的地址。
//   - 函数也会被加载进内存、也有地址。指向函数的指针就叫【函数指针】，存的是"某段代码的入口地址"。
//     指向数据、指向代码，本质都是"一个地址 + 一个类型"。
//   - 比较函数签名：`int (*cmp)(const void* a, const void* b)`
//       * 圆括号不能省：`(*cmp)` 表示 cmp 是个指针；去掉括号会变成"返回 int* 的函数"，完全两回事。
//       * `void*` = "我还不知道具体类型的一块内存"——因为 qsort 是通用排序机，它不知道你的元素是 Student 还是别的。
//       * 返回值约定（qsort 的规矩）：<0 → a 应排在 b 前面；>0 → a 应排在 b 后面；==0 → 相等。
//   - 怎么用：qsort 内部反复调用你的 cmp 来定夺是否交换；你在 cmp 里把 void* 转回 `Student*` 再比具体字段。
//   今天只要：能看懂下面三个 cmp 写法、能照着写出"按某字段排序"即可；深讲留到第 5 周函数指针专讲。

// ============ TODO（平铺，解注运行看现象；参考代码在底部折叠区）============
// 【任务】在 day24 指针版框架上，加三件事：
//   1) qsort 排序：写三个比较函数 —— cmp_by_id（按学号升序）/ cmp_by_name（按姓名字典序）/ cmp_by_score（按成绩升序）
//      调用示例：qsort(st, n, sizeof(Student), cmp_by_score);  排序后打印看顺序对不对
//   2) 按姓名查找：find_by_name(const Student* p, int n, const char* name) —— 找到返回指针、找不到返回 NULL（同 find_by_id 套路，用 strcmp）
//   3) 写文件：save_to_file(const Student* p, int n, const char* path) —— fopen(path,"w") 打开、fprintf 逐行写、fclose 关闭；
//      写完后用文本编辑器打开 students.txt 核对内容是否和打印一致
//   4) 自测（计划源要求）：把代码 push 到 GitHub；README 写清【编译命令 + 功能 + 已知问题】
// 【预测】qsort 后打印顺序按所选字段排好；find_by_name 查一个不存在的姓名应返回 NULL；save_to_file 生成的文件内容应与打印内容一致
// 【参考代码】（#pragma region 折叠 + 注释，解注或照抄改写；解注前先读一遍想清楚每个指针的指向）
#pragma region day25 参考代码（解注运行看现象）
/*
// —— qsort 比较函数：按学号升序 ——
int cmp_by_id(const void* a, const void* b) {
    const Student* sa = a; const Student* sb = b;
    return (sa->id > sb->id) - (sa->id < sb->id);   // 经典三目化简：>0 / <0 / 0
}
// —— 按姓名字典序（strcmp 返回值正好符合 qsort 约定）——
int cmp_by_name(const void* a, const void* b) {
    const Student* sa = a; const Student* sb = b;
    return strcmp(sa->name, sb->name);
}
// —— 按成绩升序 ——
int cmp_by_score(const void* a, const void* b) {
    const Student* sa = a; const Student* sb = b;
    return (sa->score > sb->score) - (sa->score < sb->score);
}
// —— 按姓名查找（复用 find_by_id 套路，比较换成 strcmp）——
Student* find_by_name(const Student* p, int n, const char* name) {
    for (int i = 0; i < n; i++)
        if (strcmp(p[i].name, name) == 0) return (Student*)&p[i];
    return NULL;
}
// —— 写文件 ——
int save_to_file(const Student* p, int n, const char* path) {
    FILE* f = fopen(path, "w");
    if (!f) { printf("打开文件失败: %s\n", path); return -1; }
    for (int i = 0; i < n; i++)
        fprintf(f, "%d\t%s\t%.1f\n", p[i].id, p[i].name, p[i].score);
    fclose(f);
    return 0;
}
// —— main 示范（解注整段运行）——
// int main(void) {
// #ifdef _WIN32
//     SetConsoleOutputCP(CP_UTF8);
// #endif
//     int n = 3;
//     Student* st = create_students(n);
//     if (!st) return 1;
//     input_ptr(st, n);
//     printf("--- 录入后（未排序）---\n");
//     print_ptr(st, n);
//
//     qsort(st, n, sizeof(Student), cmp_by_score);
//     printf("--- 按成绩排序后 ---\n");
//     print_ptr(st, n);
//
//     Student* hit = find_by_name(st, n, "Alice");   // 换成你实际录入的某个姓名
//     if (hit) printf("找到 %s: id=%d score=%.1f\n", hit->name, hit->id, hit->score);
//     else     printf("未找到该姓名\n");
//
//     if (save_to_file(st, n, "students.txt") == 0)
//         printf("已写入 students.txt（请打开核对）\n");
//
//     free(st);
//     return 0;
// }
*/
#pragma endregion

// —— 复用 day24 的函数原型（本文件自包含，day24 已不参与编译）——
Student* create_students(int n);
void input_ptr(Student* p, int n);
void print_ptr(const Student* p, int n);
Student* find_by_id(const Student* p, int n, int id);
int cmp_by_id(const void* a, const void* b);
int cmp_by_name(const void* a, const void* b);
int cmp_by_score(const void* a, const void* b);
Student* find_by_name(const Student* p, int n, const char* name);
int save_to_file(const Student* p, int n, const char* path);

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    // TODO：解注上方参考代码（或自己写）跑通；实测 qsort 排序 / find_by_name / save_to_file 三件事
    // 提示：main 里 find_by_name 的 "Alice" 要换成你本次实际录入的某个姓名才能真正验证到找到分支
    int n = 3;
    Student* st = create_students(n);
    if (!st) return 1;
    input_ptr(st, n);
    printf("--- 录入后（未排序）---\n");
    print_ptr(st, n);

    qsort(st, n, sizeof(Student), cmp_by_id);
    printf("--- 按学号排序后 ---\n");
    print_ptr(st, n);

    qsort(st, n, sizeof(Student), cmp_by_name);
    printf("--- 按姓名排序后 ---\n");
    print_ptr(st, n);

    qsort(st, n, sizeof(Student), cmp_by_score);
    printf("--- 按成绩排序后 ---\n");
    print_ptr(st, n);

    Student* hit = find_by_name(st, n, "Bob");
    if (hit) printf("找到 %s: id=%d score=%.1f\n", hit->name, hit->id, hit->score);
    else     printf("未找到该姓名\n");

  /*  if (save_to_file(st, n, "students.txt") == 0)
        printf("已写入 students.txt（请打开核对）\n");*/

    free(st);
    return 0;
}

Student* create_students(int n) {
    Student* p = (Student*)malloc((size_t)n * sizeof(Student));
    if (!p) return NULL;
    return p;
}
void input_ptr(Student* p, int n) {
    for (int i = 0; i < n; i++) {
        printf("输入 学号 姓名 成绩（第%d个）: ", i + 1);
        scanf("%d %31s %f", &p[i].id, p[i].name, &p[i].score);
    }
}
void print_ptr(const Student* p, int n) {
    for (int i = 0; i < n; i++)
        printf("%d\t%s\t%.1f\n", p[i].id, p[i].name, p[i].score);
}
Student* find_by_id(const Student* p, int n, int id) {
    for (int i = 0; i < n; i++)
        if (p[i].id == id) return (Student*)&p[i];
    return NULL;
}
int cmp_by_id(const void* a, const void* b) {
    const Student* sa = a; const Student* sb = b;
    return (sa->id > sb->id) - (sa->id < sb->id);
}
int cmp_by_name(const void* a, const void* b) {
    const Student* sa = a; const Student* sb = b;
    return strcmp(sa->name, sb->name);
}
int cmp_by_score(const void* a, const void* b) {
    const Student* sa = a; const Student* sb = b;
    return -((sa->score > sb->score) - (sa->score < sb->score));
}
Student* find_by_name(const Student* p, int n, const char* name) {
    for (int i = 0; i < n; i++)
        if (strcmp(p[i].name, name) == 0) return (Student*)&p[i];
    return NULL;
}
int save_to_file(const Student* p, int n, const char* path) {
    FILE* f = fopen(path, "w");
    if (!f) { printf("打开文件失败: %s\n", path); return -1; }
    for (int i = 0; i < n; i++)
        fprintf(f, "%d\t%s\t%.1f\n", p[i].id, p[i].name, p[i].score);
    fclose(f);
    return 0;
}
