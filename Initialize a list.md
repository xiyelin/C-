## 初始化列表（Initialize a list）

----------------------------


	构造函数与类名同名，没有返回值，可以重载，与其它函数不同的是，它还有初始化列表；
	
### 为什么要有初始化列表？

	1.常量成员，因为常量只能初始化不能赋值，所以必须放在初始化列表里面；
	
	2.引用类型，引用必须在定义的时候初始化，并且不能重新赋值，所以也要写在初始化列表里面；
	
	3.没有默认构造函数的类类型，因为使用初始化列表可以不必调用默认构造函数来初始化，而是
	  直接调用拷贝构造函数初始化；

<br>

### 为什么使用初始化列表效率更高？

	1.对于内置类型，如：int char 等来说，初始化列表和构造函数体内初始化效率差不多；
	
	2.一旦类中含有类对象的时候，那么初始化列表的效率就高得多；原因如下：


```cpp
		
		# include <iostream>
		using namespace std;
		
		class A
		{
		public:
		    A()
		    {
		        cout << "A()" << endl;
		    }
		
		    A(const A& a)
		    {
		        cout << "A(const A& a)" << endl;
		    }
		
		    A& operator=(const A& a)
		    {
		        cout << "A& operator=(const A& a)" << endl;
		
		        return *this;
		    }
		};
		
		class B
		{
		public:
		    //在构造函数内初始化
		    B(const A& a)
		    {
		        _a = a;
		    }
		
		    //在初始化列表初始化
		    //B(const A& a)
		    //    :_a(a)
		    //{}
		
		private:
		    A _a;
		};
		
		int main()
		{
		    A a;
		    B b(a);
		
		    system("pause");
		    return 0;
		}
		
		
		
```

	分析：
	
	1.在构造函数体内进行初始化：

![image](http://hbimg.b0.upaiyun.com/136ddda32c901980523cd71df9a2c122f10cc1f44e04-A2qwV1_fw658)

	2.在初始化列表初始化：

![image](http://hbimg.b0.upaiyun.com/834d1700a286b314b4d07db6f8836d1385830fe0441c-YhD5wA_fw658)

<br>
<br>

















