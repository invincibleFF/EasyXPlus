## EasyXPlus
EasyXPlus is a simple graphic library **for C++ BEGINNERS** under Windows. It provides following features:

*	**Simple**. It encapsulate GDI functions, so users do not need to learn the complex Win32 programming environment.
*	**Small**. It only wraps a part of GDI functions that newbies may be interested ( after all, it's a library for beginners! ).

## How to build
### From project templates
There are two build templates using VS under the `builds` folder, users can use these project templates to build with the right VS version installed.

### From source
Also, users can use any c++ develop environment to build using source files under `src` folder. Note to install a appropriate Windows SDK first！

## Guide to use
1.	**Set the entry point to wWinMainCRTStartup**. We build the wWinMain function inside the library which possibly makes VS finding entry point automatically unpossible. Thus, we need to set it manually.
2.	**Add library and header files** to you project (header files are under the `headers` folder).
3.	**Use Unicode character set**(VS use this by default).

If you don't know how to set these configurations in you IDE, please google.

## Samples
There is a sample using **Keyboard**, **Mouse**, **Geometry** and **Window** modules under `sample` folder, maybe it is a good start place for you. 

## Bugs
1.	Keyboard and Mouse modules not work when library was built with /O2 optimization level opened.