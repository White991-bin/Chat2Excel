#include <bite_scaffold/mail.h>
#include <bite_scaffold/log.h>
#include <string>

int main(){
    // 1. 初始化日志器
    bitelog::bitelog_init();
    // 2. 设置邮箱配置
    bitecode::mail_settings settings = {
        .username = "ailiangshilove@163.com",
        .password = "SXdW58976zvQfWJk",
        .url = "smtps://smtp.163.com:465",
        .from = "ailiangshilove@163.com",
    };

    // 3. 创建邮件客户端并发送邮件
    bitecode::MailClient mailClient(settings);
    mailClient.send("569334855@qq.com", "123456");
    return 0;
}