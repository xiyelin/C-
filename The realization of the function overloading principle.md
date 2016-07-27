## C++ 函数重载的实现原理

----------------------------------------------------

<br>

## C++ 要实现函数重载需要考虑解决的问题：

	1.声明和定义的时候，C++底层是如何解决命名冲突的？
  
	2.在调用重载函数的时候，编译器怎么知道要调用哪个重载函数？


## 什么是函数重载？
	
	在同一作用域下，函数名相同，参数列表不同（参数个数或顺序不同），返回值可以相同，也可以不同的一组函数；
	
	重载函数通常用来命名一组功能相似的函数，这样做减少了函数名的数量，避免了名字空间的污染，对于程序的可
	
	读性有很大的好处。

  
### 首先我们来看一个函数重载的例子：

```cpp

		# include <iostream>
		using namespace std;
		
		//整型的比较
		int Max(int a, int b)                                 
		{
		    cout << "int Max(int a, int b)" << endl;
		
		    return a > b ? a : b;
		}
		//浮点型的比较
		double Max(double a, double b)
		{
		    cout << "double Max(double a, double b)" << endl;
		
		    return a > b ? a : b;
		}
		
		int main()
		{
		    cout << Max(2, 5) << endl;
		    cout << Max(1.9, 9.9) << endl;
		
		    system("pause");
		    return 0;
		}
		
		
```
![image](http://hbimg.b0.upaiyun.com/d4d3f919ab19eee6f9a5b5ce9726e514e99d1c051c43-K5JKNa_fw658)

<br>

### 为什么需要重载函数？

	1.上述例子，如果我们在C语言中实现，我们必须这样来定义： int_max(int, int), double_max(double,double);
	  
	  试想，我们如果需要比较所有的内置类型的比较，那我们必须为实现同一功能的函数取多个函数名。
	  
	2.例如：C++中的构造函数，如果我们想实现不同的构造函数，就得命名许多不同的函数名，很不方便。
	
	3.操作符重载，本质也是函数重载，它丰富了操作符的含义，对于程序设计人员来说，更加方便，高效。
	

## 编译器是如何解决命名冲突的？

	我们使用上述例子，进行反汇编查看如下：

![image]()
	
	
	
	
	
	
	
	
	
	
	
	





