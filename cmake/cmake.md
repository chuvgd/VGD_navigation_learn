# CMake基础

## 一.cmake概述

cmake是一个项目构建工具，且跨平台

先概述一下相关的toolchain：

```
预处理-->编译器编译(gcc/g++)-->得到汇编文件-->处理得到二进制文件(.o/.obj)-->链接器链接产生可执行文件
```

如果是一个大型项目就需要一个项目构建工具

- makefile --> make(make通常依赖于当前的编译平台)
- CMakeLists.txt --> cmake --> makefile -->make（cmake是跨平台构建工具）

不仅生成相关的可执行文件，还有生成库文件（动态库或者静态库）——第三方项目的引入（只提供头文件就可以做到简化项目的编写）

**重点：就是去学习和掌握引入第三方库或者构建自己的项目库**

## 二.构建简单的cmakelists.txt

以ubuntu22.04举例：

安装cmake：

```shell
sudo apt install cmake
```

查看安装版本：

```shell
cmake --version
```

cmake的简单使用

### 1.注释

- 注释

  - 注释行：#

   - 注释块：#[[]]

- 添加CMakeLists.txt

  - cmake_minimum_required：指定cmake最低版本（可选，非必须，但是推荐）

  - project：定义工程名称，并指定工程版本，工程描述，web主页地址，支持的语言（默认情况支持所有语言），如果不需要这些都是可以忽略的，只需要指定出工程名字

    ```cmake
    # PROJECT 指令的语法是：
    project(<PROJECT-NAME> [<language-name>...])
    project(<PROJECT-NAME>
           [VERSION <major>[.<minor>[.<patch>[.<tweak>]]]]
           [DESCRIPTION <project-description-string>]
           [HOMEPAGE_URL <url-string>]
           [LANGUAGES <language-name>...])
    ```

  - add_executable：定义工程生成一个可执行文件

    ```cmake
    add_executable(可执行程序名 源文件名)
    ```

    - 空格间隔各种源文件
    - ;间隔

### 2.执行cmake命令

```shell
cmake CMakeLists.txt所对于路径
```

## 三.set命令

### 1.定义变量

对于demo1里面的示例，一共提供了5个源文件，假设5个源文件需要反复被使用是很麻烦的，需要定义一个变量，将文件名对应的字符串存储起来，在cmake里定义变量需要使用set命令

```cmake
# SET 指令的语法是：
# [] 中的参数为可选项, 如不需要可以不写
SET(VAR [VALUE] [CACHE TYPE DOCSTRING [FORCE]])
```

- VAR：变量名
- VALUE：变量值

### 2.指定cpp标准

```shell
g++ *.cpp -std=c++11 -o app
```

在cmake里面

第一种：

```cmake
set(CMAKE_CXX_STANDARD 11)
```

第二种：

```cmake
cmake CMakeLists.txt文件路径 -DCMKAE_CXX_STANDARD = 11
#D:表明宏定义
```

### 3.指定输出的路径

在CMake中指定可执行程序输出的路径，也对应一个宏，叫做EXECUTABLE_OUTPUT_PATH，它的值还是通过set进行设置：

```cmake
set(HOME /home/robin/Linux/sort)
set(EXCUTABLE_OUTPUT_PATH ${HOME}/bin)
```

- 第一行：定义一个变量用于存储一个**绝对路径**
- 第二行：将拼接好的路径设置给EXECUTABLE_OUTPUT_PATH宏
  - 如果这个路径中的子目录不存在会自动生成，无需手动创建

**如果此处指定可执行文件程序生成的时候使用的是相对路径./xxx/xxx，那么在这个路径中的./对应的就是makefile文件所在的那个目录**

在cmakelists.txt中更推荐使用绝对路径，不会导致出现路径混乱发生（如果用./这样的相对路径一定要弄清楚相关路径的具体位置）

## 四.搜索文件路径

### 1.使用aux_source_directory

使用aux_source_dircetory命令可以查找某个路径下**所有的源文件**，命令格式为:

```cmake
aux_source_directory(< dir > < variable >)
```

- dir：要搜索的目录
- variable：将dir目录下搜索到的源文件列表存储到变量中

