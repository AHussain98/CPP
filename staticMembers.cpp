class Student{
	
	private: //so that it cannot be accessed outisde the class, but then how can it be initialised??? Can be accessed by using a function
	static int totalStudents; //static means in the whole programme, this specific variable will be created only once
	//initalisation of the static variable should be done outside of the class
	int age;
	int rollno;
	public:	
	Student(int age, int rollno){
	this->age = age;	
	this->rollno = rollno;	
	totalStudents++;
	}
	
	Student() {
		cout << "Constructor called" << endl;
		totalStudents++;
	}
	
	int static NumStudents(){ //static variable can only be returned using a static function
		return totalStudents; //public function to access the private totalStudents variable
	} // private varibales can be accessed through public functions, though if the variable is static, the function must also be static
	
}; 
//double colon is the scope resolution operator, whatever is on the rhs belongs to the structure on the lhs
int Student::totalStudents = 0; //static variables can never be initialised inside their class, only ouside in this manner
// first datatype, class, scope resolution operator, static variable and then value
//we have to preface it with Student:: because it belong to the class and is not the specific property of one student object
//why can we access the static above outside the class even though its private??

//static variables/functions only have one copy in the memory, they take up their own memory space away from ebeyrthing else
//static variables value initalised outside the class with a value of 0
