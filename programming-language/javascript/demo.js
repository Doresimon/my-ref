//// 1
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

//// 2
// class People {
//   constructor(name, age = 18) {
//     this.name = name;
//     this.age = age;
//   }
//   // instance methods
//   hello() {
//     console.log(`hello, i'm ${this.name}`);
//   }
//   foo() {
//     console.log("People.name", People.name);
//   }
//   // static methods(only for class)
//   static oops() {
//     console.log("oops");
//     if (!this.prototype.cnt) {
//       this.prototype.cnt = 0; // define a static variable
//     }
//     this.prototype.cnt++;
//     console.log("cnt", this.prototype.cnt);
//   }
// }

// const alice = new People("alice");
// alice.hello();
// alice.foo();
// // alice.oops(); // not a function
// People.oops();
// People.oops();

//// 3
// const wait = () => {
//   return new Promise((resolve, reject) => {
//     setTimeout(resolve, 1000);
//   });
// };

// wait()
//   .then(() => {
//     console.log("Promised to run 1000ms later");
//     return wait();
//   })
//   .then(() => {
//     console.log("Promised to run 1000ms + 1000ms later");
//   });

//// 4
// const alice = {
//   name: "alice",
//   age: 18,
//   school: {
//     name: "fdu"
//   }
// };
// const { name: herName, age, school: school } = alice;
// console.log(herName, age, school);

// const map = new Map();
// map.set(1, "aaa");
// map.set({ name: 1 }, "bbb");

// console.log(map.get(1));
// console.log(map.get({ name: 1 })); // error

//// 5

class People {}

console.log("true", typeof true); // number
console.log("NaN", typeof NaN); // number
console.log("Infinity", typeof Infinity); // number
console.log("1", typeof 1); // number
console.log("''", typeof ""); // string
console.log("[]", typeof []); // object
console.log("{}", typeof {}); // object
console.log("null", typeof null); // object
console.log("undefined", typeof undefined); // undefined
console.log("() => {}", typeof (() => {})); // function
console.log("class{}", typeof People); // function
console.log("Symbol('...')", typeof Symbol("s")); // symbol

//// 6
function Car(make, model, year) {
  this.make = make;
  this.model = model;
  this.year = year;
}
let someCar = new Car("Honda", "Accord", 1998);

console.log(someCar instanceof Car);
// expected output: true

console.log(someCar instanceof Object);
// expected output: true

let arr = [1, 2, 3];

let nnn = Number(666);
let sss = "aaaaa";

console.log(arr instanceof Array);
console.log(1 instanceof Number);
console.log(Number(1) instanceof Number);
console.log(new Number(1) instanceof Number);
console.log(sss instanceof String);