### 2.file命令

如果在一个项目中的源文件有很多，在编写CMakeLists.txt文件的时候不能将项目目录中的各个文件一一罗列下来，所有在CMake中提供了**搜索文件**的命令——file

```cmake
file(GLOB/GLOB_RECURSE 变量名 要搜索的文件路径和文件类型)
```

- CLOB：将指定的目录下搜索到的满足条件的所有文件名生成一个列表，并将其存储到变量中
- GLOB_RECURSE：递归搜索指定目录，将搜索到的满足条件的文件名生成一个列表，并将其存储到变量中

eg.

```cmake
file(GLOB MAIN_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE MAIN_HEAD ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
#GLOB_RECURSE会搜索${CMAKE_CURRENT_SOURCE_DIR}和${CMAKE_CURRENT_SOURCE_DIR}/include下所有.h后缀的文件
#而GLOB只会搜索${CMAKE_CURRENT_SOURCE_DIR}/src下的.cpp文件，不会搜索${CMAKE_CURRENT_SOURCE_DIR}下.cpp文件
```

**注意：${PROJECT_SOURCE_DIR}和${CMAKE_CURRENT_SOURCE_DIR}是等价的，都是cmakelists.txt所在的文件路径下**

## 五.指定头文件路径

在编译项目源文件的时候，很多时候需要将源文件对应的头文件路径指定出来，这样才能保证在编译过程中编译器能够找到这些头文件，并顺利通过编译，这个命令就是include_directories：

```cmake
include_directories(headpath)
```

## 六.变量

上述讲述了cmake这么多相关的内容，但是还有一个最重要的就像单位一样的存在在cmake中的——变量

变量是cmake语言中存储的基本单位，它们的值始终为字符串类型，我们使用set()和unset()命令显式设置和取消设置变量，变量名区分大小，目前

## 七.指定头文件路径补充

### 1. 古早cmake

在编译项目源文件的时候，很多时候有#include，且不在源文件当前的目录下，需要去在编译的时候指定头文件路径让编译器能找到相关的头文件

在过去：

```cmake
include_directories(headpath)
```

这样是全局包含，在后续add_executable编译相关可执行文件的时候，所有的可执行文件都会默认加上这个这个头文件路径，极容易导致命名空间和依赖的污染

### 2. 现代cmake

为了解决这个问题，提出了指定目标头文件路径

```cmake
target_include_directories(executable(target) PRIVATE/PUBLIC/INTERFACE headpath)
```

- executable(target)：这里就是指定的目标，有可能是生成的可执行文件也有可能是生成的库文件

- PRIVATE/PUBLIC/INTERFACE：

  - PRIVATE：后面的headpath只会包含给executable，如果executable是库文件，后续链接这个库文件的源文件不会包含相关的头文件路径（不会向后穿透，既是源文件也需要库文件中包含的头文件路径）

    **注意：这里说的是路径，不是头文件本身文件**

  - PUBLIC：和PRIVATE相对，是会向后穿透，即链接时executable包含的头文件路径也会给其他目标文件

  - INTERFACE：execuatble自己不会去包含相关的头文件路径，但是会向后穿透给链接的其他目标文件

## 八. 链接库文件

### 1. 古早cmake

```cmake
link_libraries(lib1,lib2...)
```

全局链接，**后续**所有目标都会链接相关的库文件，会污染全局作用域

### 2. 现代cmake

```cpp
target_link_libraries(target PRIVATE/PUBLIC/INTERFACE lib1.lib2...)
```

用于指定构建目标（如可执行目标或者库）在链接时需要依赖的库文件，目标或者链接标志

这个和```target_include_directories```命令有点相似，这里是将指定的库或者cmake目标链接到目标二进制文件上

- PRIVATE：只在当前目标内部使用该依赖，不传递给依赖当前目标后续目标

```
打个比方就是：
lib1只和target1链接，链接产生的二进制文件假如也是一个库文件lib2，如果后续这个lib2被链接到target2，如果target2用到了lib1中相关的api，由于是private，target2只能用到lib2中相关的api，但是用不到lib1相关的api
```

