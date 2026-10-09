# 数据库驱动层测试计划

## 一、测试概述

本文档详细描述数据库驱动层（`dbDriver`）各组件的测试计划，测试对象包括：

- **databaseSchema** - 数据结构与配置类
- **SQLValidator** - SQL验证器
- **DatabaseFactory** - 数据库工厂类
- **MySQLDatabase** - MySQL数据库实现
- **SQLiteDatabase** - SQLite数据库实现

---

## 二、测试文件组织

```
test/svc_dbService/testDriver/
├── CMakeLists.txt
├── databaseSchemaTest.cc    # 数据结构与配置类测试
├── sqlValidatorTest.cc       # SQL验证器测试
├── databaseFactoryTest.cc    # 工厂类测试
├── mysqlDatabaseTest.cc      # MySQL实现测试
└── sqliteDatabaseTest.cc     # SQLite实现测试
```

---

## 三、databaseSchema 测试计划

### 3.1 MySQLConfig 测试

#### 3.1.1 `validConfig()` 测试

> **MySQL连接配置信息**：
> - 服务器地址：124.222.231.213
> - 端口号：3306
> - 用户名：root
> - 密码：123456
> - 数据库名称：testdb

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T001 | 有效配置_所有必填字段正确 | host="124.222.231.213", port=3306, username="root", password="123456", database="testdb" | 返回true | 正常 |
| T003 | 无效配置_host为空 | host="", port=3306, username="root", password="123456", database="testdb" | 返回false | 异常 |
| T004 | 无效配置_port为0 | host="124.222.231.213", port=0, username="root", password="123456", database="testdb" | 返回false | 异常 |
| T005 | 无效配置_port为负数 | host="124.222.231.213", port=-1, username="root", password="123456", database="testdb" | 返回false | 异常 |
| T006 | 无效配置_port超过65535 | host="124.222.231.213", port=65536, username="root", password="123456", database="testdb" | 返回false | 异常 |
| T007 | 无效配置_username为空 | host="124.222.231.213", port=3306, username="", password="123456", database="testdb" | 返回false | 异常 |
| T008 | 无效配置_database为空 | host="124.222.231.213", port=3306, username="root", password="123456", database="" | 返回false | 异常 |

> **说明**：T002（SSL配置）和 T009（SSL证书不完整）已从测试计划中移除。

#### 3.1.2 `getType()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T010 | 获取类型_MySQL配置 | 创建MySQLConfig对象 | 返回DBType::MYSQL | 正常 |

### 3.2 SQLiteConfig 测试

#### 3.2.1 `validConfig()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T011 | 有效配置_路径以db结尾_文件存在 | dbPath="/path/test.db"（文件已存在） | 返回true | 正常 |
| T012 | 无效配置_dbPath为空 | dbPath="" | 返回false | 异常 |
| T013 | 无效配置_路径不以db结尾 | dbPath="/path/test.sqlite" | 返回false | 异常 |
| T014 | 无效配置_文件不存在 | dbPath="/path/nonexistent.db"（文件不存在） | 返回false | 异常 |

#### 3.2.2 `getType()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T015 | 获取类型_SQLite配置 | 创建SQLiteConfig对象 | 返回DBType::SQLITE | 正常 |

### 3.3 PreparedParam 测试

#### 3.3.1 构造函数测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T016 | 构造空参数 | PreparedParam() | 类型为ParamType::Null | 正常 |
| T017 | 构造空指针参数 | PreparedParam(nullptr) | 类型为ParamType::Null | 正常 |
| T018 | 构造整数参数 | PreparedParam(100LL) | 类型为ParamType::Int，值为100 | 正常 |
| T019 | 构造浮点数参数 | PreparedParam(3.14) | 类型为ParamType::Double，值为3.14 | 正常 |
| T020 | 构造字符串参数 | PreparedParam("hello") | 类型为ParamType::String，值为"hello" | 正常 |
| T021 | 构造布尔参数_true | PreparedParam(true) | 类型为ParamType::Bool，值为true | 正常 |
| T022 | 构造布尔参数_false | PreparedParam(false) | 类型为ParamType::Bool，值为false | 正常 |

