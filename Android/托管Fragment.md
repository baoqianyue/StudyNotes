## 为什么要使用Fragment    
有的时候因为跳转界面很复杂，或者用户界面需要在运行时进行重新组合，Activity本身并不具有这样的灵活性，我们可以使用Activity托管Fragment的方法来实现这种UI效果     
## 托管方式    
* 在Activity视图中可用FrameLayout预留出Fragment视图插入的位置，如果有多个fragment要插入，activity可以提供多个位置     
* 具体的两种托管方式   
  * 在activity*布局*中添加fragment
  * 在activity*代码*中添加fragment      
  常用第二种方式，足够灵活，也是唯一可以在运行时控制fragment的方式，我们可以自行决定何时添加fragment以及随后可以完成何种特殊任务，也可以移除  fragment,用其他fragment代替当前fragment,然后重新添加已移除的fragment        


## 具体例子
* 1 先定义一个Fragment容器视图(FrameLayout)    
activity_crime.xml
```xml
<FrameLayout
    xmlns:android="http://schemas.android.com/apk/res/android"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:id="@+id/fragment_container">
</FrameLayout>
```    
* 2 定义目标Fragment的布局   
fragment_crime.xml    

```xml
<LinearLayout xmlns:android="http://schemas.android.com/apk/res/android"
              android:layout_width="match_parent"
              android:layout_height="match_parent"
              android:orientation="vertical">

    <EditText
        android:id="@+id/crime_title"
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:hint="@string/crime_title_hint"/>

</LinearLayout>
```   
* 3 创建一个具体的Fragment类从而将布局中的控件读取出来    
  * 首先让该类继承自Fragment   
  * 实现fragment生命周期方法```onCreate(Bundle)```,```onCreateView(...)```   
  这里分析一下后者   
  ```java
  public void onCreateView(LayoutInflater inflater,ViewGroup container,
  Bundle savedInstanceState){
    View v = inflater.inflate(R.layout.fragment_crime,container,false);
    return v;
  }
  ```    
  fragment的布局是直接通过inflater.inflate()方法生成的，第一个参数是资源ID，第二个参数是视图的父视图，我们通常需要父视图来正确配置组件，第三个参数告知布局生成器是否将生成的视图添加给父视图，我们传入false，**因为我们将以activity代码的方式添加视图**   

  * 加载相关组件和一些具体事务的逻辑处理    
  ```java
  mTitleField = (EditText) v.findViewById(R.id.crime_title);
        mTitleField.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start,
                                          int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start,
                                      int before, int count) {
                mCrime.setTitle(s.toString());
            }

            @Override
            public void afterTextChanged(Editable s) {

            }
        });
  ```   

* 4 使用FragmentManager将fragment添加到activity中   
  * 获取FragmentManager   
  ```java
  public class CrimeActivity extends FragmentActivity {
    protected void onCreate(Bundle savedInstanceState) {
      super.onCreate(savedInstanceState);
      setContentView(R.layout.activity_crime);

      FragmentManager fm = getSupportFragmentManager();
    }
  }
  ```      
  * 使用fragment事务将fragment队列中的fragment添加      
 ```java
 FragmentManager fm = getSupportFragmentManager();
 //将fragment队列引进来  
 Fragment fragment = fm.findFragmentById(R.id.fragment_container);
 if (fragment == null) {
   fragment = new Fragment();
   fm.beginTransaction()
   .add(R.id.fragment_crime,fragment)
   .commit();
 }
 ```
 这里```beginTransaction()```方法创建并返回FragmentTransaction实例，然后使用```add()```方法添加事务，在该方法中，我们使用容器资源ID来确定布局，这样做的目的是：   

  * 告诉FragmentManager，fragment视图应该出现在activity中的什么位置(根据FrameLayout的具体位置)   
  * 告诉FragmentManager队列中fragment的唯一标识符    

这里我们还有一点判断逻辑，第一次将fragment队列使用findFragmentById()方法引进来的时候，先判断队列是否为空，如果为空就新创建一个fragment,再添加并提交，如果队列不为空，就将原来的fragment提交。

## 要善于使用fragment    
AUF(Always Use Fragment)原则     
