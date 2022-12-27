class Complex {
	private :
	int real;
	int img;
	
	public : //constructor always public
		Complex(int real, int img) {
			this->real = real;
			this->img = img;
			
		}

    void display() {
    	cout << real << " + " << img << "i" << endl;
	}
	
	void add(Complex const &c2) { //using const and passing address for optimisation
		
		int real_part = this->real + c2.real; //you can access c2's private members directly through a public function
		int img_part = this->img + c2.img; 
		this->real = real_part;
		this->img = img_part;
	}
    void multiply(Complex const &c2) {
    	int real_part = (this->real * c2.real) - (this->img * c2.img);
    	int img_part =  (this->real * c2.img) + (this->img * c2.real);
    	
    	this->real = real_part;
    	this->img = img_part;
	}

};