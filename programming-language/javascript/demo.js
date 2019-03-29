// function People(name) {
//   this.name = name;
//   this.age = 18;

//   this.__proto__.cnt = this.__proto__.cnt || 0;
//   this.__proto__.cnt++;

//   this.who = function() {
//     console.log(`i'm ${this.name}, ${this.age} years old.`);
//   };
// }
// var Alice = new People("alice");
// var Bob = new People("bob");
// People("caca");

// Alice.age = 20;
// Alice.who();
// Bob.who();

// People.prototype.showCnt = function() {
//   console.log("cnt is", this.cnt);
// };

// People.prototype.showCnt();
// Alice.showCnt();
// Bob.showCnt();

class People {
  constructor(name, age = 18) {
    this.name = name;
    this.age = age;
  }
  // instance methods
  hello() {
    console.log(`hello, i'm ${this.name}`);
  }
  foo() {
    console.log("People.name", People.name);
  }
  // static methods(only for class)
  static oops() {
    console.log("oops");
    if (!this.prototype.cnt) {
      this.prototype.cnt = 0; // define a static variable
    }
    this.prototype.cnt++;
    console.log("cnt", this.prototype.cnt);
  }
}

const alice = new People("alice");
alice.hello();
alice.foo();
// alice.oops(); // not a function
People.oops();
People.oops();
