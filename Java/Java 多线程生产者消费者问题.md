## 多线程生产者消费者问题    

我们同时有多个线程去生产商品,同时有多个线程去消费商品,会有出现线程安全问题的隐患   

下面先来看看只有一个生产者线程和一个消费者线程的情况     

* 两个线程       

    ```java
    class Commodity {

        private String name;
        //商品编号
        private int count = 1;
        //商品是否被生产的标志
        private boolean flag = false;

        /**
        * 生产者生产商品
        *
        * @param name
        */
        public synchronized void set(String name) {
            if (flag) {
                try {
                    this.wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            //相当于生产过程，每产生一个商品，其编号加1
            this.name = name + "...." + count++;
            System.out.println(Thread.currentThread().getName() + "...生产者......" + this.name);
            //给商品标志设置为true，表示以生产，此时消费者线程可以执行
            flag = true;
            //唤醒消费者进程
            this.notify();
        }

        public synchronized void out() {
            //如果商品标志为false，表示此时无商品，消费者线程应该等待
            if (!flag) {
                try {
                    this.wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            //相当于消费过程，打印消费该商品的线程信息
            System.out.println(Thread.currentThread().getName() + "...消费者..." + this.name);
            //在消费商品过后，需要将商品标志位设置为false
            flag = false;
            //同时消费者线程应该等待，在等待前应该将生产者线程唤醒
            this.notify();
        }
    }

    class Producer implements Runnable {

        private Commodity commodity;

        public Producer(Commodity commodity) {
            this.commodity = commodity;
        }

        @Override
        public void run() {
            while (true) {
                commodity.set("商品");
            }
        }
    }

    class Consumer implements Runnable {

        private Commodity commodity;

        public Consumer(Commodity commodity) {
            this.commodity = commodity;
        }

        @Override
        public void run() {
            while (true) {
                commodity.out();
            }
        }
    }

    public class ProducerAndConsumer {

        public static void main(String[] args) {
            Commodity commodity = new Commodity();
            Producer producer = new Producer(commodity);
            Consumer consumer = new Consumer(commodity);

            Thread producerT = new Thread(producer);
            Thread consumerT = new Thread(consumer);
            producerT.start();
            consumerT.start();
        }
    }
    ```  

    输出:   

    ```
    ...
    Thread-0...生产者......商品....24443
    Thread-1...消费者...商品....24443
    Thread-0...生产者......商品....24444
    Thread-1...消费者...商品....24444
    Thread-0...生产者......商品....24445
    Thread-1...消费者...商品....24445
    ...
    ```   

    情况正常,就是生产者线程生产一个商品,然后消费者线程消费一个商品       

* 多个线程   

    下面看一下生产者和消费者同时有多个线程的情况     

    ```java
    public class ProducerAndConsumer {

        public static void main(String[] args) {
            Commodity commodity = new Commodity();
            Producer producer = new Producer(commodity);
            Consumer consumer = new Consumer(commodity);

            //生产者和消费者都有多个线程
            Thread producerT = new Thread(producer);
            Thread producerT1 = new Thread(producer);
            Thread consumerT = new Thread(consumer);
            Thread consumerT1 = new Thread(consumer);
            producerT.start();
            producerT1.start();
            consumerT.start();
            consumerT1.start();

        }
    }
    ```   

    输出:    

    ```
    ...
    Thread-0...生产者......商品....59011
    Thread-1...生产者......商品....59012
    Thread-2...消费者...商品....59012
    Thread-0...生产者......商品....59013
    Thread-1...生产者......商品....59014
    Thread-2...消费者...商品....59014
    ...
    ```  

    这里出现了生产了两个商品，但是只有一个商品被消费的情况   

    





