-----
#### 　　我们知道C语言中本身没有提供字符串类型，但是给了一系列的字符串操作函数的接口来  
#### 操作字符串。String类是C++中的一个字符串类，它将字符串的一系列操作都封装在一起。而  
#### 且和 `char*`相比，它更加方便灵活，不用担心内存不足，字符串的长度是否越界等等问题。 
-----

<br>
### String类的几种实现方法：
<br>
#### 方法一：<深拷贝>

```cpp
        
        //每个字符串都拥有自己独立的内存空间
        //深拷贝        空间利用率低
        class String
        {
        public:
        	String(const char* s = NULL)
        	{
        		if (NULL == s)
        		{
        			_a = new char[1];                        //如果为空，就给一个字符串结束的标志
        			_a[0] = '\0';
        		}
        		else
        		{
        			_a = new char[strlen(s) + 1];            //最好检查是否会抛出异常
        			strcpy(_a, s);
        		}
        	}
        	~String()
        	{
        		if (_a)
        		{
        			delete[] _a;
        			_a = NULL;
        		}
        	}
        	String(const String& s)
        	{
        		_a = new char[strlen(s._a) + 1];              //最好检查是否会抛出异常
        		strcpy(_a, s._a);
        	}
        	String& operator=(const String& s)
        	{
        		if (this != &s)
        		{
        			if (_a)                                   //防止内存泄露
        			{
        				delete[] _a;
        				_a = NULL;
        			}
        
        			_a = new char[strlen(s._a) + 1];          //最好检查是否会抛出异常
        			strcpy(_a, s._a);
        		}
        
        		return *this;
        	}
        
        private:
        	char* _a;
        };


```
<br>
#### 方法二：<引用计数浅拷贝（1/2）>

```cpp

        //浅拷贝   空间利用率高，但是利用指针_pRefCount会产生大量的内存碎片
        
        class String
        {
        public:
        	String(const char* s = "")
        	{
        		if (NULL == s)
        		{
        			_a = new char[1];
        			_a[0] = '\0';
        		}
        		else
        		{
        			_a = new char[strlen(s) + 1];
        			strcpy(_a, s);
        		}
        
        		_pRefCount = new int[1];                    //每块空间都有一个引用计数，初始化为1
        		*_pRefCount = 1;
        	}
        	~String()
        	{
        		if (1 == *_pRefCount)                       //当引用计数为1时，才释放该空间
        		{
        			delete[] _a;
        			delete _pRefCount;
        			_a = NULL;
        			_pRefCount = NULL;
        		}
        		else
        			--(*_pRefCount);
        	}
        	String(const String& s)
        	{
        		_a = s._a;
        		_pRefCount = s._pRefCount;
        
        		++(*s._pRefCount);
        	}
        	String& operator=(const String& s)
        	{
        		if (this != &s)
        		{
        			if (_a)                                   //防止内存泄露
        			{
        				delete[] _a;
        				delete _pRefCount;
        			}
        
        			_a = s._a;
        			_pRefCount = s._pRefCount;
        			++(*_pRefCount);
        		}
        
        		return *this;
        	}
        
        
        private:
        	char* _a;
        	int* _pRefCount;
        };


```

<br>
#### 方法二：<引用计数浅拷贝（2/2）>

```cpp

        //这种引用计数把_a的前4个字节当做是_pRefCount，通过指针偏移和强制类型转换来改变引用计数
        //减少了开辟空间的次数，和内存碎片
        class String
        {
        public:
        	String(const char* s = "")
        		:_a(new char[strlen(s) + 5])
        	{
        		_a += 4;
        		_GetRefCount(_a) = 1;
        		strcpy(_a, s);
        	}
        	~String()
        	{
        		if (1 == _GetRefCount(_a))
        		{
        			_a -= 4;
        			delete[] _a;
        			_a = NULL;
        		}
        	}
        	String(const String& s)
        	{
        		_a = s._a;
        		++_GetRefCount(s._a);
        	}
        	String& operator=(const String& s)
        	{
        		if (this != &s)
        		{
        			if (1 == _GetRefCount(_a))
        			{
        				_a -= 4;
        				delete[] _a;
        				_a = NULL;
        			}
        
        			_a = s._a;
        			++(_GetRefCount(s._a));
        		}
        
        		return *this;
        	}
        
        	char& operator[](int index)                         //写时拷贝，在需要改变字符串内容的时候用
        	{
        		if (_GetRefCount(_a) > 1)
        		{
        			char* tmp = new char[strlen(_a) + 5];
        			tmp += 4;
        			strcpy(tmp, _a);
        
        			_GetRefCount(tmp) = 1;
        			--_GetRefCount(_a);
        
        			_a = tmp;
        		}
        
        		return _a[index];
        	}
        
        protected:
        	int& _GetRefCount(char* a)
        	{
        		assert(a);
        
        		return (*(int*)(a - 4));            //通过指针偏移和强转来取得_pRefCount的值
        	}
        
        private:
        	char* _a;
        };


```
    











