class DynamicArray{
	int *data; //we need a dynamic data pointer
	int nextIndex; //will tell us the next index value to be inserted
	int capacity; //tells us size of the array
	//variables above are private by default, can only be accessed from within the class
	public:
	
	DynamicArray() { 	//constructor to initialise all these values
		data = new int[5];
		nextIndex = 0;
		capacity = 5;
	}
	
	void add(int element){
		if (nextIndex == capacity) { // means the array is full, so we need to increase the size of the array, if that's the case, see below logic
		int *newData = new int[2*capacity]; //  create a new pointer to a new heap array with double the capacity
		for(int i = 0; i < capacity; i++) {
			newData[i] = data[i]; // copy over the values from the old array to the new one, this is why the limit condition only needs to be upto the original capacity
		}
		delete []data; // so the previous heap array can be removed, to delete a heap array, you put the brackets first then array name
		data = newData; //the pointer still exists so we can repoint it to the new heap array with the larger size, this line accomplishes that
		capacity = 2*capacity; //the capacity variable is then doubled, to account for its new array size
		
		}
		
		data[nextIndex] = element; // update the value of the heap array through the pointer on the stack
		nextIndex++;
	}
	
	void print() {
		for (int i = 0; i<nextIndex;i++) {
			cout << data[i] << endl;
		}
	}
	
	int getData(int i){
		if (i >= nextIndex) {
			return -1;
		}
		return data[i];
	}
	
	//function overload is overloading fucntions so they can be used with extra parameters, or a different number/order of parameters
	//overloading the add fucntion so the first parameter is the index, second is the value:
	
	void add(int i, int element) {
		if (i < nextIndex) {
			data[i] = element;
		}
		else if (i == nextIndex) {
			add(element); // do this instead of the above because there's a possibility that the array has reached its max capacity, and the add function has the capability to increase array size in that case
		}
		else { return; //this functionality means the furthest into the array you can edit is the nextIndex value, you can't skip ahead
			
		}
	}
	
	
	//now we can define a deep copy constructor 
	DynamicArray(DynamicArray &d) {
		this->nextIndex = d.nextIndex;
		this->capacity = d.capacity;
		//this->data = d.data //shallow copy
	    this->data = new int[capacity]; // so define a new array at a new address on the heap, away from the original we're passing into the constructor
	     // now we can copy in the values from the original but NOT the address
	     for (int i = 0; i < nextIndex; i++) {
	     	this->data[i] = d.data[i]; // copy value
		 }
	//assignment operator does shallow copy by default, so doing d2 = d1 would create a shallow copy, using the above copy constructor would create a deep copy
	}
	
	
	
	
	
};