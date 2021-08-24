# ABC of C#

## Language introduction

- [菜鸟教程](https://www.runoob.com/csharp/csharp-tutorial.html)
- [c# | Microsoft Doc](https://docs.microsoft.com/en-us/dotnet/csharp/)

## Feature

### Dependency Injection (DI)

- [wiki](https://en.wikipedia.org/wiki/Dependency_injection)
- [dependency-injection | Microsoft Doc](https://docs.microsoft.com/en-us/dotnet/core/extensions/dependency-injection)

### Attribute

```cs
class User
{
    [Obsolete]
    public string Name {get; set;}
}
```

- [Attribute | Microsoft Doc](https://docs.microsoft.com/en-us/dotnet/csharp/programming-guide/concepts/attributes/)

### Async/Await & Task

```cs
async Task Sleep_1_Second(){
    await Task.Delay(1000);
}
await Sleep_1_Second();
```

- [Async/Await | Microsoft Doc](https://docs.microsoft.com/en-us/dotnet/csharp/programming-guide/concepts/async/)
- [await operator| Microsoft Doc](https://docs.microsoft.com/en-us/dotnet/csharp/language-reference/operators/await)
- [Task | Microsoft Doc](https://docs.microsoft.com/en-us/dotnet/csharp/programming-guide/concepts/async/task-asynchronous-programming-model)

### Lambda expressions

```cs
Func<int, string> func = (number) => number.ToString();
var ret = func(1); // ret = "1"
```

- [Lambda expressions | Microsoft Doc](https://docs.microsoft.com/en-us/dotnet/csharp/language-reference/operators/lambda-expressions)

### Exception

```cs
try {
    throw new Exception();
} catch(Exception e) {
    Console.WriteLine("Exception is " + e.Message);
} finally {
    Console.WriteLine("Always executed");
}
```

- [Exception | Microsoft Doc](https://docs.microsoft.com/en-us/dotnet/csharp/fundamentals/exceptions/)

## Sample Apps

- [web API | Helloworld](https://docs.microsoft.com/en-us/aspnet/core/tutorials/first-web-api?view=aspnetcore-5.0&tabs=visual-studio)
- [web API | With MongoDB](https://docs.microsoft.com/en-us/aspnet/core/tutorials/first-mongo-app?view=aspnetcore-5.0&tabs=visual-studio)
