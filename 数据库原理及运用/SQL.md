# SQL      
SQL是一种国际标准    

## SQL的特点     

* 综合统一   
    SQL集数据定义语言(DDL)，数据操纵语言(DML)和数据控制语言于一体
* 高度非过程化   
    就是只需告诉数据库管理系统“做什么”，而无须指明“怎么做”，因此在编写sql语句时，无须知道数据的具体存储路径，这些操作都由数据库管理系统完成。    
* 面向集合的操作方式      
* 以同一种语法结构提供多种使用方式    
* 语言简洁，易学易用    


## SQL的基本概念    

支持SQL的关系数据库管理系统同时支持关系数据库的三级模式     

其中外模式包括若干视图和部分基本表，模式包括若干基本表，内模式包括若干存储文件。       

![sql](../image/sql1.png)       


## 数据定义    

关系数据库系统支持三级模式，其中模式，外模式，内模式的基本对象有模式、关系、视图和索引，所以sql首先有对这些对象操作的语句   

一个关系数据库管理系统的实例(instance)中可以建立多个数据库，一个数据库中可以建立多个模式，一个模式下通常包括多个表、视图和索引等数据库对象。    

* 模式的定义和删除    

    ```sql
    CREATE SCHEMA TEST AUTHORIZATION BAO 
    CREATE TABLE TAB1(
        COL1 SMALLINT,
        COL2 INT,
        COL3 CHAR(20),
        COL4 NUMERIC(10,3),
        COL5 DECIMAL(5,2)
    );
    DROP SCHEMA TEST CASCADE/RESTRICT;   
    ``` 

* 基本表的定义和删除和修改     

    ```sql
    //建一个基本表Student 
    CREATE TABLE Student(
        Sno CHAR(9) PRIMARY KEY,
        Sname CHAR(20) UNIQUE,
        Ssex CHAR(2),
        Sage SMALLINT,
        Sdept CHAR(20)
    );

    //建一个基本表Course
    CREATE TABLE Course(
        Cno CHAR(4) PRIMARY KEY,
        Cname CHAR(40) NOT NULL,
        Cpno CHAR(4),
        Ccredit SMALLINT,
        FOREIGN KEY(Cpno) REFERENCES Course(Cno)
    );

    //建一个基本表SC
    CREATE TABLE SC(
        Sno CHAR(9),
        Cno CHAR(4),
        Grade SMALLINT,
        PRIMARY KEY(Sno,Cno),
        FOREIGN KEY(Sno) REFERENCES Student(Sno),
        FOREIGN KEY(Cno) REFERENCES Course(Cno)
    );
    ```            

* 修改基本表     

    ```sql
    //向Student表中增加"入学时间"列，数据类型为日期
    ALTER TABLE Student ADD S_entrance DATE;
    //将Student表中的年龄的数据类型改为整数类型
    AlTER TABLE Student ALTER COLUMN Sage INT;
    //增加课程名必须取唯一值的约束 
    ALTER TABLE ADD COLUMN UNIQUE(Cname);
    ```   

* 删除基本表    

    ```sql
    //删除Student表   
    DROP TABLE Student CASCADE;  
    ```    

* 索引的建立和删除    
    
    ```sql
    //给Student、Course和SC三个表建立索引，其中Student表按学号升序建唯一索引，
    CREATE UNIQUE INDEX Stusno ON Student(Sno ASC);
    //Course表按课程号建唯一索引
    CREATE UNIQUE INDEX Coucno ON Course(Cno);
    //SC表按学号升序和课程号降序建唯一索引
    CREATE UNIQUE INDEX SCsnocno ON SC(Sno ASC,Cno DESC);
    ```
    