- INTERFACE：当前目标不使用，但依赖当前目标的后续目标会继承，使用这个依赖
- PUBLIC：当前目标内部使用，且会传递给依赖当前目标的后续目标

**对于头文件路径和链接的相关传递性，在rm这个算法构建中用到的也是不算特别多和特别复杂，只需要了解即可，相关链接和包含的头文件路径主动对应上去即可，无需一定用到传递性**

这里再补充一个命令：```link_directories/target_link_directories```

link_directories命令用于添加目录使链接器能在其查找库，添加路径使链接器应在其中搜索相关库，提供给此命令的相对路径被解释为相对于当前源目录

该命令只适用于在它被调用后创建的target，如果不是自己通过add_library创建出的库文件，而是第三方库文件，则需要相应的指令去告诉链接器在哪个路径下去查找相关名字的库

**注意：这个命令也和上述两类命令一样，是针对全局目录，其后面所有的target都会受到影响——查找链接库都会从这个目录下开始找，也是会导致命名空间和依赖相关的污染**

target_link_directories：仅仅针对相关目标去让链接器找相关库文件的路径

```cmake
target_link_directories(target INTERFACE/PUBLIC/PRIVATE	库文件相关路径)
```

- PRIVATE：目录仅用于编译和链接当前目标
- INTERFACE：目录会传播给依赖当前目标的其他目录，target链接相关库不会拿到库文件相关路径
- PUBLIC：兼具PRIVATE和INTERFACE

## 九. 嵌套cmake

add_subdirectory()——用于将子目录添加到构建

将子目录和主目录一起进行构建

```cmake
add_subdirectory(source_dir)
```

source_dir指定源CMakeLists.txt和代码文件所在的目录，如果是相对路径，则将相对于当前目录对其进行评估，但也可能是绝对路径

```
注意：
- 主目录中CMakeLists.txt中set的变量能给子目录的CMakeLists.txt进行使用
- 但是反过来子目录set的变量不能给主目录使用
```

## 十. CMake Install

cmake install是cmake工具的一个重要的组成部分，主要是将构建的目标（如可执行文件，库等）和其他相关文件（如头文件，配置文件等）安装到指定的位置，在CMakeLists.txt中使用install命令实现的

### 1. 目标：

add_executable或者add_library来创建一个目标，通过target_link_libraries命令为目标添加依赖项

### 2. 安装规则：

install()命令来为一个目标添加安装规则，安装规则主要包括目标安装的位置，安装的权限设置，在安装过程中需要执行的操作等

### 3. 安装路径：

通过CMAKE_INSTALL_PREFIX变量来设置安装路径的前缀，然后在install命令中通过DESTINATION参数来指定目标的具体安装位置

### 4. 组件

组件是CMake Install的一个高级概念，在一个大型项目中，我们可能会有多个目标需要安装，这些目标可能属于不同的组件，使用COMPONENT参数来为目标指定其所属的组件

### 5. Install命令的基本结构

帮助我们将构建的目标(target)和文件(file)安装到指定的位置

```cmake
install(<TYPE> files... DESTINATION <dir>
        [PERMISSIONS permissions...]
        [CONFIGURATIONS [Debug|Release|...]]
        [COMPONENT <component>]
        [OPTIONAL] [NAMELINK_ONLY|NAMELINK_SKIP])
```

- ```<TYPE>```：必选参数，定义了我们要安装的内容的类型，这个参数可以是TARGETS（目标），FILES（文件），DIRECTORY（目录）等

- ```files```：一个或者多个我们要安装的目标或者文件，对于TARGETS，这是我们在add_executable或者add_library中定义的目标名称；对于FILES和DIRECTTORY，这是文件或目录的路径

- `DESTINATION <dir>`：这是一个必选参数，它定义了我们要将文件或目标安装到哪个目录

### 6. 目标和文件的安装

#### 6.1 目标的安装：

在CMake中，目标通常是add_execuatble和add_library命令创建的可执行文件或库

```cmake
install(TARGETS myExecutable DESTINATION bin)
install(TARGETS myLibrary DESTINATION lib)
```

