### 开发中经常要遇到从一个Activity传递一些信息到另一个Activity或者Fragment中，还有类似的很多情况。

#### 使用Intent    

* (1)单个或少量数据        
直接采用intent携带,以键值对的方式来标记数据           

```java
@Override  
  public void onCreate(Bundle savedInstanceState) {  
      super.onCreate(savedInstanceState);  
      setContentView(R.layout.main);  
      initComponent();  
      button.setOnClickListener(new View.OnClickListener() {  
          @Override  
          public void onClick(View v) {  
              Intent intent = new Intent(IntentDemo.this, Other.class);  
              // 在Intent中传递数据  
              intent.putExtra("name", "BarackBao");  
              intent.putExtra("age", 19);    
              // 启动Intent  
              startActivity(intent);  
          }  
      });  
  }  
```   


在另一个Activity获取数据         

```java
@Override  
   protected void onCreate(Bundle savedInstanceState) {  
       // TODO Auto-generated method stub  
       super.onCreate(savedInstanceState);  
       setContentView(R.layout.other);  
       Intent intent = getIntent();  
       int age = intent.getIntExtra("age", 0);  
       String name = intent.getStringExtra("name");  

       textView.setText("My age is " + age + "\n" + "My name is " + name + "\n");  
   }  
```      

* (2)数据有些复杂或数据之间有联系             
使用容器Bundle,存储数据然后进行传递,同样使用键值对标记数据            

```java
@Override
protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);
    findViewById(R.id.button).setOnClickListener(new View.OnClickListener() {
        @Override
        public void onClick(View v) {
            Intent i = new Intent(MainActivity.this,OtherActivity.class);
            Bundle bundle = new Bundle();
            bundle.putString("name","BarackBao");
            bundle.putInt("age",19);
            i.putExtra("bundle",bundle);
            startActivity(i);
        }
    });
}
```         

在另一个Activity中获取数据         

```java
@Override
protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);
    findViewById(R.id.button).setOnClickListener(new View.OnClickListener() {
        @Override
        public void onClick(View v) {
            Bundle bundle = getIntent.getBundleExtra("bundle");
            String name = bundle.getString("name");
            String age = bundle.getInt("age");
        }
    });
}
```
