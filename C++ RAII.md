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


## 八大智能指针的简单实现：

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


	No.2  scoped_ptr
	
```cpp

		
		
		
		
		
		
		
		
		
		
```


	

























































    
    
    
    
    
    
    
    

