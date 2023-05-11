<Query Kind="Program">
  <Connection>
    <ID>54bf9502-9daf-4093-88e8-7177c12aaaaa</ID>
    <NamingService>2</NamingService>
    <Persist>true</Persist>
    <Driver Assembly="(internal)" PublicKeyToken="no-strong-name">LINQPad.Drivers.EFCore.DynamicDriver</Driver>
    <AttachFileName>&lt;ApplicationData&gt;\LINQPad\ChinookDemoDb.sqlite</AttachFileName>
    <DisplayName>Demo database (SQLite)</DisplayName>
    <DriverData>
      <PreserveNumeric1>true</PreserveNumeric1>
      <EFProvider>Microsoft.EntityFrameworkCore.Sqlite</EFProvider>
      <MapSQLiteDateTimes>true</MapSQLiteDateTimes>
      <MapSQLiteBooleans>true</MapSQLiteBooleans>
    </DriverData>
  </Connection>
</Query>

abstract class Vehicle
{
	public string type;
	
	public Vehicle(string type){
		this.type = type;
	}
	public string getType(){
		return type;
	}

	public abstract void drive();
}

class Car : Vehicle{
  public string model; 
  

  public Car(string model) : base("car"){
    this.model = model;
  
  }
  public override void drive(){
  	Console.WriteLine("I'm driving my " + type + " it's a " + model);
  }

  
}

class Motorbike : Vehicle{
  public string model; 
  

  public Motorbike(string model) : base("bike"){
    this.model = model;
  
  }
  public override void drive(){
  	Console.WriteLine("I'm driving my " + type + " it's a " + model);
  }
  
}
static void Main(string[] args)
  {
    Vehicle[] garage = new Vehicle[3];
	garage[0] = new Car("mustang");
	garage[1] = new Car("ford");
	garage[2] = new Motorbike("harvey");
    garage[0].drive();
	
	List<Vehicle> v = new List<Vehicle>();
	v.Add(new Car("mustang"));
	v.Add(new Car("ford"));
	v.Add(new Motorbike("harvey"));
	v.Add(new Motorbike("dent"));
	
	var x = garage.Where(x => x.type == "bike").Select(x => new {Type = x.type});
	
    foreach (var item in x)
    {
        Console.WriteLine($"{item.Type}");
    }
  }