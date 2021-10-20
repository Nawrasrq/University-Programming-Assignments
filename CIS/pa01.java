/*=============================================================================
| Assignment: pa01 - Encrypting a plaintext file using the Vigenere cipher
|
| Author: Nawras Rawas Qalaji
| Language: c, c++, Java
|
| To Compile: javac pa01.java
| gcc -o pa01 pa01.c
| g++ -o pa01 pa01.cpp
|
| To Execute: java -> java pa01 kX.txt pX.txt
| or c++ -> ./pa01 kX.txt pX.txt
| or c -> ./pa01 kX.txt pX.txt
| where kX.txt is the keytext file
| and pX.txt is plaintext file
|
| Note: All input files are simple 8 bit ASCII input
|
| Class: CIS3360 - Security in Computing - Fall 2021
| Instructor: McAlpin
| Due Date: per assignment
|
+=============================================================================*/

import java.io.*;
import java.util.*;

public class pa01{
	
	//reads file & returns lowercase string without non-alphabetic characters
	public static char[] readFile(BufferedReader file){
		char[] text = new char[512];
		int read;
		int i = 0;
		
		try{
			while((read = file.read()) != -1){
				if(Character.isLetter((char)read)){
					text[i] = Character.toUpperCase((char)read);
					i+=1;
				}
			}
		}
		catch (Exception e){
		}
		
		return text;
	}
	
	
	public static void main(String [] args) throws Exception{
		//scan file names into strings
		String keyStr = args[0];
		String plaintextStr = args[1];
		
		//open both files
		FileReader keyFile = new FileReader(keyStr);
		BufferedReader keyFileB = new BufferedReader(keyFile);
		
		FileReader plaintextFile = new FileReader(plaintextStr);
		BufferedReader plaintextFileB = new BufferedReader(plaintextFile);
		
		//read key & plaintext 
		char[] key = readFile(keyFileB);
		char[] plaintext = readFile(plaintextFileB);
		char[] ciphertext = new char[512];
		int count = 0;
		
		for(int i = 0,j = 0;i < 512; i++,j++){
			//pad plaintext with x if neccesary
			if(Character.isLetter(plaintext[i]) == false){
				plaintext[i] = 'X';
			}
			if(Character.isLetter(key[j]) == false){
				j=0;
			}
			
			//encryption
			int letter = (plaintext[i] + key[j]) % 26;
			letter += 'a';
			ciphertext[i] = (char)letter; 
		}
		
		//print out key to console
		System.out.println("\n");
		System.out.print("Vigenere Key:\n\n");
		for(int i = 0;i < 512;i++){
			count++;
			if(Character.isLetter(key[i])){
				System.out.print(Character.toLowerCase(key[i]));	
				if(count == 80 && Character.isLetter(key[i])){
					System.out.println("");
					count = 0;
				}
			}
		}
		System.out.println("\n\n");
		count = 0;
		
		//print plaintext
		System.out.print("Plaintext:\n\n");
		for(int i = 0;i < 512;i++){
			count++;
			if(Character.isLetter(plaintext[i])){
				System.out.print(Character.toLowerCase(plaintext[i]));	
				if(count == 80 && Character.isLetter(plaintext[i])){
					System.out.println("");
					count = 0;
				}
			}
		}
		System.out.println("\n\n");
		count = 0;
		
		//print ciphertext
		System.out.print("Ciphertext:\n\n");
		for(int i = 0;i < 512;i++){
			count++;
			if(Character.isLetter(ciphertext[i])){
				System.out.print(Character.toLowerCase(ciphertext[i]));	
				if(count == 80 && Character.isLetter(ciphertext[i])){
					System.out.println("");
					count = 0;
				}
			}
		}
		System.out.println("");	
	}
}

/*=============================================================================
| I Nawras Rawas Qalaji (na413580) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/