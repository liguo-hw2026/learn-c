#include <stdio.h>

int main(void)
{
    printf("=== START ===\n");
    printf("%5d|\n", 33);
    printf("%-5d|\n", 33);
    printf("%05d|\n", 33);
    // 宽度只是最少位数，超过不截取
    printf("%3d|\n", 12345);
    printf("%8.2f|\n", 3.14159);   // 宽8、2位小数 → "    3.14|"
    printf("%-8.2f|\n", 3.14159);
    printf("%.3s|\n", "abcdef");
    printf("%.2d|\n", 5);
    printf("%08x|\n", 0x1234);
    return 0;
}