#### 3.3.2 `getType()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T023 | 获取类型_整数参数 | PreparedParam(100LL) | 返回ParamType::Int | 正常 |
| T024 | 获取类型_字符串参数 | PreparedParam("test") | 返回ParamType::String | 正常 |
| T025 | 获取类型_空参数 | PreparedParam(nullptr) | 返回ParamType::Null | 正常 |

#### 3.3.3 `isNull()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T026 | 判断为空_空参数 | PreparedParam(nullptr) | 返回true | 正常 |
| T027 | 判断为空_整数参数 | PreparedParam(0LL) | 返回false | 正常 |
| T028 | 判断为空_空字符串 | PreparedParam("") | 返回false | 正常 |

#### 3.3.4 `getIntValue()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T029 | 获取整数值_整数类型 | PreparedParam(42LL) | 返回42 | 正常 |
| T030 | 获取整数值_浮点类型 | PreparedParam(3.14) | 返回3（截断） | 正常 |
| T031 | 获取整数值_字符串有效 | PreparedParam("123") | 返回123 | 正常 |
| T032 | 获取整数值_字符串无效 | PreparedParam("abc") | 返回0 | 正常 |
| T033 | 获取整数值_布尔true | PreparedParam(true) | 返回1 | 正常 |
| T034 | 获取整数值_布尔false | PreparedParam(false) | 返回0 | 正常 |
| T035 | 获取整数值_空类型 | PreparedParam(nullptr) | 返回0 | 正常 |

#### 3.3.5 `getDoubleValue()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T036 | 获取浮点值_浮点类型 | PreparedParam(3.14) | 返回3.14 | 正常 |
| T037 | 获取浮点值_整数类型 | PreparedParam(100LL) | 返回100.0 | 正常 |
| T038 | 获取浮点值_字符串有效 | PreparedParam("2.718") | 返回2.718 | 正常 |
| T039 | 获取浮点值_字符串无效 | PreparedParam("abc") | 返回0.0 | 正常 |
| T040 | 获取浮点值_布尔true | PreparedParam(true) | 返回1.0 | 正常 |

#### 3.3.6 `getStringValue()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T041 | 获取字符串值_字符串类型 | PreparedParam("hello") | 返回"hello" | 正常 |
| T042 | 获取字符串值_整数类型 | PreparedParam(123LL) | 返回"123" | 正常 |
| T043 | 获取字符串值_浮点类型 | PreparedParam(3.14) | 返回"3.14" | 正常 |
| T044 | 获取字符串值_布尔true | PreparedParam(true) | 返回"1" | 正常 |
| T045 | 获取字符串值_空类型 | PreparedParam(nullptr) | 返回"" | 正常 |

#### 3.3.7 `getBoolValue()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T046 | 获取布尔值_布尔true | PreparedParam(true) | 返回true | 正常 |
| T047 | 获取布尔值_布尔false | PreparedParam(false) | 返回false | 正常 |
| T048 | 获取布尔值_整数1 | PreparedParam(1LL) | 返回true | 正常 |
| T049 | 获取布尔值_整数0 | PreparedParam(0LL) | 返回false | 正常 |
| T050 | 获取布尔值_字符串TRUE | PreparedParam("TRUE") | 返回true | 正常 |
| T051 | 获取布尔值_字符串YES | PreparedParam("YES") | 返回true | 正常 |
| T052 | 获取布尔值_字符串false | PreparedParam("false") | 返回false | 正常 |
| T053 | 获取布尔值_字符串abc | PreparedParam("abc") | 返回false | 正常 |
| T054 | 获取布尔值_空类型 | PreparedParam(nullptr) | 返回false | 正常 |

### 3.4 QueryResult 测试

#### 3.4.1 `success()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T055 | 成功结果_默认 | QueryResult默认构造 | 返回true | 正常 |
| T056 | 失败结果 | QueryResult，_success=false | 返回false | 正常 |

#### 3.4.2 `errorMsg()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T057 | 无错误消息 | QueryResult默认构造 | 返回空字符串 | 正常 |
| T058 | 有错误消息 | QueryResult，_errorMsg="error" | 返回"error" | 正常 |

