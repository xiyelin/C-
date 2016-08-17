## 常见的零碎知识

----------------------------------

### 为什么虚函数必须是类的成员函数？

	虚函数诞生的目的就是为了实现多态，在类外定义虚函数毫无实际用处。
	

### 为什么类的静态成员函数不能为虚函数？

	如果定义为虚函数，那么它就是动态绑定的，也就是在派生类中可以被覆盖的，这与静态成员函数的定义
	（在内存中只有一份拷贝；通过类名或对象引用访问静态成员）本身就是相矛盾的。
	

### 为什么构造函数不能为虚函数？

	因为如果构造函数为虚函数的话，它将在执行期间被构造，而执行期则需要对象已经建立，构造函数所完成的工作
	就是为了建立合适的对象，因此在没有构建好的对象上不可能执行多态（虚函数的目的就在于实现多态性）的工作。
	在继承体系中，构造的顺序就是从基类到派生类，其目的就在于确保对象能够成功地构建。构造函数同时承担着虚
	函数表的建立，如果它本身都是虚函数的话，如何确保 vtbl 的构建成功呢？
	
	注意：当基类的构造函数内部有虚函数时，会出现什么情况呢？结果是在构造函数中，虚函数机制不起作用了，调
	用虚函数如同调用一般的成员函数一样。当基类的析构函数内部有虚函数时，又如何工作呢？与构造函数相同，只
	有“局部”的版本被调用。但是，行为相同，原因是不一样的。构造函数只能调用“局部”版本，是因为调用时还没有
	派生类版本的信息。析构函数则是因为派生类版本的信息已经不可靠了。我们知道，析构函数的调用顺序与构造函
	数相反，是从派生类的析构函数到基类的析构函数。当某个类的析构函数被调用时，其派生类的析构函数已经被调
	用了，相应的数据也已被丢失，如果再调用虚函数的派生类的版本，就相当于对一些不可靠的数据进行操作，这是
	非常危险的。因此，在析构函数中，虚函数机制也是不起作用的。









