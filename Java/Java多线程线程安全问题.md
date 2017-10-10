## 线程的安全性      

上一篇笔记写的那个例子表面上很正确，其实上有线程安全隐患，先来制造一点错误出来。      

为了方便展示输出，这里将课的总数改为20节。      

```java
public class Elective implements Runnable {

    private int classes = 20;

    @Override
    public void run() {
        while (true) {
            if (classes > 0) {
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                System.out.println(Thread.currentThread().getName() + " 课余量" + classes--);
            }
        }
    }
}

public class Main {

    public static void main(String[] args) {
        Elective elective = new Elective();
        Thread thread1 = new Thread(elective);
        Thread thread2 = new Thread(elective);
        Thread thread3 = new Thread(elective);
        thread1.start();
        thread2.start();
        thread3.start();
    }
}
```      

输出：     

```
Thread-0 课余量12
Thread-2 课余量11
Thread-0 课余量10
Thread-1 课余量10
Thread-2 课余量9
Thread-1 课余量8
Thread-0 课余量8
Thread-2 课余量7
Thread-1 课余量6
Thread-0 课余量5
Thread-2 课余量4
Thread-0 课余量3
Thread-1 课余量2
Thread-2 课余量1
Thread-0 课余量0
Thread-1 课余量-1
```      

我只是让线程休眠了1s就出现了两个线程课余量相同的情况，更严重的是居然出现了-1节课......        

这就是线程的安全隐患         

* 线程不安全出现的原因：         

当多个线程操作到一个共享数据时，一个线程对该数据的操作还没有完成，另一个线程就也开始操作该数据了，这时就会导致共享数据发生错误。           

* 解决办法：     

对于操作到共享数据的代码，我们只能让一个线程执行结束，而且该线程执行的时候其他线程不能介入操作该数据，Java对多线程的安全问题提供了专业的解决方案，那就是同步机制，有两种方式，一种是使用同步代码块，一种就是同步函数。         

## 使用同步代码块解决该线程安全问题       

* 同步代码块     

```Java
synchronized (Object){
    //需要同步的代码
}
```    



```Java
public class Elective implements Runnable {

    private int classes = 20;

    Object object = new Object();

    @Override
    public void run() {
        while (true) {
            synchronized (object) {
                if (classes > 0) {
                    try {
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    System.out.println(Thread.currentThread().getName() + " 课余量" + classes--);
                }
            }

        }
    }
}

public class Main {

    public static void main(String[] args) {
        Elective elective = new Elective();
        Thread thread1 = new Thread(elective);
        Thread thread2 = new Thread(elective);
        Thread thread3 = new Thread(elective);
        thread1.start();
        thread2.start();
        thread3.start();
    }
}

```       

输出：    

```
Thread-0 课余量20
Thread-0 课余量19
Thread-0 课余量18
Thread-0 课余量17
Thread-0 课余量16
Thread-2 课余量15
Thread-2 课余量14
Thread-2 课余量13
Thread-2 课余量12
Thread-2 课余量11
Thread-2 课余量10
Thread-2 课余量9
Thread-2 课余量8
Thread-2 课余量7
Thread-2 课余量6
Thread-2 课余量5
Thread-2 课余量4
Thread-2 课余量3
Thread-2 课余量2
Thread-2 课余量1
```   

选课正常。           

* 为什么可以解决问题     

同步代码块使用的时候用到了一个对象，这个对象就如同一把锁，只有持有锁的线程才可以执行任务，没有获取到锁的线程即使获取了cpu的执行权，也不能执行代码。       

* 线程同步的条件      

 * 必须要有两个或两个以上的线程，不然同步也就没什么意义了。      

 * 必须是多个线程使用同一把锁。     
 假如这样写：     

 ```Java
 public class Elective implements Runnable {

    private int classes = 20;

    @Override
    public void run() {
        while (true) {
            synchronized (new Object()) {
                if (classes > 0) {
                    try {
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    System.out.println(Thread.currentThread().getName() + " 课余量" + classes--);
                }
            }

        }
    }
}

 ```     
 结果就是错误的，所以这把锁必须固定，不然就是每个线程一把锁，同步就没了意义。            


* 同步代码块的弊端         
这样的同步会使多个线程都要判断锁，较为耗费资源。        


## 使用同步函数解决线程安全问题。        
