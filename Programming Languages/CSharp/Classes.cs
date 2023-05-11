abstract class Monster{
	private float GPA;
	private float IQ;
	
	protected Monster(float GPA, float IQ){
		this.GPA = GPA;
		this.IQ = IQ;
	}
	
	public virtual void present(){
		Console.WriteLine("My team can do everything, there is no need for effort on my part.");
	}
	public abstract void prepare();
	public abstract void learn();
}

class SocialLoafer : Monster{
	public SocialLoafer(float GPA, float IQ) : base(GPA, IQ){}
	
	public override void prepare(){
		Console.WriteLine("My team can do everything, there is no need for effort on my part.");
	}
	public override void present(){
		Console.WriteLine("I will let my team do all of the presentation and stand off to the side.");
	}
	public override void learn(){
		Console.WriteLine("I learn a lot, especially when I watch YouTube cartoons..");
	}
}

class TakeAttendanceAndLeave : Monster{
	public TakeAttendanceAndLeave(float GPA, float IQ) : base(GPA, IQ){}
	
	public override void prepare(){
		Console.WriteLine("I will prepare next week. Right now I have better things to do.");
	}
	public override void present(){
		Console.WriteLine("I hope I can sneak out after my group presents. Who cares about the other teams?");
	}
	public override void learn(){
		Console.WriteLine("I will play a YouTube video while I sleep and absorb the material.");
	}
}

class IncredibleSoftwareEngineer : Monster{
	public IncredibleSoftwareEngineer(float GPA, float IQ) : base(GPA, IQ){}
	
	public override void prepare(){
		Console.WriteLine("I won't quit until this is perfect. I want to show Leinecker he is not as smart as me.");
	}
	public override void present(){
		Console.WriteLine("I dressed up for this and we practiced! More paradise.");
	}
	public override void learn(){
		Console.WriteLine("My favorite video to watch are YouTube tutorials. I know a lot.");
	}
}

static void Main(string[] args){
	SocialLoafer sl = new SocialLoafer(2.9f,80);
	IncredibleSoftwareEngineer ise = new IncredibleSoftwareEngineer(3.9f, 140);
	TakeAttendanceAndLeave taal = new TakeAttendanceAndLeave(2.1f, 90);
	Console.WriteLine("SocialLoafer");
	sl.prepare();
	sl.present();
	sl.learn();
	Console.WriteLine("IncredibleSoftwareEngineer");
	ise.prepare();
	ise.present();
	ise.learn();
	Console.WriteLine("TakeAttendanceAndLeave");
	taal.prepare();
	taal.present();
	taal.learn();
	
	Console.WriteLine("\nDynamic Binding");
	Monster m1 = new SocialLoafer(2.9f, 80);
	Monster m2 = new IncredibleSoftwareEngineer(3.9f, 140);
	Monster m3 = new TakeAttendanceAndLeave(2.1f, 90);
	
	m1.present();
	m2.present();
	m3.present();
}
