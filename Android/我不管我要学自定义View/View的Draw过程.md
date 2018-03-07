# View的Draw过程     

它的任务就是将View绘制到屏幕上，View的绘制过程遵循下面几步：    

* 绘制背景background.draw(canvas)    
* 绘制自己(onDraw)    
* 绘制children(dispatchDraw)     
* 绘制装饰(onDrawScrollBars)      

View绘制过程的传递是通过dispatchDraw方法实现的，dispatchDraw会遍历调用所有子元素的draw方法，这样draw事件就一层层的传递下去了。     

## setWillNotDraw     

View有一个特殊的方法`setWillNotDraw()`     
如果一个View不需要绘制任何内容，那就设置这个标记为true，这样系统就会进行相应的优化，默认情况下，View没有启用这个优化标记位，但是ViewGroup默认会启用这个标记位，这个标记位的实际意义是：当我们的自定义控件继承于ViewGroup并且本身不具备绘制功能时，就可以开启这个标记位从而便于系统进行后续的优化，当然，当明确知道一个ViewGroup需要通过onDraw来绘制内容时，我们需要显示的关闭`WILL_NOT_DRAW`这个标记位。      

