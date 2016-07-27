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
	

## 编译器是如何解决命名冲突的？(分为全局函数重载和成员函数重载)

	上述例子重载的函数都是全局的，我们在CentOS 下使用命令：objdump -d a.out >log.txt 将反汇编重定向到该文件；
	
	我们使用上述例子，进行反汇编查看如下：

![image](http://hbimg.b0.upaiyun.com/82bbe9f8a855ae25ae6e6e2d5dc0db95724b7b7512218-yZpxb9_fw658)

<br>
	
	int Max(int a, int b)    					---->    _Z3Maxii
	
	double Max(double a, double b)				---->    _Z3Maxdd
	
	_Z后面的参数3代表返回值的类型，即整型为3，不同的编译器可能不同，本文用g++编译的；
	
	函数签名规则： 返回值类型+函数名+参数类型
	
<br>
<br>

### 类的成员函数命名规则：

```cpp
		
		# include <iostream>
		using namespace std;
		
		class Compare
		{
		public:
		    int Max(int a, int b)
		    {
		        cout << "int Max(int a, int b)" << endl;
		
		        return a > b ? a : b;
		    }
		
		    double Max(double a, double b)
		    {
		        cout << "double Max(double a, double b)" << endl;
		
		        return a > b ? a : b;
		    }
		};
		
		
		int main()
		{
		    Compare c;
		
		    cout << c.Max(2, 5) << endl;
		    cout << c.Max(1.9, 9.9) << endl;
		
		    system("pause");
		    return 0;
		}
		
		
```

#### 类的成员函数的反汇编：

![image](http://hbimg.b0.upaiyun.com/80cad2e56602bd5bfef3ec3b8571833c5ae0d92613436-N8pidX_fw658)

<br>

	int Max(int a, int b)                        ----> _ZN7Compare3MaxEii 
	
	double Max(double a, double b)               ----> _ZN7Compare3MaxEdd
	
	其中_Z后面的N7Compare代表作用域，3为返回值类型，后面为函数名和参数列表；
	
	成员函数签名规则： 作用域+返回值类型+函数名+参数列表
	
	
<br>
<br>

### 为什么我们不把返回值类型考虑到函数重载中呢？


	如果返回类型考虑到函数重载中，这样将不可能再独立于上下文决定调用哪个函数。
	
	这是为了保持解析操作符或函数调用时，独立于上下文（不依赖于上下文），看下面的例子：
	
```cpp
		
		float sqrt(float);
		double sqrt(double);

		void f(double da, float fla)
		{
		      float fl=sqrt(da);//调用sqrt(double)
		      double d=sqrt(da);//调用sqrt(double)
		
		      fl=sqrt(fla);//调用sqrt(float)
		   	  d=sqrt(fla);//调用sqrt(float)
		}
		
		
```

<br>

## 重载函数的调用匹配

	重载函数的匹配步骤：
	
	1.精确匹配：参数匹配而不做转换，或者只是做微不足道的转换，如数组名到指针、函数名到指向函数的指针、T到const T； 
	
	2.提升匹配：即整数提升（如bool 到 int、char到int、short 到int），float到double 
	
	3.使用标准转换匹配：如int 到double、double到int、double到long double、Derived*到Base*、T*到void*、int
						到unsigned int；
	
	4.使用用户自定义匹配；
	
	5.使用省略号匹配：类似printf中省略号参数；
	
	注意：如果在最高层有多个匹配函数找到，调用将被拒绝（因为有歧义、模凌两可）。
	
<br>
<br>

## 编译器是如何解析重载函数调用的？

	



	

	
	
	
	
	
	
	
	
	
	
	
	
	





