function nfib(num:Number){
    var fib = [0, 1];

    if(num == 0){
        return;
    }
    else if(num == 1){
        return;
    }
    else{
        for (var i = 2; i <= num; i++) {
            fib[i] = fib[i - 2] + fib[i - 1];
            let str = String(fib[i]*3)
            if(str.startsWith("4")){
                console.log(str)
            }
        }
    }
}

nfib(40)