#### 3.4.3 `columnCount()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T059 | 无列 | QueryResult默认构造 | 返回0 | 正常 |
| T060 | 有列 | QueryResult._columns=["a", "b", "c"] | 返回3 | 正常 |

#### 3.4.4 `rowCount()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T061 | 无行 | QueryResult默认构造 | 返回0 | 正常 |
| T062 | 有行 | QueryResult._rows有3行 | 返回3 | 正常 |

#### 3.4.5 `getRow()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T063 | 获取有效行 | QueryResult._rows=[["1","2"], ["3","4"]], index=1 | 返回["3","4"] | 正常 |
| T064 | 获取无效行_索引为负 | QueryResult._rows=[["1","2"]], index=-1 | 返回空vector | 异常 |
| T065 | 获取无效行_索引超范围 | QueryResult._rows=[["1","2"]], index=5 | 返回空vector | 异常 |

---

## 四、SQLValidator 测试计划

### 4.1 `trim()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T066 | 去除左侧空格 | "  SELECT * FROM users" | "SELECT * FROM users" | 正常 |
| T067 | 去除右侧空格 | "SELECT * FROM users  " | "SELECT * FROM users" | 正常 |
| T068 | 去除两侧空格 | "  SELECT * FROM users  " | "SELECT * FROM users" | 正常 |
| T069 | 去除Tab字符 | "\tSELECT * FROM users\t" | "SELECT * FROM users" | 正常 |
| T070 | 去除换行符 | "\nSELECT * FROM users\n" | "SELECT * FROM users" | 正常 |
| T071 | 全部空格 | "     " | "" | 异常 |
| T072 | 空字符串 | "" | "" | 异常 |

### 4.2 `removeComments()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T073 | 去除单行注释 | "SELECT * FROM users -- 这是注释" | "SELECT * FROM users " | 正常 |
| T074 | 去除多行注释 | "SELECT /* comment */ * FROM users" | "SELECT  * FROM users" | 正常 |
| T075 | 保留字符串内内容 | "SELECT * FROM users WHERE name='-- test'" | "SELECT * FROM users WHERE name='-- test'" | 正常 |
| T076 | 保留字符串内单引号 | "SELECT * FROM users WHERE name='it''s'" | "SELECT * FROM users WHERE name='it''s'" | 正常 |
| T077 | 去除多个单行注释 | "SELECT * -- comment1\nFROM -- comment2\nusers" | "SELECT * \nFROM \nusers" | 正常 |
| T078 | 去除嵌套注释 | "SELECT * FROM users /* outer /* inner */ outer */" | "SELECT * FROM users  outer */ outer */" | 正常 |
| T079 | 无注释 | "SELECT * FROM users" | "SELECT * FROM users" | 正常 |

### 4.3 `normalize()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T080 | 规范化_去除注释和空格 | "  SELECT * FROM users -- comment  " | "SELECT * FROM users" | 正常 |
| T081 | 规范化_多行注释 | "  /* comment */ SELECT * FROM users  " | "SELECT * FROM users" | 正常 |

### 4.4 `validate()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T082 | 有效SELECT | "SELECT * FROM users" | 返回true | 正常 |
| T083 | 有效INSERT | "INSERT INTO users VALUES(1)" | 返回true | 正常 |
| T084 | 有效UPDATE | "UPDATE users SET name='test'" | 返回true | 正常 |
| T085 | 有效DELETE | "DELETE FROM users WHERE id=1" | 返回true | 正常 |
| T086 | 无效空字符串 | "" | 返回false | 异常 |
| T087 | 无效全空格 | "     " | 返回false | 异常 |
| T088 | 无效_包含DROP | "DROP TABLE users" | 返回false | 异常 |
| T089 | 无效_包含危险关键词 | "SELECT * FROM users WHERE id=1 OR 1=1" | 返回false | 异常 |
| T090 | 无效_多条语句 | "SELECT * FROM users; DROP TABLE users" | 返回false | 异常 |

