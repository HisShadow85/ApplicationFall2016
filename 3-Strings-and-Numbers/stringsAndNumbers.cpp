#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<sstream>
#include<algorithm>
#include<regex>
#include<iterator>
#include"BigInteger.h"

class Map{
public:
	static const int INSIGNIFICANT = -1;
	static const int MAX_SYMBOLS = 128;

	struct Symbol{
		unsigned char ch;
		unsigned count;
		Symbol(unsigned ch,unsigned count):ch((unsigned char)ch),count(count){}
	};

	struct Comparator{
		bool operator()(const Symbol &sym1,const Symbol &sym2){
			return sym1.count < sym2.count;
		}
	};

	Map(std::string &cripted_str):symbols(MAX_SYMBOLS,0){

		for(unsigned index = 0 ; index < cripted_str.size(); index++){
			symbols[cripted_str[index]]++;
		}

		std::priority_queue<Symbol, std::vector<Symbol>, Comparator > priority_q;

		for(unsigned index = 0 ; index < symbols.size(); index++){
			if(symbols[index] != 0){
				priority_q.push(Symbol(index,symbols[index]));
			}
			symbols[index] = INSIGNIFICANT;
		}

		for(unsigned index = 0 ; index < 10 && !priority_q.empty() ; index++){
			Symbol &sym =  priority_q.top();
			symbols[sym.ch] = (9 - index) + '0';
			priority_q.pop();
		}
	}

	unsigned char get_decrypted_char(unsigned char ch){
		if(ch < symbols.size() && symbols[ch] != INSIGNIFICANT){
			return symbols[ch];
		}
		return ch;
	}

private:
	 std::vector<int> symbols;
};

void decrypt_str(std::string &encrypted_str){
	Map symbol_digit_map(encrypted_str);
	for(unsigned index = 0 ; index < encrypted_str.size(); index++){
		encrypted_str[index] = symbol_digit_map.get_decrypted_char(encrypted_str[index]);
	}
}

std::vector<std::string*> *get_number_tokens(std::string &decrypted_str){
	//std::istringstream iss(decrypted_str);
	std::vector<std::string*> *tokens = new std::vector<std::string*>();

	for(unsigned index = 0 ; index < decrypted_str.size(); index++){
		std::string *curr_num = new std::string();
		//remove non digit symbols
		while (!isdigit(decrypted_str[index])){
			index++;
		}
		//extract the digits
		while (isdigit(decrypted_str[index])){ 
			curr_num->push_back(decrypted_str[index++]);
		}

		if(curr_num->size() > 0){
			tokens->push_back(curr_num);
		}
	}

	return tokens;
}

BigInteger *get_sum_from_number(std::vector<std::string*> * tokens){
	BigInteger *sum = new BigInteger(0);
	for(unsigned index = 0; index < tokens->size(); index++){
		(*sum)+=BigInteger(*(*tokens)[index]);
	}
	return sum;
}

int main(int argc , char *argv[]){
	
	if(argc > 1 ){
		std::string str(argv[1]);
		decrypt_str(str);
		std::vector<std::string*> *tokens = get_number_tokens(str);
		BigInteger *sum = get_sum_from_number(tokens);
		std::cout<<(string)(*sum)<<std::endl;
	}
	return 0;
}
