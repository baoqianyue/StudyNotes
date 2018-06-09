/**
 * ES6 对面向对象的支持  
 */

class Animal {
    //构造函数
    constructor() {
        this.name = "animal";
    }
    //成员函数
    getName() {
        return this.name;
    }
}

//实例化对象
let animal = new Animal();

class Animal1 {
    constructor(name) {
        this.name = name;
    }
    getName() {
        return this.name;
    }
}
let animal1 = new Animal1("test");

class Cat extends Animal {
    constructor() {
        super();//调用一下父类构造函数，获取this指针
        this.name = 'cat';
    }
}

//对象写法
var name = 'Barack',
    age = 18;
var obj = {
    name: name,
    age: age,
    getName: function () {
        return this.name;
    },
    getAge: function () {
        return this.age;
    }
}

//对象的拓展   
Object.keys(obj);//输出一个对象的所有属性