### 4.5 `getSQLType()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T091 | SELECT语句 | "SELECT * FROM users" | 返回SqlType::SELECT | 正常 |
| T092 | INSERT语句 | "INSERT INTO users VALUES(1)" | 返回SqlType::INSERT | 正常 |
| T093 | UPDATE语句 | "UPDATE users SET name='test'" | 返回SqlType::UPDATE | 正常 |
| T094 | DELETE语句 | "DELETE FROM users WHERE id=1" | 返回SqlType::DELETE | 正常 |
| T095 | REPLACE语句 | "REPLACE INTO users VALUES(1)" | 返回SqlType::REPLACE | 正常 |
| T096 | TRUNCATE语句 | "TRUNCATE TABLE users" | 返回SqlType::TRUNCATE | 正常 |
| T097 | CREATE语句 | "CREATE TABLE users(id INT)" | 返回SqlType::CREATE | 正常 |
| T098 | DROP语句 | "DROP TABLE users" | 返回SqlType::DROP | 正常 |
| T099 | ALTER语句 | "ALTER TABLE users ADD COLUMN name VARCHAR(100)" | 返回SqlType::ALTER | 正常 |
| T100 | SHOW语句 | "SHOW TABLES" | 返回SqlType::SHOW | 正常 |
| T101 | DESC语句 | "DESC users" | 返回SqlType::DESC | 正常 |
| T102 | 未知类型 | "UNKNOWN SQL" | 返回SqlType::UNKNOWN | 异常 |

### 4.6 `isReadOnly()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T103 | SELECT只读 | "SELECT * FROM users" | 返回true | 正常 |
| T104 | SHOW只读 | "SHOW TABLES" | 返回true | 正常 |
| T105 | DESC只读 | "DESC users" | 返回true | 正常 |
| T106 | INSERT非只读 | "INSERT INTO users VALUES(1)" | 返回false | 正常 |
| T107 | UPDATE非只读 | "UPDATE users SET name='test'" | 返回false | 正常 |
| T108 | DELETE非只读 | "DELETE FROM users" | 返回false | 正常 |

### 4.7 `isModifySQL()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T109 | SELECT非修改 | "SELECT * FROM users" | 返回false | 正常 |
| T110 | INSERT是修改 | "INSERT INTO users VALUES(1)" | 返回true | 正常 |
| T111 | UPDATE是修改 | "UPDATE users SET name='test'" | 返回true | 正常 |
| T112 | DELETE是修改 | "DELETE FROM users" | 返回true | 正常 |
| T113 | 未知类型非修改 | "UNKNOWN SQL" | 返回false | 正常 |

### 4.8 `containsDangerousKeywords()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T114 | 无危险关键词 | "SELECT * FROM users" | 返回false | 正常 |
| T115 | 包含DROP_DATABASE | "DROP DATABASE testdb" | 返回true | 异常 |
| T116 | 包含DROP_TABLE | "DROP TABLE users" | 返回true | 异常 |
| T117 | 包含TRUNCATE | "TRUNCATE TABLE users" | 返回true | 异常 |
| T118 | 包含EXEC | "EXEC sp_name" | 返回true | 异常 |
| T119 | 包含UNION_ALL_SELECT | "SELECT * FROM users UNION ALL SELECT * FROM admin" | 返回true | 异常 |
| T120 | 包含OR_1=1 | "SELECT * FROM users WHERE id=1 OR 1=1" | 返回true | 异常 |
| T121 | 包含SLEEP | "SELECT * FROM users WHERE SLEEP(5)" | 返回true | 异常 |
| T122 | 包含INTO_OUTFILE | "SELECT * FROM users INTO OUTFILE '/tmp/test.txt'" | 返回true | 异常 |
| T123 | 大小写不敏感检测 | "drop table users" | 返回true | 异常 |

### 4.9 `hasMultipleStatements()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T124 | 单条语句 | "SELECT * FROM users" | 返回false | 正常 |
| T125 | 多条语句_分号分隔 | "SELECT * FROM users; DROP TABLE users" | 返回true | 异常 |
| T126 | 分号在字符串内 | "INSERT INTO users VALUES('test;abc')" | 返回false | 正常 |
| T127 | 转义单引号内含分号 | "INSERT INTO users VALUES('it''s;a')" | 返回false | 正常 |
| T128 | 空字符串 | "" | 返回false | 异常 |
| T129 | 只有分号 | ";" | 返回false | 异常 |
| T130 | 分号后无内容 | "SELECT * FROM users;" | 返回false | 正常 |

