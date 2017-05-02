# 设计按钮样式       
我们可以在布局文件xml中给每一个button通过```style:""```语句引用到style中预先设计好的样式来更改button的样式，但是通常一个应用中有很多Button，想要快速更改所有button的样式，就要使用主题。        
## 创建按钮样式      
在res/values/style.xml文件中创建一个ButtonStyle            

```xml
<resources>
    <!-- Base application theme. -->
    <style name="AppTheme" parent="Theme.AppCompat">
        <!-- Customize your theme here. -->
        <item name="colorPrimary">@color/red</item>
        <item name="colorPrimaryDark">@color/dark_red</item>
        <item name="colorAccent">@color/gray</item>
    </style>

    <style name="BeatBoxButton" parent="android:style/Widget.Holo.Button">
    </style>

</resources>
```    
这里让新建的BeatBoxButton继承android:style/Widget.Holo.Button，如果不设置父类样式，所有的button都会变的不像个按钮。           
新建好BeatBoxButton后，还要在```Base application theme```中覆盖buttonStyle属性让它指向刚刚新建的BeatBoxButton,这样就可以引用到我们自己设置按钮风格了         

```xml
<!-- Base application theme. -->
   <style name="AppTheme" parent="Theme.AppCompat">
       <!-- Customize your theme here. -->
       <item name="colorPrimary">@color/red</item>
       <item name="colorPrimaryDark">@color/dark_red</item>
       <item name="colorAccent">@color/gray</item>

       <item name="android:buttonStyle">@style/BeatBoxButton</item>
   </style>
```

## 优化按钮表现，使用XML drawable      
Android在MaterailDesign中对按钮按下时有沉浸效果，我们可以自己定制按下效果       

使用ShapeDrawable，可以将button变成圆形     


* 创建圆形drawable    
在res/drawable目录下创建一个xml文件用来定义按钮未选中时的样式       


```xml
<shape xmlns:android="http://schemas.android.com/apk/res/android"   android:shape="oval">  

  <solid     android:color="@color/dark_blue"/>

</shape>   
```       

这里我们定义了一个背景为深蓝色的圆形，当然可以通过```android:shape=""```属性设置其他形状     

效果是这样的     

![](http://i4.buimg.com/567571/460cdbc776176a6f.png)   

* 创建按钮按下时的样式       
在res/drawable目录下创建一个xml文件用来定义按钮选中时的样式        

```xml
<shape xmlns:android="http://schemas.android.com/apk/res/android"
       android:shape="oval">

    <solid
        android:color="@color/red"/>

</shape>
```     

这里定义了一个背景为红色的圆形按钮       

* 创建一个state list drawable        
现在要在按钮按下时使用这个新建的shape drawable,就根据按钮的状态,在state list drawable中切换指向不同的drawable       

```xml
<selector xmlns:android="http://schemas.android.com/apk/res/android">

    <item android:drawable="@drawable/button_beat_box_pressed"
          android:state_pressed="true"/>
    <item android:drawable="@drawable/button_beat_box_normal"/>
</selector>
```     


* 在Base.application.Theme中修改按钮样式       

在style.xml中     

```xml
style name="BeatBoxButton" parent="android:style/Widget.Holo.Button">
        <item name="android:background">@drawable/button_beat_box</item>
    </style>
```     

效果如图    

![](http://i4.buimg.com/567571/78919cb7e8ff6dc8.png)   
