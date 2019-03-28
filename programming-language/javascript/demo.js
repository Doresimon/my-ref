function People(name) {
  this.name = name;
  this.age = 18;

  this.__proto__.cnt = this.__proto__.cnt || 0;
  this.__proto__.cnt++;

  this.who = function() {
    console.log(`i'm ${this.name}, ${this.age} years old.`);
  };
}
var Alice = new People("alice");
var Bob = new People("bob");
People("caca");

Alice.age = 20;
Alice.who();
Bob.who();

People.prototype.showCnt = function() {
  console.log("cnt is", this.cnt);
};

People.prototype.showCnt();
Alice.showCnt();
Bob.showCnt();
