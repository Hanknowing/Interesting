#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_USERS 100 // 最大用户数量
#define MAX_USERNAME_LENGTH 50 // 最大用户名长度
#define MAX_PASSWORD_LENGTH 50 // 最大密码长度

// 用户结构体
typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int loggedIn; // 标记用户是否已登录
} User;

// 全局变量，存储所有注册用户的信息
User users[MAX_USERS];
int totalUsers = 0; // 当前注册用户数量
int loggedInUserIndex = -1; // 记录当前登录用户的索引，初始值为-1表示未登录

// 注册函数
void registerUser() {
    if (totalUsers >= MAX_USERS) {
        printf("抱歉，用户数量已达到上限，无法注册新用户。\n");
        return;
    }

    printf("请输入用户名：");
    char username[MAX_USERNAME_LENGTH];
    scanf("%s", username);

    // 检查用户名是否已存在
    for (int i = 0; i < totalUsers; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("该用户名已被注册，请尝试其他用户名。\n");
            return;
        }
    }

    printf("请输入密码：");
    char password[MAX_PASSWORD_LENGTH];
    scanf("%s", password);

    // 将用户信息存储到全局变量中
    strcpy(users[totalUsers].username, username);
    strcpy(users[totalUsers].password, password);
    users[totalUsers].loggedIn = 0; // 初始状态下用户未登录
    totalUsers++;

    printf("注册成功！\n");
}

// 登录函数
void loginUser() {
    printf("请输入用户名：");
    char username[MAX_USERNAME_LENGTH];
    scanf("%s", username);

    printf("请输入密码：");
    char password[MAX_PASSWORD_LENGTH];
    scanf("%s", password);

    // 遍历所有用户，查找匹配的用户名和密码
    for (int i = 0; i < totalUsers; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            users[i].loggedIn = 1; // 登录成功，设置用户登录状态为已登录
            loggedInUserIndex = i; // 记录当前登录用户的索引
            printf("登录成功！\n");
            return;
        }
    }

    printf("用户名或密码错误，请重新登录。\n");
}

void play(int loggedIn) {
    if (!loggedIn) {
        printf("请先登录！\n");
        return;
    }

    int min_number = 1; // 最小抽奖号码
    int max_number = 100; // 最大抽奖号码
    int lucky_number; // 幸运号码
    int guess; // 用户猜测的号码

    // 使用系统时间设置随机数种子，确保每次运行时随机数不同
    srand(time(NULL));

    // 生成幸运号码
    lucky_number = min_number + rand() % (max_number - min_number + 1);

    // 提示用户输入猜测的号码
    printf("欢迎参加幸运抽奖！请输入一个介于%d和%d之间的号码：", min_number, max_number);
    scanf("%d", &guess);

    // 判断猜测结果并输出相应信息
    if (guess < min_number || guess > max_number) {
        printf("您输入的号码超出了范围，请输入介于%d和%d之间的号码。\n", min_number, max_number);
    } else if (guess == lucky_number) {
        printf("恭喜您中奖了！幸运号码是%d。\n", lucky_number);
    } else {
        printf("很遗憾，您没有中奖。幸运号码是%d。\n", lucky_number);
    }
}

int main() {
    int choice;

    do {
        printf("\n欢迎使用幸运抽奖系统\n");
        printf("1. 注册\n");
        printf("2. 登录\n");
        printf("3. 玩\n");
        printf("4. 退出\n");
        printf("请选择操作：");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                play(users[loggedInUserIndex].loggedIn); // 传递登录状态给play函数
                break;
            default:
                printf("无效的选项，请重新选择。\n");
        }
    } while (choice != 4);

    return 0;
}
