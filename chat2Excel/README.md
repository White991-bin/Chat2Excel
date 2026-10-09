# ChatExcel - AI驱动的Excel智能分析平台
**C++微服务 + 大模型 实现 Excel 自然语言数据分析**

上传 Excel 文件，通过自然语言对话即可完成查询、筛选、排序、统计，AI 自动生成并执行 SQL，零代码完成表格数据分析。

## ✨ 核心亮点
- **自然语言交互**：中文口语提问自动转 SQL 查询数据
- **多模型兼容**：支持 DeepSeek、Gemini、ChatGPT、Ollama
- **模块化微服务**：基于 BRPC + Protobuf，低耦合易扩展
- **全业务闭环**：登录注册、文件存储、AI会话、消息通知齐全
- **容器化部署**：Docker Compose 一键部署，适配云服务器

## 📌 主要功能
- 用户注册登录、邮箱验证码通知
- 智能解析 .xlsx 表格，自动识别表头与数据
- 自然语言 AI 数据分析，自动生成 SQL 执行
- 多 AI 会话创建、历史对话留存管理
- 基于 FastDFS 实现 Excel 文件上传与持久化存储

## 🏗️ 技术架构
**架构流程**：浏览器 → Gateway网关(8000) → etcd服务发现 → 七大微服务 → MySQL/Redis/FastDFS

### 服务端口清单
| 服务名 | 端口 | 功能 |
|--------|------|------|
| gateway-service | 8000 | 前端页面、API网关、请求转发 |
| user-service | 8001 | 用户登录注册、身份校验 |
| notify-service | 8002 | 邮箱消息通知 |
| excel-service | 8003 | Excel 表格解析 |
| file-service | 8004 | 文件上传存储（FastDFS） |
| database-service | 8005 | SQL 执行、数据查询 |
| ai-service | 8006 | 大模型对接、NL2SQL 转换 |

### 技术栈
C++、BRPC、Protobuf、OpenXLSX、etcd、MySQL、Redis、FastDFS、原生前端、Docker

## 💻 环境依赖
- Docker 20.10+、Docker Compose v2
- 服务器放行端口：8000、2379、6379
- 提前启动基础设施：MySQL、etcd、Redis、FastDFS

## ⚙️ 核心配置
### 1. 网络配置（必填）
与基础设施共用外部网络，`docker-compose.yml`：
```yaml
networks:
  default:
    name: bite-dev-environment_dev-network
    external: true
```

### 2. AI 密钥配置
国内服务器**仅 DeepSeek 可用**，无需翻墙：
```yaml
environment:
  - deepseek_apikey=sk-xxxxxxxxxxxxxxxxxxxx
```

### 3. 前端接口地址
`bin/www/js/config.js`
```javascript
const API_BASE_URL = 'http://服务器公网IP:8000';
```

## 🚀 部署启动
### 1. 启动命令
```bash
# 进入项目目录
cd ~/llmexcel/chat2Excel/chat2Data

# 后台启动所有服务
docker compose up -d

# 等待服务注册 etcd（必执行）
sleep 40

# 查看运行状态（全部 healthy 正常）
docker compose ps
```

### 2. 访问地址
登录：`http://IP:8000/login.html` | 注册：`http://IP:8000/register.html`

### 3. 常用运维命令
```bash
docker compose start/stop/restart  # 启动/停止/重启
docker compose logs -f              # 查看全部日志
docker compose logs ai --tail 50    # 查看AI服务日志
docker compose down                 # 销毁容器
```

## 📝 使用流程
注册账号 → 登录系统 → 上传带表头的 .xlsx 文件 → 新建 DeepSeek 会话 → 自然语言提问分析数据

**提问示例**：按语文成绩降序、筛选数学大于120分、计算各科平均分

## 🛠️ 自定义编译
修改 AI 提示词（`svc_aiService/userPrompt.h`）后重新编译替换：
```bash
# 编译二进制
docker run --rm -v /home/ubuntu/llmexcel/chat2Excel/chat2Data:/build 镜像名 bash -c 'cd /build && rm -rf build && mkdir build && cd build && cmake .. && make -j$(nproc) AIService'

# 替换并重启服务
docker cp /build/build/svc_aiService/AIService ai-service:/home/chat2Data/AIService
docker restart ai-service
```

## ❌ 常见问题速排
- **503 服务不可用**：等待40秒 etcd 注册完成，或重启服务
- **Excel 解析失败**：删除表格空白工作表，保留表头+有效数据
- **Gemini 无法使用**：国内网络受限，仅用 DeepSeek
- **AI 密钥不生效**：修改密钥后执行 `docker compose up -d --force-recreate ai`
- **文件上传失败**：清理服务器磁盘，降低 FastDFS 存储预留阈值

## 📁 项目结构
```
chat2Data/
├── docker-compose.yml   # 服务编排配置
├── entrypoint.sh        # 容器启动脚本
├── bin/www              # 前端静态页面与配置
├── svc_xxxService/      # 各微服务源码目录
└── data/sql             # 数据库初始化脚本
```

## 📌 持久化说明
容器内修改（前端配置、AI二进制、服务配置）重建容器会丢失，可通过 Volume挂载 或自定义镜像固化配置。

## 📄 开源协议
本项目仅用于学习交流，禁止商业用途。