### 4.10 `extractTableName()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T131 | INSERT_INTO表名 | "INSERT INTO users VALUES(1)" | 返回"users" | 正常 |
| T132 | UPDATE表名 | "UPDATE users SET name='test'" | 返回"users" | 正常 |
| T133 | DELETE_FROM表名 | "DELETE FROM users WHERE id=1" | 返回"users" | 正常 |
| T134 | TRUNCATE_TABLE表名 | "TRUNCATE TABLE users" | 返回"users" | 正常 |
| T135 | REPLACE_INTO表名 | "REPLACE INTO users VALUES(1)" | 返回"users" | 正常 |
| T136 | ALTER_TABLE表名 | "ALTER TABLE users ADD COLUMN age INT" | 返回"users" | 正常 |
| T137 | CREATE_TABLE表名 | "CREATE TABLE users(id INT)" | 返回"users" | 正常 |
| T138 | DROP_TABLE表名 | "DROP TABLE users" | 返回"users" | 正常 |
| T139 | 单引号包裹表名 | "INSERT INTO 'users' VALUES(1)" | 返回"users" | 正常 |
| T140 | SELECT非修改类 | "SELECT * FROM users" | 返回空字符串 | 正常 |
| T141 | 空字符串 | "" | 返回空字符串 | 异常 |

### 4.11 `isValidTableName()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T142 | 有效_普通表名 | "users" | 返回true | 正常 |
| T143 | 有效_带下划线 | "user_info" | 返回true | 正常 |
| T144 | 有效_带点 | "db.users" | 返回true | 正常 |
| T145 | 有效_带短横线 | "user-data" | 返回true | 正常 |
| T146 | 有效_中文表名 | "用户表" | 返回true | 正常 |
| T147 | 有效_以字母开头 | "Table123" | 返回true | 正常 |
| T148 | 无效_空字符串 | "" | 返回false | 异常 |
| T149 | 无效_以数字开头 | "123users" | 返回false | 异常 |
| T150 | 无效_包含分号 | "users;table" | 返回false | 异常 |
| T151 | 无效_包含单引号 | "user's" | 返回false | 异常 |
| T152 | 无效_包含空白 | "users table" | 返回false | 异常 |
| T153 | 无效_包含星号 | "users*" | 返回false | 异常 |
| T154 | 无效_包含反斜杠 | "users\\table" | 返回false | 异常 |
| T155 | 无效_包含斜杠 | "users/table" | 返回false | 异常 |
| T156 | 无效_连续点 | "users..table" | 返回false | 异常 |
| T157 | 无效_连续短横线 | "users--table" | 返回false | 异常 |
| T158 | 无效_超长名称 | 65个字符的字符串 | 返回false | 异常 |

### 4.12 `isValidColumnName()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T159 | 有效列名 | "user_name" | 返回true | 正常 |
| T160 | 无效列名 | "user name" | 返回false | 异常 |

---

## 五、DatabaseFactory 测试计划

### 5.1 `getInstance()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T161 | 单例模式_首次调用 | 首次调用getInstance() | 返回非空单例 | 正常 |
| T162 | 单例模式_多次调用 | 多次调用getInstance() | 返回同一实例 | 正常 |

### 5.2 `registerDatabase()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T163 | 注册MySQL | registerDatabase(DBType::MYSQL, creator) | 注册成功，无错误日志 | 正常 |
| T164 | 注册SQLite | registerDatabase(DBType::SQLITE, creator) | 注册成功，无错误日志 | 正常 |
| T165 | 重复注册同一类型 | 两次注册同一DBType | 第二次注册失败，有错误日志 | 异常 |

### 5.3 `createDatabase()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T166 | 创建MySQL_有效配置 | MySQLConfig配置全部有效 | 返回非空IDatabase指针 | 正常 |
| T167 | 创建SQLite_有效配置 | SQLiteConfig配置全部有效，文件存在 | 返回非空IDatabase指针 | 正常 |
| T168 | 创建_nullptr配置 | config=nullptr | 返回nullptr | 异常 |
| T169 | 创建_无效MySQL配置 | MySQLConfig配置无效 | 返回nullptr | 异常 |
| T170 | 创建_无效SQLite配置 | SQLiteConfig配置无效 | 返回nullptr | 异常 |
| T171 | 创建_不支持的类型 | 未注册的DBType | 返回nullptr | 异常 |

