## 如果你想在Activity中启动一个新的Activity，并将新的Activity中的数据返回，就需要用到startActivityForResult()和onActivityResult()方法了，其实这两个方法在Fragment之间传递数据也同样适用。      
### startActivityForResult(Intent intent,int requestCode)     
* 第一个参数：可以使用putExtra(a,b)方法将各种数据类型的数据存起来   
* 第二个参数：如果该参数大于零，requestCode就会归还到onActivityResult()方法中，用来确定返回的数据是哪个Activity需要的，用来标识目标Activity     
### onActivityResult(int requestCode,int result,Intent data)    
* 第一个参数：用来与startActivityForResult()方法中的参数进行比对，来确认目标Activity，    
* 第二个参数：
