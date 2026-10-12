// day02：变量、浮点数、表达式与运算符
// 翁恺 C 语言 第 11-19 讲
//
// 玩法（跟 printf 那次一样）：
//   先预测输出 -> 再运行验证 -> 预测错了把原因写进注释
//   带 TODO 的地方要你自己补代码

#include <stdio.h>

int main(void)
{
    // ========== 第 11-12 讲：变量定义、赋值与初始化 ==========
    /*int price = 0;          // 定义时立刻初始化，是好习惯
    int amount=100;
    printf("price=%d\n", price);
    printf("amount=%d\n", amount);
   
    // TODO 1：试一下不初始化会怎样 —— 删掉 = 0，改成 int price; 再打印
    //         （未初始化的局部变量是垃圾值，每次运行结果可能不同）

    // ========== 第 13 讲：scanf 读入数字（& 千万别漏） ==========
    // 提示语用英文：Windows 控制台默认代码页 936，printf 中文会显示乱码
    // （想用中文提示，先在运行窗口执行 chcp 65001 切换代码页）
    printf("price amount (e.g. 23 3): ");
    int ret = scanf("%d %d", &price, &amount);   // ret = 成功读入的变量个数
    // TODO 2：输入两个数字时 ret 等于几？输入 abc 时又等于几？（后者是 scanf 的经典坑）
    printf("scanf returned %d\n", ret);
    
    // ========== 第 14 讲：常量 vs 变量 ==========
    const int DISCOUNT = 10;    // const = 只读，赋值会编译报错
    // TODO 3：把下面这行的注释去掉，看编译器报什么错（看完再注释回去）
    DISCOUNT = 20;
    
    // ========== 第 15 讲：浮点数（整数除法只取整数部分！） ==========
    int a = 5, b = 2;
    // TODO 4a：先预测下面四行输出、再运行验证 —— 这四行就是翁恺第 15 讲的核心演示（浮点数运算）
    printf("5 / 2     = %d\n", a / b);      // 预测：2
    printf("5.0 / 2   = %f\n", 5.0 / b);    // 预测：2.5
    printf("5 %% 2     = %d\n", a % b);     // 取余，预测：1（%% 才是输出一个 %）
    printf("5 / 2.0   = %f\n", a / 2.0);    // 预测：2.5
     
    // TODO 4b：翁恺这讲的经典应用题 —— 输入身高的英尺和英寸，换算成米（同样考整数除法陷阱）
    //         （提示：1 英尺 = 12 英寸，1 英寸 = 0.0254 米；注意整数除法陷阱）
    int foot = 0;
    int inch = 0;
    printf("enter the height(foot inch):\n");
    scanf(" %d %d", &foot, &inch);
    float meters = 0;
    meters = (foot * 12 + inch) * 0.0254;
    printf("the height is %f meters.\n", meters);
   
    // ========== 第 16-17 讲：表达式、优先级与结合性 ==========
    int x = 2, y = 3, z = 4;
    // TODO 5：先预测下面三行的结果，再运行验证（优先级 / 括号 / 赋值右结合）
     printf("x + y * z   = %d\n", x + y * z);
     printf("(x + y) * z = %d\n", (x + y) * z);
     printf("x = y = z   -> %d %d %d\n", x, y, z);
    
    // ========== 第 18 讲：交换两个变量（用临时变量） ==========
    // TODO 6：交换 a 和 b 的值并打印，验证真的换过来了
     int a = 5; 
     int b = 3;
     int t = 0;
     t = a;
     a = b;
     b = t;
     printf("%d %d", a, b);
     */
    // ========== 第 19 讲：复合赋值与递增递减（++i vs i++） ==========
    // 提示语一律用英文：Windows 控制台默认代码页 936，printf 中文会显示乱码
    // （想用中文输出，先在运行窗口执行 chcp 65001 切换代码页，或改控制台字体）
    int i = 5;
    printf("value of  i++  = %d\n", i++);   // 预测：5（先用后加）
    printf("now i is       = %d\n", i);     // 预测：6
    printf("value of  ++i  = %d\n", ++i);   // 预测：7（先加后用）
    printf("now i is       = %d\n", i);     // 预测：7
    // ⚠️ 这讲的重点：不要在同一个表达式里对同一个变量用两次 ++，
    //    如 printf("%d %d", i++, ++i); —— 结果由编译器决定，是未定义行为
  
    return 0;
}
