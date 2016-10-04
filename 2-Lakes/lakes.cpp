#include <iostream>
#include <string>

class Lake{
public:
	typedef char relief;

	static const relief down = 'd';
	static const relief up = 'u';
	static const relief horizontal = 'h';


	Lake(const std::string &lake_decription):watter_capacity(0),current_watter_depht(0){
		for(unsigned index = 0; index < lake_decription.size() ; index++){
			add_relief(lake_decription[index]);
		}
	}

	unsigned int get_total_watter(){
		return  watter_capacity;
	}

protected:

	void add_relief(relief rel){
		switch(rel){
		case down:{
				if(current_watter_depht >= 0){
					watter_capacity+= (500 + current_watter_depht*1000);
				}
				current_watter_depht++;
				break;
			 }
		case up :{
			if(current_watter_depht > 0){
				watter_capacity+= (-500 + current_watter_depht*1000);		
			}
			current_watter_depht--;
			break;
			  }
		case horizontal:{
			if(current_watter_depht > 0){
				watter_capacity += current_watter_depht*1000;			
			}
			break;
			  }
		}
	}


private:
	unsigned int watter_capacity; //the total watter in the lake multiplicate by two.
								//operation with integer is much faster than float
	int current_watter_depht; //the current real watter depth
};

int main(int argc , char *argv[]){

	if(argc < 2){
		std::cout<<"Not enought arguments"<<std::endl;
	}else{
		Lake lake(argv[1]);
		std::cout<<lake.get_total_watter()<<std::endl;
	}

	return 0;
}
