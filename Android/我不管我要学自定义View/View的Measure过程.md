# View的Measure     

测量view的大小使用onMeasure函数，当我们重写这个函数的时候，会有两个参数：    

```java
@Override 
protected void onMeasure(int widthMeasureSpec,int heightMeasureSpec) {
    int width = MeasureSpec.getSize(widthMeasureSpec); //获取宽度的确切值
    int widthMode = MeasureSpec.getMode(widthMeasureSpec);//获取宽度的测量模式
    
    int height = MeasureSpec.getSize(heightMeasureSpec);//获取高度的确切值  
    int heightMode = MeasureSpec.getMode(heightMeasureSpec);//获取高度的测量模式    
}  
```    

这两个参数就是`widthMeasureSpec`和`heightMeasureSpec`，但他们其实并不是实际的宽高，是宽度和高度与它们对应的测量模式组合起来的一个值。      

## 测量模式    

| 模式     | 二进制数值  | 含义   |
|----------|----------|-------|
| UNSPECIFIED|00|默认值，父控件没有给子view任何限制，子view可以设置为任意大小|
|EXACTLY|01|表示父控已经确切的指定了子view的大小 |
|AT_MOST|10|表示子view具体大小没有限制，但是有上限，上限一般为父控件大小|   


* 注意：    

如果对view的宽高进行了修改，调用super.onMeasure(widthMeasureSpec,heightMeasureSpec)方法不起作用，需要调用setMeasureDimension(widthSize,heightSize)这个函数保存修改。     

## onSizeChanged确定view大小    

这个函数在view大小发生改变时调用    

因为view的大小不仅由view本身控制，还受父view的影响，使用onMeasure()后，只是测量除了view本身的属性大小，但最后确定view的大小时，就需要考虑到父控件的影响，使用系统提供的onSizeChanged回调函数。    

```java
@Override
protected void onSizeChanged(int w,int h,int oldw,int oldh) {
    super.onSizeChanged(w,h,oldw,oldh);
}
```    

我们只需要关注w和h这两个参数，它们就是view最终的大小。     


