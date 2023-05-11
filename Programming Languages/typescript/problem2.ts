function isPrime(num:number)
{   
    let sqrt = Math.sqrt(num);
    if (num < 1){
        return 0;
    }
    for(let i = 2; i <= sqrt; i++) {
        if(num % i === 0){
            return false;
        }
    }
    return true;
}

function threeAndisNotPal(num:number){
    let str = num.toString()
    let strR = str.split("").reverse().join("")
    let strNum = str[str.length-1]

    if(str != strR){
        if(parseInt(strNum) == 3){
            return true
        }
    }
    return false
}

function primeList(num:number){
    for(let i = 0; i <= num; i++){
        if(isPrime(i) && threeAndisNotPal(i)){
            console.log(i);
        }
    }

}
primeList(1000);