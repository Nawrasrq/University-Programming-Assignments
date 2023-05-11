function Multiple(num:Number){
    var total = 0;
    for(var i = 0; i < num; i++){
        if(i%3 == 0 || i%5 == 0){
            total = total + i;
        }
    }
    console.log("total sum is " + total);
}
Multiple(1000)

function evenFib(){
    var fib = [0, 1];
    var total = 0;
    var i = 2;

    for(var i = 2; (fib[i - 2] + fib[i - 1]) < 4000000; i++) {
        fib[i] = fib[i - 2] + fib[i - 1];
        
        if(fib[i] % 2 == 0){
            total = total + fib[i];
        }
    }

    console.log("Even Fib sum " + total);
}
evenFib();

function bigPrime(num:any) {
    var divide = 2;
    var max = 1;

    while (num >= 2) {
      if (num % divide == 0) {
        if(divide > max){
            max = divide
        }
        num = num / divide;
      } else {
        divide = divide + 1;
      }
    }
    return max;
}
  
console.log("Largest prime factor of " + 600851475143   + " is " + bigPrime(600851475143))
  