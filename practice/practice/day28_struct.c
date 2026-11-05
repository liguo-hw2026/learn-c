/*
 * day28_struct.c —— 第 5 周 第 1 天（结构体定义、访问、结构体数组与指针，3.2h）
 * 计划源知识点（outputs/李果_硬件转型48周_半量慢速计划.md 第5周第1天 line 300–304）：
 *   struct 定义与 typedef（翁恺 V1 P97–99、P104）、. 与 ->、结构体作为函数参数（传值 vs 传指针的代价）
 * 资源：📺 V1 P97–99（结构类型 / 结构与函数 / 结构中的结构）＋ P104（typedef）｜ 📄 D1「C 结构体 / C 共用体」
 * 硬件相关性：🟢 极高——MCU 固件里传感器读数、寄存器配置、设备描述符全是结构体；
 *   用指针传结构体既省栈上拷贝、又能原地改配置，是每天都会写的套路。
 * 衔接 day27：print_by_ptr 用 const Sensor* —— 只读参数，呼应 day27「const 全局只读→可留 Flash」思路。
 *
 * ⚠️ 对齐 / 位域是 day3–4 的内容，今天只观察 sizeof，不深究对齐规则。
 * ⚠️ 本日不含翁恺递归 / 链表（属更晚周），按步骤 3.5 避开前置缺口。
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>   // 根治中文控制台输出乱码（day23 已落地）
#endif

// ============ TODO（平铺；先预测后运行，预测写在代码行尾）============
// 【任务】
//   1) 看 V1 P96–97 + P104，理解 struct 定义、typedef、. 与 -> 的区别
//   2) 定义并初始化一个结构体，用 . 访问成员并打印
//   3) 取结构体指针，用 -> 访问成员并打印
//   4) 写两个函数：结构体【传值】 vs 【传指针】，观察谁在栈上拷贝了整个结构体
//   5) 自测（口述）：为什么结构体参数几乎总要用指针传？
// 【预测】（跑之前填，写在下面对应代码行尾）
//   - sizeof(Sensor) 是多少字节？我猜：____（成员 int+float+int，暂不考虑对齐）
//   - 传值函数里若改 r.temp，外面的 s.temp 会变吗？我猜：____不变（变 / 不变）
//   - 传指针函数里改 p->temp，外面的 s.temp 会变吗？我猜：____变（变 / 不变）
// 【完成标准】① 能写 struct+typedef；② 分清 . 与 -> 的适用对象；
//   ③ 用代码说明"传值拷贝整个结构体、传指针只拷指针本身"；④ 自测能答出指针传参的理由
// 【参考代码】（#pragma region 折叠 + 注释，先自己写再对照）
#pragma region day28 参考代码（预测完再对照）
/*
typedef struct {
    int   id;
    float temp;
    int   status;
} Sensor;

void print_by_value(Sensor r) {          // 传值：调用时把整个 r 在栈上拷贝一份
    printf("传值：id=%d temp=%.2f status=%d\n", r.id, r.temp, r.status);
}
void print_by_ptr(const Sensor* p) {     // 传指针：只拷贝 8 字节地址；const=只读不可改
    printf("传指针：id=%d temp=%.2f status=%d\n", p->id, p->temp, p->status);
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    Sensor s = { 1, 25.5f, 0 };
    printf("sizeof(Sensor) = %zu 字节\n", sizeof(Sensor));

    printf("用 . 访问：id=%d temp=%.2f status=%d\n", s.id, s.temp, s.status);

    Sensor* p = &s;
    printf("用 -> 访问：id=%d temp=%.2f status=%d\n", p->id, p->temp, p->status);

    print_by_value(s);   // 整个 s 被拷贝到 print_by_value 的栈帧
    print_by_ptr(&s);    // 只传 8 字节地址

    Sensor t = { 2, 30.0f, 0 };
    print_by_value(t);
    return 0;
}
*/
#pragma endregion

// ============ 你的实现区（解注/照抄折叠区，或自己写）============
typedef struct {
    int   id;
    float temp;
    int   status;
} Sensor;

void print_by_value(Sensor r) {
    printf("传值：id=%d temp=%.2f status=%d\n", r.id, r.temp, r.status);
}
void print_by_ptr(const Sensor* p) {
    printf("传指针：id=%d temp=%.2f status=%d\n", p->id, p->temp, p->status);
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    // TODO：先填【预测】，再补全下面，运行验证
    Sensor s = { 1, 25.5f, 0 };
    printf("sizeof(Sensor) = %zu 字节\n", sizeof(Sensor));//预测：int+float+int=16字节（暂不计对齐）

    printf("用 . 访问：id=%d temp=%.2f status=%d\n", s.id, s.temp, s.status);//预测：. 用于结构体变量本身

    Sensor* p = &s;
    printf("用 -> 访问：id=%d temp=%.2f status=%d\n", p->id, p->temp, p->status);//预测：-> 用于结构体指针

    print_by_value(s);   // 预测：整个 s 被拷贝到函数栈帧
    print_by_ptr(&s);    // 预测：只拷贝 8 字节地址；const 保证只读

    // 自测验证：传值拷贝的是副本，传指针能原地改原结构体
    Sensor t = { 2, 30.0f, 0 };
    print_by_value(t);
    return 0;
}