这里我们将myExecutable安装到bin目录，将myLibrary目标安装到lib目录

#### 6.2 文件的安装：

```cmake
install(FILES readme.txt DESTINATION doc)
```

将readme.txt安装到了doc目录

注意：install(FILES)命令只能用来安装在构建过程中不会改变的文件

### 7. 安装目录的管理

#### 7.1 使用变量管理安装目录

在CMake中，我们可以使用变量来管理安装目录

INSTALL_BIN_DIR来表示二进制文件的安装目录，在install命令使用这个变量

```cmake
set(INSTALL_BIN_DIR bin)
install(TARGETS myExecutable DESTINATION{INSTALL_BIN_DIR})
```

#### 7.2 使用GNUInstallDirs模块管理安装目录

CMake提供了一个名为GNUInstallDirs的模块，可以帮助我们更好的管理安装目录

这个模块定义了一些变量，表示了GNU系统中常见的安装目录

eg. CMAKE_INSTALL_BINDIR表示二进制文件的安装目录，CMAKE_INSTALL_LIBDIR表示库文件的安装目录

```cmake
include(GNUInstallDirs)
install(TARGETS myExecuatbale DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS myLibrary DESTINATION ${CMAKE_INSTALL_LIBDIR})
```

使用GNUInstallDirs模块可以使我们的项目更加符合GNU的标准，同时也使得安装目录的管理更加方便

### 8. CMake Install重要性

#### 8.1 项目部署

将构建的目标和相关文件安装到指定的位置，从而方便用户或者开发者使用，安装包的制作就需要依赖CMake Install

#### 8.2 版本控制

cmake install可以帮助更好地进行版本控制，通过CMake Install，我们可以将不同版本的目标安装到不同的位置，避免版本冲突

### 9. CMake Install高级用法

#### 9.1 如何配置CMake Install

- 定义安装规则
- 配置安装目录
- 生成安装脚本

##### 9.1.1 定义安装规则

```cmake
install(TARGETS myAPP DESTINATION bin)
install(FILES myconfig.h DESTINATION include)
```

##### 9.1.2 配置安装目录

配置安装目录——决定了安装文件的最终位置

```cmake
set(CMAKE_INSTALL_PREFIX /usr/local)
set(CMAKE_INSTALL_BINDIR bin)
```

在CMake中，我们可以使用变量来定义安装目录，这些目录包括：

```CMAKE_INSTALL_PREFIX(安装前缀)```和```CMAKE_INSTALL_BINDIR(二进制文件目录)```等

### 10. 其他

使用CMake Install进行版本控制

通过install(EXPORT)命令将我们的目标导出为一个导出集，然后在其他的CMake项目中通过find_package()命令来查找和使用这个导出集

```cmake
install(TARGETS my_library EXPORT MyLibraryTagets)
```

```cmake
find_package(MyLibrary)
```

## 十一. find_package()指令

CMake的find_package指令是管理项目的核心命令，主要是两个模式

- config-files
- find-module

来定义外部库

![cmake](/home/ubuntu/图片/cmake.png)

### 1. config-file模式（首选）

- 工作原理：直接调用库提供商生成的```<PackageName>Config.cmake```或者```<package-name>-config.cmake```脚本，**该脚本能精确导入目标（YourLib::YourLib）并设置所有依赖信息**
- 先决条件：
  - 库本身必须提供config文件，现在cmake或者使用cmake构建的库通常都会提供
  - 你需要通过```<PackageName>_DIR```变量告诉CMake这个Config文件的位置
  - 设置CMAKE_PREFIX_PATH环境变量或者缓存变量也能提示搜索路径

### 2. find_module模式

- 工作原理：执行由CMake或你的项目提供的```Find<PackageName>.cmake```脚本，这个脚本负责“猜测”并定位库头文件和二进制文件，结果通常一系列变量输出
- 先决条件：
  - 需要在CMAKE_MODULE_PATH包含的路径存在对应的```Find<PackageName>.cmake```文件
  - 库需要按照约定安装，以便脚本能通过系统路径，已知环境变量或特定命名规则找到它

用到最多的就是：find_package(... REQUIRED)

