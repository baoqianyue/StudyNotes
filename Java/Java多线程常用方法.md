## currentThread方法   

该方法可以返回代码段正在被哪个线程调用的信息     

例子：  

```java
package basic;

public class CountOperate extends Thread {

    public CountOperate(){
        System.out.println("CountOperate---begin");
        System.out.println("Thread.currentThread---" + Thread.currentThread());
        //获取当前线程的名称
        System.out.println("this.getName()---" + this.getName());
        System.out.println("CountOperate---end");
    }

    @Override
    public void run() {
        System.out.println("run---begin");
        System.out.println("Thread.currentThread---" + Thread.currentThread());
        System.out.println("this.getName()---" + this.getName());
        System.out.println("run---end");
    }
}

package basic;

public class ThreadMain {

    public static void main(String[] args) {
        CountOperate countOperate = new CountOperate();
        Thread thread = new Thread(countOperate);
        thread.setName("t1");
        thread.start();
    }
}

```  

输出：   

```
CountOperate---begin
Thread.currentThreadName---main
this.getName()---Thread-0
CountOperate---end
run---begin
Thread.currentThreadName---t1
this.getName()---Thread-0
run---end
```  

这里有点特殊情况，就是这里`countOperate`和`thread`是两个不同的线程对象，它们之间唯一的关系就是将countOperate传递给了thread对象，这个仅仅是为了能够让thread去访问到countOperate中的`run`方法