
void Main()
{
	int[] arr1 = new int[] { 5, 9, 1, 2, 3, 7, 5, 6, 7, 3, 7, 6, 8, 5, 4, 9, 6, 2 };  
	Console.Write("\nLINQ : Display the number and frequency of number from given array : \n"); 
	Console.Write("---------------------------------------------------------------------\n");
	Console.Write("The numbers in the array are : \n");
	Console.Write(" 5, 9, 1, 2, 3, 7, 5, 6, 7, 3, 7, 6, 8, 5, 4, 9, 6, 2\n");

	var numQuery = from number in arr1  
                    group number by number into num  
                    select new {Number = num.Key, Count = num.Count()};
					
	foreach(var num in numQuery){
		Console.WriteLine("Number " + num.Number + " appears " + num.Count + " times");  
	}
}
