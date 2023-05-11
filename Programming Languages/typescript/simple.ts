function fib(num:Number){
    var fib = [0, 1];

    if(num == 0){
        console.log("Fib number " + 0 + " equals " + 0);
    }
    else if(num == 1){
        console.log("Fib number " + 0 + " equals " + 0);
        console.log("Fib number " + 1 + " equals " + 1);
    }
    else{
        console.log("Fib number " + 0 + " equals " + 0);
        console.log("Fib number " + 1 + " equals " + 1);

        for (var i = 2; i <= num; i++) {
            fib[i] = fib[i - 2] + fib[i - 1];
            console.log("Fib number " + i + " equals " + fib[i]);
        }
    }
}
fib(10);