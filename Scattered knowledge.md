### C++中零碎的知识点

-----------------------------------------

<br>

>关于初始化顺序： <br>
>> 成员变量按声明的顺序依次初始化，而非初始化列表出现的顺序；

<br>


>关于const： <br>
>> 1.非const的成员变量既可以调用const类型的成员函数，也可以调用非const类型的成员函数； <br>
>> 2.const类型的成员变量只能调用const类型的成员函数； <br>
>> 3.非const类型的成员函数内既可以调用非const类型的成员函数，又可以调用const类型的成员函数； <br>
>> 4.const类型的成员函数只能调用const类型的成员函数； <br>

<br>

>关于内联函数inline： <br>
>> 1.以inline修饰的函数叫做内联函数，编译时C++编译器会调用内联函数的地方展开，没有函数压栈的开销， <br>
>> 内联函数提升程序运行的效率。 <br>
>> 2.inline是一种以空间换时间的做法，省去调用函数额开销。所以代码很长或者有循环/递归的的函数不适宜使用内联。 <br>
>> 3.inline对于编译器而言只是一个建议，编译器会自动优化，如果定义为inline的函数体内有循环/递归等等，编译器 <br>
>> 优化时会忽略掉内联。 <br>
>> 4.inline必须函数定义放在一起，才能成为内联函数，仅将inline放在声明前是不起不作用的。 <br>
>> 5.定义在类内的成员函数默认定义为内联函数。 <br>

<br>

>关于友元friend <br>
>> 1.在C++中友元函数允许在类外访问该类中的任何成员，就象成员函数一样，友元函数用关键字friend说明。 <br>
>> 2.友元函数不是类的成员函数； <br>
>> 3.友元函数可以通过对象访问所有成员，私有和保护成员也一样。 <br>
>> 4.整个类可以是另一个类的友元。友元类的每个成员函数都是另一个类的友元函数，都可访问另一个类中 <br>
>> 的保护或私有数据成员； <br>
>> 5.友元一定程度上破坏了C++的封装，友元不宜多用，在恰当的地方使用友元。 <br>

<br>

>关于输入输出重载成友元函数 <br>
>> 1.friend ostream & operator<< ( ostream& out , const Date& d ); <br>
>> 2.friend istream & operator>> ( istream& in , Date& d); <br>

<br>

>关于static <br>
>> 1.类里面static修饰的成员，成为静态类成员,类的静态成员是该类型的所有对象对象所共享； <br>

![image](http://hbimg.b0.upaiyun.com/d23133283988b82094ceb9bcafe2d32f88b9054146d0-s7zAg1_fw658)

>> 2.静态成员变量必须在类外初始化，因为它属于该类，不属于某个对象； <br>
>> 3.注意静态成员函数没有隐含this指针参数，所以可以使用类型::作用域访问符直接调用静态成员函数。 <br>
>> 4.静态成员函数可以调用静态成员函数，但是不能调用非静态成员函数； <br>
>> 5.非静态成员函数可以调用静态成员函数； <br>
>> 6.非静态成员函数可以访问静态成员变量；但是静态成员函数无法访问非静态成员变量，没有this指针； <br>
>> 7.非静态成员函数是以对象驱动型的； <br>

<br>

>C++建议以const/枚举/内联去替代宏，为什么？ <br>
>>宏的优点：
>>> 1.增强代码的复用性； <br>
>>> 2.提高性能； <br>


>>宏的缺点：
>>> 1.不方便调试宏。（因为预编译阶段进行了替换）; <br>
>>> 2.导致代码可读性差，可维护性差，容易误用； <br>
>>> 3.没有类型安全的检查； <br>

<br>
<br>









