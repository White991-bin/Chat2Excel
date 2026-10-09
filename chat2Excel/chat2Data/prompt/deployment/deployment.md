# 一键编译

你是一个资深的后端开发工程师，请帮我完成Chat2Data项目的意见编译。
目前Chat2Data项目是各个子服务独立编译的，现在我需要一键编译各个子服务。要求：
1. 将各个子服务的CMakeLists.txt文件进行备份，备份到/home/dev/workspace/chat2data-tech/chat2data-tech/chat2Data/CMakeLists-backup目录中，命名方式为: CMakeLists-子服务名称.txt
2. 在/home/dev/workspace/chat2data-tech/chat2data-tech/chat2Data目录下，创建总的CMakeLists.txt文件，该文件的职责是：
   - 将/home/dev/workspace/chat2data-tech/chat2data-tech/chat2Data/common目录下的所有代码编译成静态库，其他子服务需要用到时链接该静态库
   - 将/home/dev/workspace/chat2data-tech/chat2data-tech/chat2Data/proto文件编译生成C++代码，将生成之后的C++代码编译成静态库，其他子服务需要用到时链接该静态库
   - odb映射类让各个子服务独立编译，因为odb文件是各个子服务自己使用的
   - 将各个子服务的共同需要链接的库移动到总的CMakeLists.txt文件中，自己单独链接的库在自己的CMakeLists.txt中添加
   - 添加各个子服务的CMakeLists.txt文件，完成各个子服务的一键编译
3. 简化各个子服务CMakeLists.txt
4. 编译过程中生成的临时文件放在/home/dev/workspace/chat2data-tech/chat2data-tech/chat2Data/build，编译生成的可执行程序放在/home/dev/workspace/chat2data-tech/chat2data-tech/chat2Data/bin目录中，静态库放在bin/lib目录中

请你先仔细阅读当前项目的目录结构以及现在的编译方案，熟悉上述需求之后，请先罗列出你详细的实现规划，我看完之后确保你和我理解一致，我再告诉你实现。


# gfalgs参数处理

你是一个资深的后端开发工程师，请帮我完善chat2Data项目中gflags参数解析问题 和 服务名称硬编码问题。

【gflags参数解析】
现在各个子服务的gflags参数都是在main.cc中定义的，我需要将每个子服务的gflags参数在配置文件/home/dev/workspace/chat2data-tech/chat2data-tech/chat2Data/chat2Data.conf中配置，将来各个子服务启动时从配置文件中读取gflags参数。

【服务名称硬编码】
各个子服务在进行RPC调用时，需要获取通信信道，目前代码中是通过服务名称硬编码的方式获取的，你需要帮我修改成通过gflags参数获取，如果其他代码如果存在服务名称硬编码，需要全部使用gflags参数。

注意：
1. 相同配置的参数只配置一次，比如：MySQL、Redis、日志、ETCD地址等
2. 各个子服务名称统一如下：
   --user_service=UserService
   --file_service=FileService
   --db_service=DatabaseService
   --ai_service=AIService
   --notify_service=NotifyService
   --excel_service=ExcelService
3. 服务都包含了端口号、服务名称、服务器地址等参数，不需要考虑冲突问题，将来每个子服务都是在独立的容器中运行，端口号、服务名称、服务地址会在各自的容器中单独配置。名称统一如下：
--listen_port=${LISTEN_PORT}
--service_name=${SVC_SERVICE_NAME}
--service_addr=${SVC_SERVICE_ADDR}

请你熟悉chat2Data项目的代码后，帮我完成上述两个问题。完成之后你需要仔细深入检查，确保所有的服务名称硬编码被全部替换。
