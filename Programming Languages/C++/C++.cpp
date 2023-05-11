#include <iostream>
using std::cout; 
using std::endl;
using std::cin;

#include <string>
using std::string;
using std::getline;

class student {
	private:
		int admno;
		string sname;
		float eng, math, science, total;
	
	float ctotal(){
		return total = eng + math + science;
	}
	
	public:
		void Takedata(int admno, string sname, float eng, float math, float science){
			this->admno = admno;
			this->sname = sname;
			this->eng = eng;
			this->math = math;
			this->science = science;
			
			ctotal();
		}
		void ShowData(){
			cout << "sname:" << sname << " admno:" << admno << endl;
			cout << "eng:" << eng << " math:" << math << " science:" << science << endl;
			cout << "ctotal: " << total << endl;
		}
};

class batsman {
	private:
		string bcode;
		string bname;
		int innings, notout, runs;
		float batavg;
	
	float calcavg(){
		return batavg = runs/(innings-notout);
	}
	
	public:
		void readdata(string bcode, string bname, int innings, int notout, int runs){
			this->bcode = bcode;
			this->bname = bname;
			this->innings = innings;
			this->notout = notout;
			this->runs = runs;
			
			calcavg();
		}
		void displaydata(){
			cout << "bcode:" << bcode << " bname:" << bname << endl;
			cout << "innings:" << innings << " notout:" << notout << " runs:" << runs << endl;
			cout << "ctotal: " << batavg << endl;
		}
};

class TEST{
	private:
		int TestCode, NoCandidates, CenterReqd;
		string Description; 
	
		float CALCNTR(){
			return CenterReqd = NoCandidates/100 + 1;
		}
	public:
		void SCHEDULE(string Description, int TestCode, int NoCandidates){
			this->Description = Description;
			this->TestCode = TestCode;
			this->NoCandidates = NoCandidates;
			
			CALCNTR();
		}
		void DISPTEST(){
			cout << "Description:" << Description << endl;
			cout << "TestCode:" << TestCode << " NoCandidates:" << NoCandidates << endl;
			cout << "CenterReqd: " << CenterReqd << endl;
		}
};

class flight{
	private:
		int Flight;
		float Distance, Fuel;
		string Desination; 
	
		float CALCFUEL(){
			if(Distance <= 1000){
				return Fuel = 500;
			}
			else if(Distance > 1000 && Distance <= 2000){
				return Fuel = 1100;
			}
			else
				return Fuel = 2200;
		}
	public:
		void FEEDINFO(string Desination, float Distance, int Flight){
			this->Desination = Desination;
			this->Distance = Distance;
			this->Flight = Flight;
			
			CALCFUEL();
		}
		void SHOWINFO(){
			cout << "Description:" << Desination << endl;
			cout << "TestCode:" << Distance << " Flight:" << Flight << endl;
			cout << "Fuel: " << Fuel << endl;
		}
};

class BOOK{
	private:
		int BOOK_NO;
		string BOOK_TITLE;
		float PRICE;
		
		float TOTAL_COST(int N){
			return N*PRICE;
		}
	public:
		void INPUT(string BOOK_TITLE, int BOOK_NO, float PRICE){
			this->BOOK_TITLE = BOOK_TITLE;
			this->BOOK_NO = BOOK_NO;
			this->PRICE = PRICE;
		}
		void PURCHASE(){
			string N;
			cout << "Input how many books:" << endl;
			getline(cin, N);
			
			float total = TOTAL_COST(std::stoi(N));
			cout << "Total cost:" << total << endl;
		}
};

class REPORT{
	private:
		string adno;
		string name;
		float marks[5];
		float average;
		
		float GETAVG(){
			return average = (marks[0] + marks[1] + marks[2] + marks[3] + marks[4])/5;
		}
	public:
		void READINFO(string adno, string name, float* marks){
			this->adno = adno;
			this->name = name;
			marks = marks;

			GETAVG();
		}
		void DISPLAYINFO(){
			cout << "adno:" << adno << " name:" << name << endl;
			for(int i = 0; i < 5; i++){
				cout << "mark " <<  i << " :"<< marks[i] << endl;
			}
			cout << "average: " << average << endl;
		}
};

class Rectangle{
	public:
		float length, width;
		
		void setLength(float length){
			this->length = length;
		}
		void setWidth(float width){
			this->width = width;
		}
		float perimeter(){
			return 2*length+2*width;
		}
		float area(){
			return length*width;
		}
		void show(){
			cout << "length:" << length << " width:" << width << endl;
		}
		int sameArea(Rectangle R){
			if(R.area() == area()){
				return 1;
			}else{
				return 0;
			}
		}
};

class complex{
	public:
		float real, imag;
		
		void set(float real, float imag){
			this->real = real;
			this->imag = imag;
		}
		
		void disp(){
			cout << imag << "i"<< real << endl;
		}
		complex sum(complex c){
			complex n;
			n.set(c.real + real, c.imag + imag);
			return n;
		}
};

class Distance{
	public:
		int feet;
		float inches;
		
		void set(int feet, float inches){
			this->feet = feet;
			this->inches = inches;
		}
		
		void disp(){
			cout << "feet: " << feet << " inches: "<< inches << endl;
		}
		Distance add(Distance d){
			Distance n;
			n.set(d.feet + feet, d.inches + inches);
			return n;
		}
};

class Time{
	public:
		int hours, minutes;
		
		void settime(int hours, int minutes){
			this->hours = hours;
			this->minutes = minutes;
		}
		
		void showtime(){
			cout << "hours: " << hours << " minutes: "<< minutes << endl;
		}
		Time sum(Time d){
			Time n;
			n.settime(d.hours + hours, d.minutes + minutes);
			return n;
		}
};

int main (){
	student stud;
	stud.Takedata(5, "name", 5.3, 10.5, 15.2);
	stud.ShowData();

	batsman bat;
	bat.readdata("4412", "batterman", 5, 4, 9);
	bat.displaydata();

	TEST test;
	test.SCHEDULE("A description here", 12, 15);
	test.DISPTEST();

	flight flight;
	flight.FEEDINFO("Toronto", 2000, 100);
	flight.SHOWINFO();

	BOOK book;
	book.INPUT("Book name here", 22, 12.15);
//	book.PURCHASE();

	REPORT report;
	float arr[5] = {0.5, 0.6, 1.5, 2.5, 5.5};
	report.READINFO("adno 12", "namez", arr);

	Rectangle R;
	R.setLength(5);
	R.setWidth(2.5);
	Rectangle R2;
	R2.setLength(5);
	R2.setWidth(18.9);
	R.perimeter();
	R2.perimeter();
	R.area();
	R2.area();
	R.sameArea(R2);
	R.setLength(15);
	R.setWidth(6.3);
	R.perimeter();
	R2.perimeter();
	R.area();
	R2.area();
	R.sameArea(R2);

	complex one;
	complex two;
	complex three;
	one.set(5,3);
	two.set(1,2);
	three = one.sum(two);

	Distance a;
	Distance b;
	Distance c;
	a.set(5,3.1);
	b.set(1,2.4);
	c = a.add(b);

	Time e;
	Time f;
	Time g;
	e.settime(5,30);
	f.settime(1,20);
	g = e.sum(g);


}