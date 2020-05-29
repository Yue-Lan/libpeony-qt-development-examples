# libpeony-qt-development-examples
这是libpeony-qt的测试用例，提供了各个关键组件的简单使用方法。

## 为什么单独创建这样一个项目？
我在源码的开发中也会不停的写测试用例，这里我得吐槽一下qmake的模板机制，我必须为每一个测试用例单独创建一个pro文件才行，这样源码目录在qtcreator里看起来就很乱，而且每个用例需要的代码又不同，相互间的关系变得很复杂。

反正本来就是打算提供一个框架供于开发的，这些测试用例正好可以做这些验证，也可以解放我源码里的测试用例了。

## 构建与测试

### 依赖
我们需要libpeony-qt的头文件和so库才能进行构建，为了方便大家快速构建，我提供了两种依赖安装方式：

1. 从peony项目的libpeony-qt源码构建安装依赖（推荐）

- git clone [peony项目](https://github.com/ukui/peony)， 然后进入libpeony-qt目录，build后执行：

- > sudo make install

- 这样我们就能得到开发必须的头文件和so库，另外我也编写了pkgconfig文件，建议大家使用pkg-config进行项目的构建，qmake的构建用例可以参考该项目下的代码，其它的请自行尝试。

2. 从我的ppa中使用apt安装dev包（和源码未必同步，总是落后）

- 这个方法比较方便，但是目前只提供了eoan的源码包，而且我不能保证我对这个包的更新频率，所以可能会导致一些用例无法通过测试，具体操作如下

- > sudo add-apt-repository ppa:larue/peony-qt-development

- 确认后更新

- > sudo apt update

- 安装libpeony-qt和libpeony-qt-dev

- > sudo apt install libpeony-qt-dev

### 推荐安装的包

如果是ppa方法安装编译依赖，可以发现我附加了qt5-gtk2-platformtheme和t5-gtk-platformtheme作为推荐安装的包，主要是考虑到主题的问题，文件管理器的图标大部分使用系统主题的图标，如果主题不对，那么文件视图的图标是无法正常显示的。

### 开始构建与测试

你可以使用qtcreator进行图形化的构建和与测试，或者只是使用qmake命令，这不是什么困难的事情；但是在之前首先得确保你的编译依赖。

## 从简单的例子开始

高楼大厦不是一步建起的，一个框架的实现也都是从简单的封装开始，一层一层的实现，最后才能以高级API的形式展现在我们的眼前。高级的API虽然易用，但是不会暴露过多的实现接口，使用的场景也受到各种限制。

我建议以这样的顺序去了解libpeony-qt整个框架，首先是它的核心部分，core是对glib/gio api的第一层封装；然后是file-operation，它是介于高级api和glib/gio以及core之间的一层；最后是model层以及view层，它实现了libpeony-qt的底层api向qt model/view设计模式的抽象。

在exaples中，
file-enumerations和info-querying目录下的demo属于底层api，我建议先从这两个目录下的demo看起；而model目录下的demo则属于顶层api，可读性强、易于使用，但是难以完全理解。至于中间层级的api，我也许很难将它们以一个比较合适的demo展现出来，但也并不意味着它不重要。

## Hacking、Issue与Contribute

我希望大家能够通过这些例子去理解如何使用libpeony-qt去开发一个文件管理器，我不会暴露我对glib的封装，这些意义不大，我想让大家以qt的思路去进行快速的开发，这样能够提升很多效率。

在看懂了这些用例以后，我希望你能够了解我为什么设计这样的一个框架，这对于你掌握和使用它是很有帮助的，而不是仅仅只是照搬例子中的代码，最重要的是自己的思路。

如果你对qt的model/view编程已经有了比较深刻的了解，同时对于glib和gio的接口也很熟悉的话，我欢迎你加入到Peony的开发中来；如果还没有，也可以先从这些简单例子入手。

我欢迎大家提出issue，不限于bug和feature；大家的建议可能成为未来Peony的导向，毕竟我一个人的视野是有限的。
