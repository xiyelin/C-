## C++ 函数重载的实现原理

----------------------------------------------------

## C++ 要实现函数重载需要考虑解决的问题：

	1.声明和定义的时候，C++底层是如何解决命名冲突的？
  
	2.在调用重载函数的时候，编译器怎么知道要调用哪个重载函数？

  
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





