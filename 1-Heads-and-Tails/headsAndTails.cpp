#include <iostream>
#include <string>


class HeadsAndTails{
public:
	typedef unsigned int seq_size;

	enum coin_side{
		HEAD,
		TAIL,
		NONE
	};

	static const char HEAD_SIGN = 'H';
	static const char TAIL_SIGN = 'T';

	HeadsAndTails():
		head_longest_secquence(0),
		head_current_secquence(0),
		tail_longest_secquence(0),
		tail_current_secquence(0),
		previous_toss(HEAD){}

	coin_side start_game(const std::string &input);

	void add_toss(coin_side toss);

	coin_side get_current_winner();

	void reset();

protected:

	bool is_consistent_toss(coin_side current_toss){
		return (previous_toss == current_toss);
	}

	void increment_current_sequence(coin_side current_toss);

	void unpdate_ended_sequence(coin_side current_toss);

	seq_size &get_current_sequnce(coin_side current_toss);

	seq_size &get_longest_sequnce(coin_side current_toss);

	void unpdate_ended_sequence(seq_size &current_sequence, seq_size &longest_sequence);

	void unpdate_sequence(seq_size &current_sequence, seq_size &longest_sequence);

private:
	seq_size head_longest_secquence;
	seq_size head_current_secquence;
	seq_size tail_longest_secquence;
	seq_size tail_current_secquence;

	coin_side previous_toss;
};


int main(int argc , char *argv[]){

	if(argc < 2){
		std::cout<<" Not enought parameters!"<<std::endl;
	}else{
		HeadsAndTails game;
		game.start_game(argv[1]);

		switch(game.get_current_winner()){

		case HeadsAndTails::HEAD:{
				std::cout<<"H wins!"<<std::endl;
			break;
			  }

		case HeadsAndTails::TAIL:{
					std::cout<<"T wins!"<<std::endl;
			break;
			  }
		default:{
			std::cout<<"Draw!"<<std::endl;
				  break;
		      }
		}
	}
}

typedef HeadsAndTails::seq_size seq_size;
typedef HeadsAndTails::coin_side coin_side;

inline coin_side HeadsAndTails::start_game(const std::string &input){
		for(size_t input_index = 0 ; input_index < input.size() ; input_index++){
			switch(input[input_index]){
			case HEAD_SIGN:{
				add_toss(HEAD);
				break;
						   }
			case TAIL_SIGN:{
				add_toss(TAIL);
				break;
						   }
			}
		}
		return get_current_winner();
	}


inline void HeadsAndTails::add_toss(coin_side toss){
		if(!is_consistent_toss(toss)){
			unpdate_ended_sequence(toss);		
		}
		increment_current_sequence(toss);
	}


inline coin_side HeadsAndTails::get_current_winner(){

		unpdate_sequence(head_current_secquence, head_longest_secquence);
		unpdate_sequence(tail_current_secquence, tail_longest_secquence);

		if(head_longest_secquence > tail_longest_secquence){
			return HEAD;
		}else if(head_longest_secquence < tail_longest_secquence){
			return TAIL;
		}else{
			return NONE;
		}
	}


inline void HeadsAndTails::reset(){
		head_longest_secquence = 0,
		head_current_secquence = 0,
		tail_longest_secquence = 0,
		tail_current_secquence = 0,
		previous_toss = HEAD;
	}

inline void HeadsAndTails::increment_current_sequence(coin_side current_toss){
		switch(current_toss){
		case HEAD:{
			head_current_secquence++;
			break;
				  }
		case TAIL:{
			tail_current_secquence++;
			break;
				  }
		}
	}


inline void HeadsAndTails::unpdate_ended_sequence(coin_side current_toss){
		seq_size &curr_seq = get_current_sequnce(previous_toss);
		seq_size &longest_seq = get_longest_sequnce(previous_toss);
		unpdate_ended_sequence(curr_seq,longest_seq);
		previous_toss = current_toss;
	}

inline seq_size &HeadsAndTails::get_current_sequnce(coin_side current_toss){
		if(current_toss == HEAD){
			return head_current_secquence;
		}else{
			return tail_current_secquence;
		}
	}


inline seq_size &HeadsAndTails::get_longest_sequnce(coin_side current_toss){
		if(current_toss == HEAD){
			return head_longest_secquence;
		}else{
			return tail_longest_secquence;
		}
	}


inline void  HeadsAndTails::unpdate_ended_sequence(seq_size &current_sequence, seq_size &longest_sequence){
		unpdate_sequence(current_sequence,longest_sequence);
		current_sequence = 0;
	}

inline void HeadsAndTails::unpdate_sequence(seq_size &current_sequence, seq_size &longest_sequence){
		if(current_sequence > longest_sequence){
			longest_sequence = current_sequence;
		}
	}
