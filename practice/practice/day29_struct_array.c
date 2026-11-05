/*
 * day29_struct_array.c —— 第 5 周 第 2 天（结构体数组、嵌套结构体、初始化器，3.2h）
 * 计划源知识点（outputs/李果_硬件转型48周_半量慢速计划.md 第5周第2天 line 306–310）：
 *   结构体数组、嵌套结构体、初始化器（翁恺 V1 P98–99、P104）
 * 资源：📺 V1 P98–99 讲（结构类型 / 结构与函数 / 结构中的结构）＋ P104（typedef）｜ 📄 D1「C 结构体 / C 共用体」
 * 硬件相关性：🟢 极高——固件里传感器采样常存成结构体数组（环形缓冲 / 历史记录）；
 *   设备描述符常是"嵌套结构体"（Device 含 Sensor、含 Config）。
 * 衔接 day28：day28 学了 . 与 ->、传值/传指针；今天加"数组 + 嵌套 + 初始化器"，
 *   以及"返回结构体"——返回结构体 = 调用处得到一份拷贝（对比 day28 传指针原地改）。
 * ⚠️ 本日不含对齐/位域（属 day3–4），只观察。
 *
 * ⭐ 甘 2026-11-05 新约定（练习日骨架）：实现区只放【练习题题目 + 空壳函数】，
 *   完整参考代码放 #pragma region 折叠区（注释围起来防误编译），由甘本人手敲实现。
 *   本文件即按此约定：下方"你的实现区"只有函数签名/空壳 + 题目，不要直接解注折叠区当作业交。
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>   // 根治中文控制台输出乱码（day23 已落地）
#endif

// ============ TODO（平铺；先预测后实现，预测写在代码行尾）============
// 【任务】
//   1) 看 V1 P98–99 + P104，理解结构体数组、嵌套结构体、初始化器
//   2) 定义嵌套结构体（例如 Device 含一个 Sensor 成员 + 设备名），用初始化器初始化，用 . 与 -> 访问
//   3) 定义结构体数组（例如 Sensor readings[3]），用初始化器初始化，用循环打印
//   4) 写一个【返回结构体的函数】并返回该结构体；对比 day28 的传指针，观察返回时拷贝了几份
//   5) 自测（口述）：返回结构体 vs 返回指针，各自代价/风险是什么？
// 【预测】（实现前填，写在对应代码行尾）
//   - 嵌套访问内层成员怎么写？我猜：____（如 d.sens.temp）
//   - readings[3] 的初始化器怎么写？我猜：____（如 {{1,..},{2,..},{3,..}}）
//   - 返回结构体的函数，调用处拿到的东西会被改影响原变量吗？我猜：____（会 / 不会）
// 【完成标准】① 能用初始化器初始化嵌套结构体与结构体数组；② 分清 . 在数组/嵌套上的连续使用；
//   ③ 用代码说明"返回结构体=拷贝、返回指针=共享"；④ 自测能答出返回结构体的代价
// 【参考代码】（#pragma region 折叠 + 注释，自己写完后对照）

#pragma region day29 参考代码（自己写完后对照，勿直接解注当作业交）
/*
typedef struct {
    int   id;
    float temp;
    int   status;
} Sensor;

typedef struct {
    char  name[16];
    Sensor sens;        // 嵌套结构体成员
} Device;

Device make_device(const char* n, int id, float t) {
    Device d;
    strncpy(d.name, n, sizeof(d.name) - 1);
    d.name[sizeof(d.name) - 1] = '\0';
    d.sens.id = id;
    d.sens.temp = t;
    d.sens.status = 0;
    return d;           // 返回结构体：调用处得到 d 的一份拷贝
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    Device d = { "MCU", { 1, 25.5f, 0 } };            // 嵌套初始化器
    printf("设备 %s 温度 %.2f\n", d.name, d.sens.temp);     // 连续 . 访问

    Sensor readings[3] = { {1,25.5f,0}, {2,30.0f,0}, {3,28.0f,0} };
    for (int i = 0; i < 3; i++)
        printf("读数%d: id=%d temp=%.2f\n", i, readings[i].id, readings[i].temp);

    Device d2 = make_device("SENSOR_A", 9, 31.0f);
    printf("make 返回：%s 温度 %.2f\n", d2.name, d2.sens.temp);
    return 0;
}
*/
#pragma endregion

// ============ 你的实现区（手敲；参考代码在上方折叠区）============
typedef struct {
    int   id;
    float temp;
    int   status;
} Sensor;

typedef struct {
    char  name[16];
    Sensor sens;        // 嵌套结构体成员
} Device;

// TODO：实现 make_device，返回一个初始化好的 Device（注意：返回的是 d 的一份拷贝）
Device make_device(const char* n, int id, float t) {
    Device d = { 0 };   // 预测：返回时调用处拿到的是 d 的拷贝（与 day28 传指针对比）
    // TODO：把 n 拷进 d.name（用 strncpy 防溢出），填 d.sens 的三个成员
    return d;
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    // TODO ①：用初始化器定义嵌套结构体 d（含 name 与 sens 两层），预测 d.sens.temp 可访问
    // TODO ②：用连续 . 访问 d.sens.temp 并打印（预测：d.sens.temp）
    // TODO ③：用初始化器定义结构体数组 readings[3]，循环打印每个成员的 id 与 temp
    // TODO ④：调用 make_device，打印返回值，观察"返回=拷贝"（对比 day28 传指针能原地改）
    return 0;
}
