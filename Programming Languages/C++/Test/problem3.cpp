#include <math.h>
#include <vector>
#include <iostream>

void largest_prime_factor(long long num){
    int z = 2;
    long long max = -1;

    while(z*z <= num){
        if (num % z == 0){
            if(z > max){
                max = z;
            }
            num = num / z;
        }
        else{
            z++;
        }
    }
    if(num > 1)
        if(num > max){
            max = num;
        }
    std::cout << "largest prime factor is " << max << std::endl;
}

main(){
    largest_prime_factor(600851475143);

}
