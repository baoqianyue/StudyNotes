# 简单工厂模式       
简单工厂模式又叫静态工厂模式，其核心就在这个静态的分类新建实例的方法。         
比如我们的客户需要负责各个模块的程序员，需要擅长各种语言的程序员，这时我们可以使用静态工厂模式。     
## 普通方法      

```Java
public class JavaProgrammer{
  public JavaProgrammer(){
    System.out.println("我是一个Java程序员");
  }
}

public class AndroidProgrammer{
  public AndroidProgrammer(){
    System.out.println("我是一个Android程序员");
  }
}

public class Custom{
  public static void main(String [] args){
    JavaProgrammer java = new JavaProgrammer();
    AndroidProgrammer android = new AndroidProgrammer();
  }
}
```

## 静态工厂实现       
上面的方法虽然也能满足要求，但是耦合度太高，其实客户需要知道一个程序员的能力，但没毕竟要知道他的成长历程，为了降低耦合，我们引入工厂类，将程序员的成长历程和一些客户不必要知道的属性放到工厂里，客户直接通过工厂的创建工厂方法，输入