### 5.4 `getSupportedTypes()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T172 | 获取支持的类型 | 调用getSupportedTypes() | 返回包含MYSQL和SQLITE的vector | 正常 |

### 5.5 `isSupported()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T173 | 支持MySQL | DBType::MYSQL | 返回true | 正常 |
| T174 | 支持SQLite | DBType::SQLITE | 返回true | 正常 |
| T175 | 不支持未知类型 | 未知DBType | 返回false | 异常 |

---

## 六、MySQLDatabase 测试计划

### 6.1 连接管理测试

#### 6.1.1 `connect()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T176 | 连接成功_有效配置 | 有效的MySQLConfig | 返回true，_connected=true | 正常 |
| T177 | 连接失败_无效配置 | MySQLConfig配置无效 | 返回false | 异常 |
| T178 | 连接失败_数据库不存在 | 连接不存在的数据库 | 返回false | 异常 |
| T179 | 连接失败_认证失败 | 用户名密码错误 | 返回false | 异常 |
| T180 | 重复连接 | 首次connect成功后再次connect | 返回true，_connected保持true | 正常 |

#### 6.1.2 `disconnect()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T181 | 断开连接_已连接 | 已连接的MySQLDatabase | _connected=false | 正常 |
| T182 | 断开连接_未连接 | 未连接的MySQLDatabase | 无副作用 | 正常 |

#### 6.1.3 `ping()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T183 | Ping成功_已连接 | 已连接状态 | 返回true | 正常 |
| T184 | Ping失败_未连接 | 未连接状态 | 返回false | 异常 |
| T185 | Ping失败_连接断开 | 已连接后断开 | 返回false | 异常 |

### 6.2 查询执行测试

#### 6.2.1 `executeQuery()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T186 | 查询成功_SELECT | "SELECT 1 AS col" | success=true, rows有数据 | 正常 |
| T187 | 查询成功_空结果集 | "SELECT * FROM nonexistent_table" | success=true, rows为空 | 正常 |
| T188 | 查询失败_未连接 | 未连接状态 | success=false, errorMsg不为空 | 异常 |
| T189 | 查询失败_语法错误 | "SELEC * FROM users" | success=false, errorMsg包含错误信息 | 异常 |
| T190 | 查询失败_表不存在 | "SELECT * FROM nonexistent" | success=false | 异常 |

#### 6.2.2 `executeModify()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T191 | 修改成功_INSERT | "INSERT INTO users(name) VALUES('test')" | success=true, affectedRows>0 | 正常 |
| T192 | 修改成功_UPDATE | "UPDATE users SET name='new' WHERE id=1" | success=true, affectedRows>=0 | 正常 |
| T193 | 修改成功_DELETE | "DELETE FROM users WHERE id=999" | success=true, affectedRows>=0 | 正常 |
| T194 | 修改失败_未连接 | 未连接状态 | success=false | 异常 |
| T195 | 修改失败_语法错误 | "INSER INTO users VALUES(1)" | success=false | 异常 |
| T196 | 修改失败_表不存在 | "DROP TABLE nonexistent" | success=false | 异常 |

### 6.3 预处理语句测试

#### 6.3.1 `executePreparedQuery()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T197 | 预处理查询成功_整数参数 | SQL="SELECT ? AS num", params=[100] | success=true, 值为"100" | 正常 |
| T198 | 预处理查询成功_字符串参数 | SQL="SELECT ? AS name", params=["test"] | success=true, 值为"test" | 正常 |
| T199 | 预处理查询成功_多参数 | SQL="SELECT ?, ?", params=[1, "test"] | success=true | 正常 |
| T200 | 预处理查询失败_未连接 | 未连接状态 | success=false | 异常 |
| T201 | 预处理查询失败_参数不匹配 | SQL="SELECT ?", params=[1, 2] | success=false | 异常 |

