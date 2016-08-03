### 　　RAII，也称为“资源获取就是初始化”，是c++等编程语言常用的管理资源、避免内存泄露的方
### 法。它保证在任何情况下，使用对象时先构造对象，在对象生命期控制对资源的访问使之始终保持
### 有效，最后析构对象。 

-----------------------------------------

<br>

## 智能指针：

    为什么要使用智能指针？
    
        因为C++编程语言没有内存自动回收机制，程序员手动开辟的内存，在生命周期完成以后，必须手动的去释放相应的内存。然而，
        
    往往在大型项目中，程序员很可能会遗忘，最终导致内存泄漏，或者程序直接挂掉等意想不到的结果。而智能指针恰恰可以缓解这种
    
    因为遗忘或者疏忽造成的错误。
    
        智能指针，它是C++封装的一个类，并不是传统意义上的指针。智能指针(smart pointer)的一种通用实现技术是使用引用计数
    
    (reference count)。智能指针类将一个计数器与类指向的对象相关联，引用计数跟踪该类有多少个对象共享同一指针。


## 智能指针的简单实现：

![image](http://hbimg.b0.upaiyun.com/e154aff72d0d52c7c5f6e56cb3a68f2dc13057e4194a0-ACqqyf_fw658)

<br>


    No.1  auto_ptr
    
```cpp
		//方法一
		template<class T>
		class Auto_Ptr
		{
		public:
		    Auto_Ptr(T* ptr)
		        :_ptr(ptr)
		        ,_owner(true)
		    {}
		    ~Auto_Ptr()
		    {
		        if (_owner == true)
		        {
		            delete _ptr;
		            _ptr = NULL;
		        }
		    }
		    Auto_Ptr(Auto_Ptr<T>& ap)
		    {
		        ap._owner = false;
		        _owner = true;
		
		        _ptr = ap._ptr;
		    }
		    Auto_Ptr<T>& operator=(Auto_Ptr<T>& ap)
		    {
		        if (this != &ap)
		        {
		            ap._owner = false;
		            _owner = true;
		
		            _ptr = ap._ptr;
		        }
		
		        return *this;
		    }
		
		public:
		    T& operator*()
		    {
		        return *_ptr;
		    }
		    T* operator->()
		    {
		        return _ptr;
		    }
		    T* GetPtr()
		    {
		        return _ptr;
		    }
		
		private:
		    T *_ptr;             //指针
		    bool _owner;         //当前拥有者为true,否则为false
		};
		
		
```

![image](http://hbimg.b0.upaiyun.com/8a67f47c792c35271689c31171d2313bf3cc17aa11eae-APabSq_fw658)

<br>

```cpp

		//方法二：
		template<class T>
		class Auto_ptr
		{
		public:
		    explicit Auto_ptr(T *ptr = NULL)
		        :_ptr(ptr)
		    {}
		    ~Auto_ptr()
		    {
		        delete _ptr;
		        _ptr = NULL;
		    }
		    Auto_ptr(Auto_ptr<T>& ap)
		        :_ptr(ap._ptr)
		    {
		        ap._ptr = NULL;
		    }
		    Auto_ptr<T>& operator=(Auto_ptr<T>& ap)
		    {
		        if (this != &ap)
		        {
		            if (NULL != _ptr)
		                delete _ptr;
		            _ptr = ap._ptr;
		            ap._ptr = NULL;
		        }
		
		        return *this;
		    }
		
		public:
		    T& operator*()const
		    {
		        return *_ptr;
		    }
		    T* operator->()const
		    {
		        return _ptr;
		    }
		    T* GetPtr()const
		    {
		        return _ptr;
		    }
		
		private:
		    T *_ptr;                //只有一个指针
		};
		
		
```

![image](http://hbimg.b0.upaiyun.com/566081c5f0c1c006e3ea46516892fd6fb150ef6db448-eIsoTD_fw658)

<br>


	No.2  scoped_ptr：防拷贝
	
```cpp

		template<class T>
		class Scoped_Ptr
		{
		public:
		    Scoped_Ptr(T *ptr)
		        :_ptr(ptr)
		    {}
		    ~Scoped_Ptr()
		    {
		        delete _ptr;
		        _ptr = NULL;
		    }
		
		public:
		    T& operator*()
		    {
		        return *_ptr;
		    }
		    T* operator->()
		    {
		        return _ptr;
		    }
		    T* GetPtr()
		    {
		        return _ptr;
		    }
		        
		private:
		    //只声明，不定义--->防拷贝
		    //声明为私有，防止在类外定义
		    Scoped_Ptr(Scoped_Ptr<T>& sp);
		    Scoped_Ptr<T>& operator=(Scoped_Ptr<T>& sp);
		
		
		private:
		    T *_ptr;
		};
		
		
```

<br>

	No.3  scoped_array：防拷贝
	
```cpp

		template<class T>
		class Scoped_Array
		{
		public:
		    Scoped_Array(T *ptr)
		        :_ptr(ptr)
		    {}
		    ~Scoped_Array()
		    {
		        delete []_ptr;
		        _ptr = NULL;
		    }
		
		    T& operator[](size_t index)
		    {
		        return _ptr[index];
		    }
		
		protected:
		    Scoped_Array(const Scoped_Array& sa);
		    Scoped_Array& operator=(const Scoped_Array& sa);
		
		private:
		    T *_ptr;
		};
		
		
```

<br>

	No.4  shared_ptr：引用计数的方法

```cpp

		template<class T>
		class Shared_Ptr
		{
		public:
		    Shared_Ptr(T *ptr)
		        :_ptr(ptr)
		        ,_pCount(new int(1))
		    {}
		    ~Shared_Ptr()
		    {
		        if (1 == *_pCount)
		        {
		            delete _ptr;
		            _ptr = NULL;
		        }
		
		        --(*_pCount);
		    }
		    Shared_Ptr(const Shared_Ptr<T>& sp)
		    {
		        _ptr = sp._ptr;
		        ++(*sp._pCount);
		        _pCount = sp._pCount;
		    }
		    //常规写法
		    Shared_Ptr<T>& operator=(const Shared_Ptr<T>& sp)
		    {
		        if (this != &sp)
		        {
		            if (NULL != _ptr)
		            {
		                if (*_pCount == 1)
		                    delete _ptr;
		                else
		                    --(*_pCount);
		            }
		
		            _ptr = sp._ptr;
		            ++(*sp._pCount);
		            _pCount = sp._pCount;
		        }
		
		        return *this;
		    }
		    //现代写法
		    //Shared_Ptr<T>& operator=(Shared_Ptr<T> sp)
		    //{
		    //    swap(_ptr, sp._ptr);
		    //    swap(_pCount, sp._pCount);
		
		    //    return *this;
		    //}
		
		public:
		    T* operator*()
		    {
		        return *_ptr;
		    }
		    T& operator->()
		    {
		        return _ptr;
		    }
		    T& GetPtr()
		    {
		        return _ptr;
		    }
		
		
		private:
		    T *_ptr;             //指针域
		    int *_pCount;        //引用计数
		};
		
		
```

<br>

	No.5  shared_array
	
```cpp

		template<class T>
		class Shared_Array
		{
		public:
		    Shared_Array(T *ptr)
		        :_ptr(ptr)
		        ,_pCount(new int(1))
		    {}
		    ~Shared_Array()
		    {
		        if (1 == *_pCount)
		        {
		            delete []_ptr;
		            _ptr = NULL;
		        }
		
		        --(*_pCount);
		    }
		    Shared_Array(const Shared_Array<T>& sp)
		    {
		        _ptr = sp._ptr;
		        ++(*sp._pCount);
		        _pCount = sp._pCount;
		    }
		    //常规写法
		    Shared_Array<T>& operator=(const Shared_Array<T>& sp)
		    {
		        if (this != &sp)
		        {
		            if (NULL != _ptr)
		            {
		                if (*_pCount == 1)
		                    delete _ptr;
		                else
		                    --(*_pCount);
		            }
		
		            _ptr = sp._ptr;
		            ++(*sp._pCount);
		            _pCount = sp._pCount;
		        }
		
		        return *this;
		    }
		    //现代写法
		    //Shared_Array<T>& operator=(Shared_Array<T> sp)
		    //{
		    //    swap(_ptr, sp._ptr);
		    //    swap(_pCount, sp._pCount);
		
		    //    return *this;
		    //}
		
		    T& operator[](size_t index)
		    {
		        return _ptr[index];
		    }
		
		private:
		    T *_ptr;             //指针域
		    int *_pCount;        //引用计数
		};
		
		
```

<br>

	No.6  weak_ptr

	weak_ptr是为了配合shared_ptr而引入的一种智能指针，它更像是shared_ptr的一个助手而不是智能指针，因为它不具有
	普通指针的行为，没有重载operator*和->,它的最大作用在于协助shared_ptr工作。
	
	1. expired() 用于检测所管理的对象是否已经释放；
	2. lock() 用于获取所管理的对象的强引用指针；
	3. 通过weak_ptr来打破shared_ptr的循环引用问题；weak_ptr没有共享资源，它的构造不会引起指针引用计数的增加；




```cpp

		template<typename T> 
		class weak_ptr
		{
		 public:
		     template <typename Y>
		     weak_ptr(const shared_ptr<Y>& r);
		 
		     weak_ptr(const weak_ptr& r);
		     
		     ~weak_ptr();
		 
		     T* get() const; 
		     bool expired() const; 
		     shared_ptr<T> lock() const;
		};
		
		
		
```

<br>

























	

























































    
    
    
    
    
    
    
    

