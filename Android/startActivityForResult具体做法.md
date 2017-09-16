### Android页面跳转时往往也会进行数据的传递，也会有数据返回的情况，比如调用摄像机拍照后，将拍摄的照片数据返回当前页面，这时就要用到```startActivityForResult()```方法了.      


#### 跳转                  

* MainActivity
```java
 private static final int SEND_REQUEST = 1;

 capture_take_photo_btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
              Intent intent = new Intent(MainActivity.this, OtherActivity.class);
              startActivityForResult(intent, SEND_REQUEST);
            }
        });
```      

需要返回数据或结果时，使用```startActivityForResult(Intent intent,int requestCode)```进行跳转，其中requestCode的值是自定义的，用于识别跳转的目标Activity，就像上面代码中定义的常量```SEND_REQUEST```。          

#### 处理是否返回数据    

* OtherActivity        
```java
((Button) findViewById(R.id.send)).setOnClickListener( new Button.OnClickListener() {    
    public void onClick(View v) {    
      //这里的RESULT_OK是系统空间里的常量，表示正确返回，当然表示无法返回的常量为RESULT_CANCELED，两者直接使用即可
        OtherActivity.this.setResult(RESULT_OK);    
        OtherActivity.this.finish();    
    }    
});
```

跳转的目标Activity需要做的就是返回数据或结果，```setResult(int resultCode)```表示只返回结果不带数据，```setResult(int resultCode, Intent data)```表示数据和结果都返回。      

但是，在```setResult()```后，要finish掉当前Activity，否则无法回到跳转前的数据，也就无法进行数据接受操作了。          

#### 接受返回的数据        

* MainActivity      

```java
private static final int SEND_REQUEST = 1;

capture_take_photo_btn.setOnClickListener(new View.OnClickListener() {
           @Override
           public void onClick(View v) {
             Intent intent = new Intent(MainActivity.this, OtherActivity.class);
             startActivityForResult(intent, SEND_REQUEST);
           }
       });       


 @Override    
 protected void onActivityResult(int requestCode, int resultCode, Intent data) {    
      if (requestCode == SEND_REQUEST) {
          if (resultCode == RESULT_OK) {
              Toast.makeText(this,"Send REQUSET_OK",Toast.LENGTH_SHORT).show();
          }
      }
 }     
```       
接收函数就是```onActivityResult(int requestCode, int resultCode, Intent data)```,这里的requestCode就是startActivityForResult里的requestCode,resultCode就是setResult里的resultCode,返回的数据在data中。           


#### 这种传递数据并返回数据的方式在Fragment向Activity跳转时同样适用。    