#### 6.3.2 `executePreparedModify()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T202 | 预处理修改成功_INSERT | SQL="INSERT INTO users(name) VALUES(?)", params=["test"] | success=true, affectedRows>0 | 正常 |
| T203 | 预处理修改失败_未连接 | 未连接状态 | success=false | 异常 |

### 6.4 事务测试

#### 6.4.1 `beginTransaction()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T204 | 开启事务成功_已连接 | 已连接状态 | 返回true | 正常 |
| T205 | 开启事务失败_未连接 | 未连接状态 | 返回false | 异常 |

#### 6.4.2 `commit()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T206 | 提交事务成功_已连接 | 已连接状态 | 返回true | 正常 |
| T207 | 提交事务失败_未连接 | 未连接状态 | 返回false | 异常 |

#### 6.4.3 `rollback()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T208 | 回滚事务成功_已连接 | 已连接状态 | 返回true | 正常 |
| T209 | 回滚事务失败_未连接 | 未连接状态 | 返回false | 异常 |

### 6.5 标识符转义测试

#### 6.5.1 `quoteIdentifier()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T210 | 转义普通标识符 | "users" | 返回"`users`" | 正常 |
| T211 | 已转义标识符 | "`users`" | 返回"`users`"（不重复包裹） | 正常 |
| T212 | 转义保留字 | "order" | 返回"`order`" | 正常 |

### 6.6 ParamBinder 辅助类测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T213 | 参数绑定_空参数 | SQL="SELECT ?", params=[] | 绑定成功 | 正常 |
| T214 | 参数绑定_各种类型 | params=[nullptr, 1, 3.14, "str", true] | 所有参数正确绑定 | 正常 |

### 6.7 ResultBinder 辅助类测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T215 | 结果绑定_SELECT多列 | "SELECT id, name, age FROM users" | 所有列正确绑定 | 正常 |
| T216 | 结果绑定_空结果集 | "SELECT * FROM empty_table" | rows为空 | 正常 |

---

## 七、SQLiteDatabase 测试计划

### 7.1 连接管理测试

#### 7.1.1 `connect()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T217 | 连接成功_有效配置 | 有效的SQLiteConfig，文件存在 | 返回true，_connected=true | 正常 |
| T218 | 连接失败_无效配置 | SQLiteConfig配置无效 | 返回false | 异常 |
| T219 | 连接失败_文件不存在 | dbPath指向不存在的文件 | 返回false | 异常 |
| T220 | 重复连接 | 首次connect成功后再次connect | 返回true | 正常 |

#### 7.1.2 `disconnect()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T221 | 断开连接_已连接 | 已连接的SQLiteDatabase | _connected=false | 正常 |
| T222 | 断开连接_未连接 | 未连接的SQLiteDatabase | 无副作用 | 正常 |

#### 7.1.3 `ping()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T223 | Ping成功_已连接 | 已连接状态 | 返回true | 正常 |
| T224 | Ping失败_未连接 | 未连接状态 | 返回false | 异常 |

### 7.2 查询执行测试

#### 7.2.1 `executeQuery()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T225 | 查询成功_SELECT | "SELECT 1 AS col" | success=true, rows有数据 | 正常 |
| T226 | 查询成功_空结果集 | "SELECT * FROM sqlite_master WHERE 1=0" | success=true, rows为空 | 正常 |
| T227 | 查询失败_未连接 | 未连接状态 | success=false | 异常 |
| T228 | 查询失败_语法错误 | "SELEC * FROM users" | success=false | 异常 |

#### 7.2.2 `executeModify()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T229 | 修改成功_INSERT | "INSERT INTO users(name) VALUES('test')" | success=true, affectedRows>0 | 正常 |
| T230 | 修改成功_UPDATE | "UPDATE users SET name='new' WHERE id=1" | success=true, affectedRows>=0 | 正常 |
| T231 | 修改成功_CREATE | "CREATE TABLE test(id INT)" | success=true | 正常 |
| T232 | 修改成功_DROP | "DROP TABLE IF EXISTS test" | success=true | 正常 |
| T233 | 修改失败_未连接 | 未连接状态 | success=false | 异常 |
| T234 | 修改失败_语法错误 | "INSER INTO users VALUES(1)" | success=false | 异常 |

### 7.3 预处理语句测试