```
REQUIRED：关键参数，指定依赖是必需的，如果未找到包，CMake将立即报错并终止配置过程，这能确保构建不会在缺失关键依赖的情况下继续进行
```

最佳实践方式：

- 优先使用config-file模式：更可靠，更精确，现代库通常提供Config文件
- 善用REQUIRED关键字：对于项目必须的依赖，总是使用REQUIRED，这样可以实现快速失败，避免后续出现令人困惑的错误
- 首选导入的目标（Imported Targets）：如果包提供了导入的目标（eg.Boost::iostreams/Qt5::Widgets），应优先通过**target_link_libraries(your_target PRIVATE SomeLib::SomeLib)**来使用，这种方式能自动传递所有必要的编译属性（如头文件路径，编译定义和链接库）
- 谨慎使用结果变量：即是找到包，也不要直接使用像```<PackageName>_INCLUDE_DIRS```这样的缓存变量，通过导入目标来获取这些信息是最安全，最现代的方式

## 十一. 目标文件

笔者在总结上述文档时，发现了没有对相关目标文件进行总结，笔者认为：目标文件就是生成的二进制文件——一般分为：

- 可执行文件
- 库文件

### 1. 可执行文件

可执行文件一般是最后经过编译和链接生成的二进制文件

通过```add_executable()```命令进行生成可执行文件

```cmake
add_execuatble(exec_name src.cpp)
```

- exec_name：生成的可执行文件的名字
- src.cpp：对于生成可执行文件相关的源文件，可以是1个也可以是多个

### 2. 库文件

其实库文件也是一个二进制文件，分成静态库和动态库

- 静态库(.a/.lib)：链接阶段和相关目标文件一起生成相关可执行文件
- 动态库(.so/.dll)：不是直接进行链接，而是在运行阶段才将动态库相关的内存数据注入可执行文件进行执行相关操作

其实这里可以做一个小实验：将同一（些）.cpp生成的静态库和动态库分别和相关目标文件进行链接，后续再对生成的静态库和动态库分别进行删除再运行可执行文件，这时候可以发现由静态库生成的可执行文件可以运行但是由动态库生成的则不行——证明了上述观点

通过```add_library()```命令进行生成库文件

```cmake
add_library(lib_name STATIC/SHARED src.cpp)
```

- lib_name：生成的库文件的名字
- STATIC：静态库  /  SHARED：动态库（共享库）
- src.cpp：对于生成库文件相关的源文件，可以是1个也可以是多个

## 十二. CMake编译模式

cpp通常需要区分调试版本(debug)和发布版本(Release)，cmake通过```CMAKE_BUILD_TYPE```控制

### 1. Debug模式和Release模式

- Debug：
  - 包含调试信息，体积较大，一般不进行激进优化，便于单步调试
  - Linux下生成elf可执行文件（以及调试符号）
- Relese：
  - 侧重优化，代码体积和运行速度更优，一般不包含调试符号

### 2. 在CMake中设置编译模式

通过CMAKE_BUILD_TYPE指定：

#### 命令行指定

```shell
cmake -DCMAKE_BUILD_TYPE = Debug
cmake -B build

cmake -DCMAKE_BUILD_TYPE = Release
cmake -B build
```

#### 在CMakeLists.txt中指定默认值

```cmake
#若用户未指定，则默认为DEBUG；用户可通过-D覆盖
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif()
#或者直接set变量写死
#set(CMAKE_BUILD_TYPE Release)
#不推荐
```

### 3.其他构建类型

除了```DEBUG```，```RELEASE```之外，cmake还常用于：

- RelWithDebInfo：带有调试信息的Release风格优化
- MinSizeRel：最小体积优化

对应变量：```CMAKE_CXX_FLAGS_RELWITHDEBINFO```，```CMAKE_CXX_FLAGS_MINSIZEREL```等

### 4. 检查是否有调试信息

Linux下可以用```readelf```来看可执行文件是否包含调试段

```shell
readelf -S <bin目录像>/myapp | grep debug
```

若有```.debug_info```，```.debug_line```等段，说明包含调试信息，而```Release```构建通常没有
