# 使用Intent传递对象   
Intent的用途很多，可以用来启动Activity，Service或者发送广播，也可以在跳转的过程中传递信息    
* 传递普通信息   
 * 在MainActivity中创建一个Intent   

 ```java
 Intent intent = new Intent(MainActivity.this,OtherActivity.class);
 intent.putExtra("String_data","Barack");
 intent.putExtra("int_data",100);
 startActivity(intent);
 ```
  * 在OtherActivity中接受传过来的信息   

  ```java
  getIntent().getStringExtra("String_data");
  getIntent().getIntExtra("int_data",0);

  ```
* 传递对象     

 *  使用Serializable   
  Serializable就是序列化的意思，可以将一个对象转化为可以存储的的形式，这样我们就可以将一个对象像普通信息一样进行传递，实现方式很简单，只要让一个类实现Serializable这个接口就行了。
  举个例子：   
  先创建一个实体类  

  ```java   

  public class Person implements Serializable{
    private String name;
    private int age;
    public String getName(){
      return name;
    }
    public void setName(String name){
      this.name = name;
    }
    public int getAge(){
      return age;
    }
    public void setAge(int age){
      this.age = age;
    }

  }
  ```    

  这样每个Person对象都是可序列化的了   
  接下来实现在Activity之间传递对象   
  ```java  
  Person person = new Person();
  person.setName("BarackBao");
  person.setAge(19);
  Intent intent = new Intent(MainActivity.this,OtherActivity.class);
  intent.putExtra("person_data",person);
  startActivity(intent);
  ```    
  在OtherActivity中获取到所传递的对象     
  ``` java
  Person person1 = getIntent().getSerializableExtra("person_data");
  ```
   * 使用Parcelable方式   
   相比于前一种将整个对象序列化的方式，Parcelable是将一个对象进行分离，将信息都分解为普通信息然后进行传递
   我们需要让实体类实现Parcelable接口，然后重写describeContent()和writeToParcel()两个方法来将对象信息分解  
   ``` java
   public class Person implements Parcelable {
    private String name;
    private int age;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeString(name);//分解出String类型
        dest.writeInt(age);//分解出int类型  
    }

   ```   
   然后我们进行对对象进行反序列化的操作

   我们先要在Person类中设置一个名为CREATOR的常量。  
   实现Parcelable.Creator这个接口，将泛型指定为Person，然后重写createFromParcel()和newArray()两个方法，在createFromParcel()方法中使用readX()方法将刚刚分解的信息读取，然后将数据组装成对象并返回。    
   在newArray()方法中，只要new一个数组，并用方法中穿入的size参数做为数组大小就可以了。    
   ```java
   public static final Parcelable.Creator<Person> CREATOR = new
           Creator<Person>() {
               @Override
               public Person createFromParcel(Parcel source) {
                   Person person = new Person();
                   person.name = source.readString();
                   person.age = source.readInt();
                   return person;
               }

               @Override
               public Person[] newArray(int size) {
                   return new Person[size];
               }
           };
   ```
**在Activity中传递对象的方法和serializable中的一样**，在OtherActivity中接收时有所不同     
```java
Person person = (Person)getIntent().getParcelableExtra("person_data");
```    


相比之下，第二种方式更为复杂一点，但第一种方式将整个对象一并序列化，运行效率比较低。    
