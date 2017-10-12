## 同步函数的锁是this       

同步代码块的锁就是定义的那个对象，那同步函数的锁也应该是个对象，但是我们并没有定义，下面还是写之前那个选课的程序来说明。     

```java
public class Elective implements Runnable {

    private int classes = 20;

    @Override
    public synchronized void run() {
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
```   

输出：    

```
Thread-0 课余量12
Thread-0 课余量11
Thread-0 课余量10
Thread-0 课余量9
Thread-0 课余量8
Thread-0 课余量7
Thread-0 课余量6
Thread-0 课余量5
Thread-0 课余量4
Thread-0 课余量3
Thread-0 课余量2
Thread-0 课余量1
```      

又有一个严重的问题，只有线程0在工作。          

原因是就是没有考虑到前面提到的那三个条件，我们真正需要同步运行的代码就只有选课的行为，而不是整个循环，这样其他线程都进入不了循环，就无法执行了。        

所以使用封装同步函数的方法修改一下：        

```java
public class Elective implements Runnable {

    private int classes = 20;

    @Override
    public void run() {
        while (true) {
            work();
        }
    }

    private synchronized void work() {
        if (classes > 0) {
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println(Thread.currentThread().getName() + " 课余量" + classes--);
        }
    }
}

```     

输出：    

```
Thread-1 课余量14
Thread-1 课余量13
Thread-2 课余量12
Thread-2 课余量11
Thread-2 课余量10
Thread-2 课余量9
Thread-2 课余量8
Thread-2 课余量7
Thread-2 课余量6
Thread-0 课余量5
Thread-0 课余量4
Thread-0 课余量3
Thread-0 课余量2
Thread-0 课余量1
```       

这样就正确了。       

* 同步函数的锁       

函数都是被对象调用，那函数就会有一个所属对象的引用，就是this，this就是对本类对象的一个引用，所以同步函数的锁就是定义该函数的本类对象，就是this(这里说法有些不妥)，下面来验证一下。        

还是那个选课程序，我们现在只需要两个线程，一个线程在同步代码块中，一个在同步函数中。       

```java
public class Elective implements Runnable {

    private int classes = 20;

    private Object object = new Object();

    public boolean flag = true;

    @Override
    public void run() {
        if (flag) {
            while (true) {
                synchronized (object) {
                    if (classes > 0) {
                        try {
                            Thread.sleep(100);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                        System.out.println(Thread.currentThread() + " 代码块课余量" + classes--);
                    }
                }
            }
        } else {
            while (true) {
                work();
            }
        }
    }

    private synchronized void work() {
        if (classes > 0) {
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println(Thread.currentThread() + " 同步函数课余量" + classes--);
        }
    }
}

public class Main {

    public static void main(String[] args) {
        Elective elective = new Elective();

        Thread thread1 = new Thread(elective);
        Thread thread2 = new Thread(elective);

        thread1.start();
        //为了防止只有第一个线程运行
        try {
            Thread.sleep(100);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        elective.flag = false;

        thread2.start();

    }
}
```     

输出：    

```
Thread[Thread-0,5,main] 代码块课余量10
Thread[Thread-1,5,main] 同步函数课余量9
Thread[Thread-0,5,main] 代码块课余量8
Thread[Thread-1,5,main] 同步函数课余量7
Thread[Thread-0,5,main] 代码块课余量6
Thread[Thread-0,5,main] 代码块课余量5
Thread[Thread-1,5,main] 同步函数课余量5
Thread[Thread-0,5,main] 代码块课余量4
Thread[Thread-1,5,main] 同步函数课余量3
Thread[Thread-0,5,main] 代码块课余量2
Thread[Thread-1,5,main] 同步函数课余量1
Thread[Thread-0,5,main] 代码块课余量0
```      

结果虽然好像是两个线程交替而且是在两个不同的同步代码处交替执行，但是出现了课余量为0的情况，这就是线程不安全的体现，为了验证上面的那个想法，我把同步代码块中的那个对象改为this：      

```java
public class Elective implements Runnable {

    private int classes = 20;

    public boolean flag = true;

    @Override
    public void run() {
        if (flag) {
            while (true) {
                synchronized (this) {
                    if (classes > 0) {
                        try {
                            Thread.sleep(100);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                        System.out.println(Thread.currentThread() + " 代码块课余量" + classes--);
                    }
                }
            }
        } else {
            while (true) {
                work();
            }
        }
    }

    private synchronized void work() {
        if (classes > 0) {
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println(Thread.currentThread() + " 同步函数课余量" + classes--);
        }
    }
}

```       

输出正确，所以可以验证同步函数的锁就是本类对象this。          

## 静态同步函数的锁         

这个问题也应该注意，当我们把同步函数变为静态的，来检测一下静态同步函数的锁是不是还是this：     

```java
private static synchronized void work() {
      if (classes > 0) {
          try {
              Thread.sleep(100);
          } catch (InterruptedException e) {
              e.printStackTrace();
          }
          System.out.println(Thread.currentThread() + " 同步函数课余量" + classes--);
      }
  }
```     

输出：    

```
Thread[Thread-1,5,main] 同步函数课余量10
Thread[Thread-1,5,main] 同步函数课余量9
Thread[Thread-0,5,main] 代码块课余量8
Thread[Thread-0,5,main] 代码块课余量7
Thread[Thread-1,5,main] 同步函数课余量6
Thread[Thread-1,5,main] 同步函数课余量5
Thread[Thread-0,5,main] 代码块课余量4
Thread[Thread-0,5,main] 代码块课余量3
Thread[Thread-1,5,main] 同步函数课余量2
Thread[Thread-0,5,main] 代码块课余量1
Thread[Thread-1,5,main] 同步函数课余量0
```      

可以看到，线程又不安全了，说明静态同步函数的锁发生了改变，其实很好理解，static修饰的成员是跟随着类的加载而加载的，此时的内存中还没有本类对象呢，但是有着类加载产生的该类的字节码文件，```类名.class```，这个就是静态函数的锁。我们把同步代码块的锁也改成这样再试一下：    

```java
public void run() {
       if (flag) {
           while (true) {
               synchronized (Elective.class) {
                   if (classes > 0) {
                       try {
                           Thread.sleep(100);
                       } catch (InterruptedException e) {
                           e.printStackTrace();
                       }
                       System.out.println(Thread.currentThread() + " 代码块课余量" + classes--);
                   }
               }
           }
       } else {
           while (true) {
               work();
           }
       }
   }
```        

输出正确。           


## 死锁的出现     
