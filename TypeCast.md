### C++中的类型转换：

>static_cast <br>
 reinterpret_cast <br>
 const_cast <br>
 dynamic_cast <br>
 
<br>
<br>
*  `static_cast`  

    static_cast 用于静态转换，任何标准准换都可以用它，但是不能用于不相关类型的转换。
    

```cpp

    例如：

        void Test()
        {
            int i = 10;
            
            double d = static_cast<double>(i);
            
            printf("%d %0.2f\n", i, d);
        }

```

<br>
*  `reinterpret_cast`  

    reinterpret_cast用于将一种类型转换为另一种不同的类型。reinterpret_cast<type-id> (expression)，type-id 必须
    
    是一个指针、引用、算术类型、函数指针或者成员指针。它可以把一个指针转换成一个整数，也可以把  
    
    一个整数转换成一个指针（先把一个指针转换成一个整数，再把该整数转换成原类型的指针，还可以得
    
    到原先的指针值）。reinterpret_cast是为了映射到一个完全不同类型的意思，这个关键词在我们需要
    
    把类型映射回原有类型时用到它。我们映射到的类型仅仅是为了故弄玄虚和其他目的，这是所有映射中
    
    最危险的。(这句话是C++编程思想中的原话)
    
    
```cpp

    static_cast和reinterpret_cast的区别主要在于多重继承，比如：
    
        class A
        {
        public:
            int m_a;
        };
         
        class B
        {
        public:
            int m_b;
        };
 
        class C : public A, public B 
        {};

        void main()
        {
            C c;
            
            printf("%p, %p, %p", &c, reinterpret_cast<B*>(&c), static_cast <B*>(&c));
        }

    前两个的输出值是相同的，最后一个则会在原基础上偏移4个字节，这是因为 static_cast 计算了父子类指针转换的偏移量，
    
    并将之转换到正确的地址（c里面有m_a,m_b，转换为B*指针后指到m_b处），而 reinterpret_cast 却不会做这一层转换。
    
    所以要 `谨慎` 使用 reinterpret_cast。
    

```


<br>
*  `const_cast`  

    const_cast最常用的用途就是删除变量的const属性，方便赋值。
    

    
```cpp

    例如：
    
        void Test ()
        {
            const int a = 2;
            int* p = const_cast< int*>(&a );    //去常属性
           
            *p = 3;
            cout<<a <<endl;
        }

```

<br>
*  `dynamic_cast`  

    dynamic_cast用于将一个父类对象的指针转换为子类对象的指针或引用（动态转换）

    向上转型：子类对象指针->父类指针/引用（不需要转换）<br>
    向下转型：父类对象指针->子类指针/引用（用dynamic_cast转型是安全的）
    
    1. dynamic_cast只能用于含有虚函数的类
    2. dynamic_cast会先检查是否能转换成功，能成功则转换，不能则返回0


    
```cpp

    例如：

        class A
        {
        public :
            virtual void f(){}
        };
        
        class B : public A
        {};
        
        void fun (A* pa)
        {
            // dynamic_cast会先检查是否能转换成功，能成功则转换，不能则返回
            B* pb1 = static_cast<B*>(pa);
            B* pb2 = dynamic_cast<B*>(pa);
            
            cout<<"pb1:" <<pb1<< endl;
            cout<<"pb2:" <<pb2<< endl;
        }
        
        int main ()
        {
            A a;
            B b;
            
            fun(&a);
            fun(&b);
            
            return 0;
        }
    

```

<br>
*  `explicit关键字`

    通常，只有一个参数的构造函数可被用于隐式转换，explicit关键字阻止经过转换构造函数进行的隐式转换的发生。
    
    作用：避免不合时宜的转换。


```cpp

    例如：
    
        class A
        {
        public :
            explicit A (int a)
            {
                cout<<"A(int a)" <<endl;
            }
        
            A(const A& a)
            {
                cout<<"A(const A& a)" <<endl;
            }
        
        private :
            int _a ;
        };
        
        int main ()
        {
            A a1 (1);
            
            // 隐式转换-> A tmp(1); A a2(tmp);
            A a2 = 1;
        }
    
    
```











