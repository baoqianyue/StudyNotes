## Java 异常处理     

### 三种异常类型   

* Checked Exception (检查性异常)     

    也叫非运行时异常，java编译器会对此类异常强制程序员去处理，这种异常往往是那种程序员无法预见的，比如要打开一个不存在的文件(IOException)或者对数据库的连接和访问(SQLException)，此类异常必须进行异常的抛出处理，否则无法通过编译       

* unChecked Exception (Runtime Exception) (运行时异常)     

    称为运行时异常，此类异常往往是被程序员所忽略的，而且也能够顺利通过编译，比如使用空指针(NullPointerException)，访问数组时下标越界(IndexOutOfBoundsException)，或者数学运算时的逻辑错误(IllegalArgumentException)。    


### 如何处理异常   

* 对代码块使用`try catch`进行异常捕获处理     

* 在有可能出现异常的代码的方法处使用`throws`关键字将异常抛出，告知此方法的调用者要注意处理异常，此时会有两种情况：    

    * Checked Exception    

        如果该方法抛出的是检查性异常，则调用方必须使用`try catch`进行处理或者继续向上抛出该异常     

    * Runtime Exception    

        如果该方法抛出的异常是运行时异常，则调用方可以有选择的进行处理     

* 在有可能出现异常的代码块使用`throw`手动将异常抛出，后续处理的情况与上一种情况类似      

    eg:  
    ```java
     public static void main(String[] args) {

        try {
            int[] a = new int[]{1, 2, 3, 4};
            System.out.println(getNumByIndex(a, -1));
        } catch (Exception e) {
            System.out.println(e.getMessage());
            e.printStackTrace();
        }

    }

    public static int getNumByIndex(int[] array, int index) {
        if (index < 0 || index > array.length) {
            throw new ArrayIndexOutOfBoundsException("数组下标越界");
        }
        return array[index];
    }
    ```

* 如果一个异常最终抛给了main方法，就相当于交给jvm处理，jvm会将异常信息打印出来        


### try,catch,finally    

* 当有多个catch块时，会按照catch块的顺序进行异常处理，一旦异常类型被一个catch块所匹配，则不会与之后的catch块进行匹配     

* 在使用`try catch finally`进行异常处理时，不要在`finally`块中使用return，因为`finally`块中的代码是一定会执行的，这样会覆盖之前return返回的内容      

    ```java
     public static void main(String[] args) {
        System.out.println(new Main().openFile("C:/test.txt"));
    }

    public String openFile(String filename) {
        try {
            FileInputStream inputStream = new FileInputStream(filename);
            int length = inputStream.read();
            return "try";

        } catch (FileNotFoundException e) {
            System.out.println("file not exist");
            e.printStackTrace();
            return "catch1";
        } catch (IOException e) {
            System.out.println("io exception");
            e.printStackTrace();
            return "catch2";
        } finally {
            System.out.println("finally");
//            return "finally";
        }

    }
    ```   


### 自定义声明异常    

* 所有异常都必须是Throwable的子类    

* 如果希望定义一个Checked Exception，则需要继承Exception     

* 如果希望定义一个Runtime Exception，则需要继承RuntimeException     

eg:   

```java

```







