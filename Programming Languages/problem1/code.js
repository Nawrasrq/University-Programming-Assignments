
function isPrime( num )
{
    sqrt = Math.sqrt(num);
    if (num < 1){
        return 0;
    }
    for(let i = 2; i <= sqrt; i++) {
        if(num % i === 0){
            return 0;
        }
    }
    return 1;

}

function calcFib()
{  
    var fib = [0, 1];
    
    num = document.getElementById("fib").value;
    
    if(num == 0){
        document.getElementById("answer1").innerHTML = "The answer is " + String(0)

    }
    else if(num == 1){        
        document.getElementById("answer1").innerHTML = "The answer is " + String(1)
    }
    else{
        var i = 2;
        let a = 0;
        for (; i <= num; i++) {
            fib[i] = fib[i - 2] + fib[i - 1];
            a = fib[i]
        }
        document.getElementById("answer1").innerHTML = "The answer is " + String(a)
    }
}

function calcPrime()
{
    num = document.getElementById("prime").value;
    if(isPrime(num) == 0){
        document.getElementById("answer2").innerHTML = "The number is not prime";
    }
    else{
        num = parseInt(num)
        while(true){
            num = num + 1;
            if(isPrime(num) == 1){
                document.getElementById("answer2").innerHTML = "The number is prime, the next prime is " + String(num);
                return 0;
            }
        }
    }
    
}
