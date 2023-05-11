//problem 14
function collatzSequence(n){
    count = 0;
    while(n != 1){
        if(n%2 == 0){
            n = n/2;
        }
        else{
            n = 3*n+1;
        }
        count += 1;
    }
    return count;
}

function longestCollatzSequence(){
    let biggestChain = 0;
    let num = 0;
    for(let i = 1; i <= 1000000; i++){
        let currChain = collatzSequence(i);

        if(currChain > biggestChain){
            biggestChain = currChain;
            num = i;
        }
    }
    console.log("Number that produces the longest chain: " + num);
    console.log("chain length: " + biggestChain);
}

longestCollatzSequence();

//problem 20
function factorial(n){
    if(n == 1){
        return n;
    }

    return n * factorial(n-1);
}

function factorialDigitSum(n){
    let digit = factorial(n);
    let total = 0;

    while(digit){
        total += total + digit%10;
        digit = Math.floor(digit/10);
    }

    return total;
}

console.log("factorial digit sum of 100: " + BigInt(factorialDigitSum(100)));