## 进程和多线程      
一个应用程序可能会由一个或多个进程组成，而进程又是由很多线程组成的，一个进程至少会有一个线程，即主线程，JVMJava虚拟机就是一个多线程进程，它还有负责垃圾回收的线程等等，其中至少有一个线程负责java程序的启动和执行，而且这个线程的代码处于main()方法中，这个线程就是主线程。                

## 使用Thread类实现一个线程    

有几个步骤：   

* 1). 继承Thread类   

* 2). 覆盖Thread类的run()方法     

* 3). 调用线程的start()方法，该方法才是启动线程的入口。      

```java
public class MyThread extends Thread{
    @Override
    public void run(){
        System.out.println("This is a thread");
    }
}

public class main{
    public static void main(String[] args) {
        MyThread thread = new MyThread();
        thread.start();
    }
}
```      

上面就是一个最简单的线程定义和调用的过程。     
