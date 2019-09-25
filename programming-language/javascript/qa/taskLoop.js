// what is the output?

function Q1() {
    async function async1() {
        console.log('async1 start');
        await async2();
        console.log('async1 end');
    }
    async function async2() {
        console.log('async2');
    }
    console.log('script start');
    setTimeout(function () {
        console.log('setTimeout');
    }, 0)
    async1();
    new Promise(function (resolve) {
        console.log('promise1');
        resolve();
    }).then(function () {
        console.log('promise2');
    });
    console.log('script end');

}

function Q2() {
    // q2
    async function async1() {
        console.log('async1 start');
        await async2();
        console.log('async1 end');
    }
    async function async2() {
        console.log('async2');
    }
    console.log('script start');
    setTimeout(function () {
        console.log('setTimeout1');
    }, 200);
    setTimeout(function () {
        console.log('setTimeout2');
        new Promise(function (resolve) {
            resolve();
        }).then(function () {
            console.log('then1')
        })
        new Promise(function (resolve) {
            console.log('Promise1');
            resolve();
        }).then(function () {
            console.log('then2')
        })
    }, 0)
    async1();
    new Promise(function (resolve) {
        console.log('promise2');
        resolve();
    }).then(function () {
        console.log('then3');
    });
    console.log('script end');
}


// // solution
// // 浏览器环境下：
// while (true) {
//     宏任务队列.shift();
//     微任务队列全部任务();
// }

// // Node 环境下：
// while (true) {
//     loop.forEach((阶段) => {
//         阶段全部任务();
//         nextTick全部任务();
//         microTask全部任务();
//     });
//     loop = loop.next;
// }