#### 7.3.1 `executePreparedQuery()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T235 | 预处理查询成功_整数参数 | SQL="SELECT ? AS num", params=[100] | success=true, 值为"100" | 正常 |
| T236 | 预处理查询成功_字符串参数 | SQL="SELECT ? AS name", params=["test"] | success=true, 值为"test" | 正常 |
| T237 | 预处理查询成功_多参数 | SQL="SELECT ?, ?", params=[1, "test"] | success=true | 正常 |
| T238 | 预处理查询成功_NULL参数 | SQL="SELECT ?", params=[nullptr] | success=true | 正常 |
| T239 | 预处理查询失败_未连接 | 未连接状态 | success=false | 异常 |

#### 7.3.2 `executePreparedModify()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T240 | 预处理修改成功_INSERT | SQL="INSERT INTO users(name) VALUES(?)", params=["test"] | success=true, affectedRows>0 | 正常 |
| T241 | 预处理修改失败_未连接 | 未连接状态 | success=false | 异常 |

### 7.4 事务测试

#### 7.4.1 `beginTransaction()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T242 | 开启事务成功_已连接 | 已连接状态 | 返回true | 正常 |
| T243 | 开启事务失败_未连接 | 未连接状态 | 返回false | 异常 |

#### 7.4.2 `commit()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T244 | 提交事务成功_已连接 | 已连接状态 | 返回true | 正常 |
| T245 | 提交事务失败_未连接 | 未连接状态 | 返回false | 异常 |

#### 7.4.3 `rollback()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T246 | 回滚事务成功_已连接 | 已连接状态 | 返回true | 正常 |
| T247 | 回滚事务失败_未连接 | 未连接状态 | 返回false | 异常 |

### 7.5 标识符转义测试

#### 7.5.1 `quoteIdentifier()` 测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T248 | 转义普通标识符 | "users" | 返回"\"users\"" | 正常 |
| T249 | 已转义标识符 | "\"users\"" | 返回"\"users\""（不重复包裹） | 正常 |
| T250 | 转义保留字 | "group" | 返回"\"group\"" | 正常 |

### 7.6 ParamBinder 辅助类测试

| 编号 | 测试用例名称 | 测试输入 | 预期结果 | 测试类型 |
|------|------------|---------|---------|---------|
| T251 | 参数绑定_空参数 | SQL="SELECT ?", params=[] | 绑定成功 | 正常 |
| T252 | 参数绑定_各种类型 | params=[nullptr, 1, 3.14, "str", true] | 所有参数正确绑定 | 正常 |
| T253 | 参数绑定_BLOB | params=[二进制数据] | 正确绑定 | 正常 |

---

## 八、测试统计汇总

| 模块 | 测试用例数 |
|------|----------|
| databaseSchema (MySQLConfig, SQLiteConfig, PreparedParam, QueryResult) | 63 |
| SQLValidator | 95 |
| DatabaseFactory | 15 |
| MySQLDatabase | 40 |
| SQLiteDatabase | 37 |
| **总计** | **250** |

---

## 九、测试执行前提条件

### 9.1 环境要求
- C++11 及以上编译器
- Google Test (gtest) 测试框架
- SQLite3 库
- MySQL Connector/C 库
- spdlog 日志库
- JSON 库 (jsoncpp)

### 9.2 测试数据库准备
- MySQL: 需要一个可访问的 MySQL 服务器实例
- SQLite: 测试用例需要创建临时 .db 文件，测试结束后清理

### 9.3 Mock 对象
对于依赖真实数据库连接的测试，建议使用 Mock 对象来隔离外部依赖，提高测试的稳定性和执行速度。

---

## 十、附录

### 10.1 测试用例命名规则
- `T` + 数字编号：唯一标识每个测试用例
- 测试类型标记：正常（预期行为）/ 异常（边界条件或错误处理）

### 10.2 预期测试覆盖率
- databaseSchema: 所有公共成员函数 100% 覆盖
- SQLValidator: 所有公共静态函数 100% 覆盖
- DatabaseFactory: 所有公共成员函数 100% 覆盖
- MySQLDatabase/SQLiteDatabase: 所有接口方法 100% 覆盖
