#include<iostream>
#include<list>
#include<limits>
#include<vector>
#include<cstdlib>

	typedef unsigned int_x;
	typedef unsigned int_y;
	typedef unsigned distance;
	static const distance INFINITY = std::numeric_limits<distance>::max();

struct point{
	int_x x;
	int_y y;
	point(int_x x,int_y y):x(x),y(y){}
};

class Bottles{
public:

	Bottles(){}

void add_bottle(int_x x,int_y y){
	bottles.push_back(point(x,y));
}

std::vector<std::vector<distance> > *get_adjacency_matrix(){
	std::vector<std::vector<distance> > *adj_matrix;
	adj_matrix = get_empty_adjacency_matrix();
	fill_adj_matrix(*adj_matrix);
	return adj_matrix;
}

private:

	std::vector<std::vector<distance> > *get_empty_adjacency_matrix(){
		return new std::vector<std::vector<distance> >(bottles.size() , std::vector<distance>(bottles.size()));
	}

	void fill_adj_matrix(std::vector<std::vector<distance> > &adj_matrix){
		std::list<point>::iterator vertex = bottles.begin();
		for(unsigned x = 0 ; x < bottles.size() - 1  && vertex != bottles.end(); x++){
			adj_matrix[x][x] = 0;
			
			std::list<point>::iterator &adj_vertex = get_firts_adj_vertex(vertex);
			
			for(unsigned y = x + 1; y <  bottles.size() ; y++){
				adj_matrix[x][y] = adj_matrix[y][x] = get_manhattan_distance(vertex->x,vertex->y,adj_vertex->x,adj_vertex->y);
				adj_vertex++;
			}

			vertex++;
		}
	}

	std::list<point>::iterator get_firts_adj_vertex(std::list<point>::iterator vertex){
		std::list<point>::iterator adj_vertex = bottles.begin();
		for(; adj_vertex != vertex && adj_vertex != bottles.end(); adj_vertex++);
		if(adj_vertex != bottles.end()) {
			return ++adj_vertex;
		}
		return  adj_vertex;
	}

	distance get_manhattan_distance(int_x x1,int_y y1,int_x x2,int_y y2){
		return abs_distance(x1,x2) + abs_distance(y1,y2);
	}

	template<typename dist>
	distance abs_distance(dist x, dist y){
		if(x > y){
			return x - y;
		}
		return y - x ;
	}

	std::list<point> bottles;
};

struct Result{
	distance shortest_dist;
	std::list<unsigned> path;
	Result(distance shortest_dist,std::list<unsigned> &path):shortest_dist(shortest_dist),path(path){}
};


class HamiltonPath{
public:

	HamiltonPath(std::vector<std::vector<distance> > &adj_matrix):adj_matrix(adj_matrix),current_distance(0),shortest_distance(INFINITY){}

	Result &get_shortest_hamilton_path(){
		for(unsigned start_vertex = 0 ; start_vertex < adj_matrix.size() ; start_vertex++){
			isVisited = std::vector<bool>(adj_matrix.size(),false);
			current_path.push_back(start_vertex);
			try_path_from_given_vertex(start_vertex);
			current_path.pop_back();
		}
		return Result(shortest_distance,shortest_path);
	}

protected:

	void try_path_from_given_vertex(unsigned start_vertex){
		
		if(current_path.size() == adj_matrix.size()){
			if(current_distance < shortest_distance){
				shortest_distance = current_distance;
				shortest_path = current_path;
			}
		}

		isVisited[start_vertex] = true;
		for(unsigned adj_vert_count = 1 ; adj_vert_count < adj_matrix.size(); adj_vert_count++){
			unsigned next_vertex = (start_vertex + adj_vert_count) % adj_matrix.size();
			if(can_step_on_vertex(start_vertex,next_vertex)){
				track(start_vertex,next_vertex);
				try_path_from_given_vertex(next_vertex);
				un_track(start_vertex,next_vertex);
			}
		}
		isVisited[start_vertex] = false;
	}

	bool can_step_on_vertex(unsigned vertex,unsigned adj_vertex){
		return isVisited[adj_vertex] == false && adj_matrix[vertex][adj_vertex] != INFINITY;
	}

	void track(unsigned vertex,unsigned adj_vertex){
		current_distance+=adj_matrix[vertex][adj_vertex];
		current_path.push_back(adj_vertex);
	}

	void un_track(unsigned vertex,unsigned adj_vertex){
		current_distance-=adj_matrix[vertex][adj_vertex];
		current_path.pop_back();
	}

private:
	std::vector<bool> isVisited;
	std::vector<std::vector<distance> > &adj_matrix;
	std::list<unsigned> current_path;
	std::list<unsigned> shortest_path;
	distance current_distance;
	distance shortest_distance;
};

int main(){
	int num_of_bottles;
	std::cin>>num_of_bottles;
	Bottles bottles;
	while(num_of_bottles--){
		int x , y;
		std::cin>>x>>y;
		bottles.add_bottle(x,y);
	}

	std::vector<std::vector<distance> > *adj_matrix = bottles.get_adjacency_matrix();

	/*for(int i = 0 ; i < adj_matrix->size() ; i++){
		for(int j = 0 ; j < (*adj_matrix)[i].size() ; j++){
			std::cout<<(*adj_matrix)[i][j];
		}
		std::cout<<std::endl;
	}*/

	 HamiltonPath hamiltonPath(*adj_matrix);
	 std::cout<<hamiltonPath.get_shortest_hamilton_path().shortest_dist<<std::endl;
	 delete adj_matrix;
	 return 0;
}
