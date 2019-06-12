#ifndef Environment_H
#define Environment_H

#include<systemc.h>


SC_MODULE(environment){
	
	sc_in<bool> clock;
	sc_fifo_in<int> robot1_to_env, robot2_to_env, robot3_to_env, robot4_to_env;

	sc_out<bool> enable_env_to_robot1, enable_env_to_robot2, enable_env_to_robot3, enable_env_to_robot4;
	sc_fifo_out<int> env_to_robot1, env_to_robot2, env_to_robot3, env_to_robot4;	 

	int point_map_pos = 0;
	int obstacle_path_map_pos = 0;

    bool move_obstacle(int id);
	void update_robot_path(int id, int data);
	void update_robot(int id, int type, int data);
	void update_obstacle(int id, int data);
	void init();
	bool check_border(int id);
	bool check_obstacle_proximity(int id);
	bool move_robot(int id);
	void enable_robot(int id);
	void send_crossing_to_server(int id, sc_fifo_out<int> fifo_out);
	void env_process();
	void read_robot_fifo (int id , sc_fifo_in<int> fifo_in);


    SC_CTOR(environment){

     	SC_THREAD(env_process);
     	sensitive<<clock.pos();

     	init();
 	} 

 };
	
	void environment:: init(){

		cout<<"@ "<<sc_time_stamp()<<"------Start init--------"<<endl;

		obstacle_location_grid[1] = 1;
		obstacle_location_point[1] = {0 , 8.5*5};
		obstacle_dir[1] = 3;
		obstacle_location_grid[2] = 13;
		obstacle_location_point[2] = {0 , 6.5*5};
		obstacle_dir[2] = 3;
		obstacle_location_grid[3] = 26;
		obstacle_location_point[1] = {0 , 4.5*5};
		obstacle_dir[3] = 3;
		obstacle_location_grid[4] = 39;
		obstacle_location_point[1] = {0 , 2.5*5};
		obstacle_dir[4] = 3;
	}

	void environment::update_robot_path(int id, int data){

		cout<<"@ "<<sc_time_stamp()<<"------Start update_robot_path--------"<<endl;

		if(north[robot_location_grid[id]] == data) {
			robot_dir[id] = 1; 
			robot_location_point[id] = {left_coordinates[data].x + 2.5 , left_coordinates[data].y};
		} 

		else if(south[robot_location_grid[id]] == data) {
			robot_dir[id] = 2; 
			robot_location_point[id] = {right_coordinates[data].x - 2.5 , right_coordinates[data].y};
		}

		else if(east[robot_location_grid[id]] == data) {
			robot_dir[id] = 3; 
			robot_location_point[id] = {left_coordinates[data].x , left_coordinates[data].y + 2.5};
		} 

		else if(west[robot_location_grid[id]] == data) {
			robot_dir[id] = 4;
			robot_location_point[id] = {right_coordinates[data].x, right_coordinates[data].y - 2.5};
		}
		
		robot_location_grid[id] = data;

	}

	void environment:: update_robot(int id, int type, int data){

			cout<<"@ "<<sc_time_stamp()<<"------Start update_robot--------"<<endl;

			switch(type) {
				case 0 : // PATH
					update_robot_path(id , data);
					break;
				case 1 : // STATUS
					robot_status[id] = data;
					break;
				default :
					cout<<"WRONG TYPE INPUT ON ROBOT";
					break;
			}
	}

	void environment:: update_obstacle(int id, int data){

		cout<<"@ "<<sc_time_stamp()<<"------Start update_obstacle--------"<<endl;

		if(north[obstacle_location_grid[id]] == data) {
			obstacle_dir[id] = 1; 
			obstacle_location_point[id] = {left_coordinates[data].x + 2.5 , left_coordinates[data].y};
		}

		else if (south[obstacle_location_grid[id]] == data) {
			obstacle_dir[id] = 2; 
			obstacle_location_point[id] = {right_coordinates[data].x - 2.5 , right_coordinates[data].y};
		}

		else if (east[obstacle_location_grid[id]] == data) {
			obstacle_dir[id] = 3; 
			obstacle_location_point[id] = {left_coordinates[data].x , left_coordinates[data].y + 2.5};
		}

		else if (west[obstacle_location_grid[id]] == data) {
			obstacle_dir[id] = 4; 
			obstacle_location_point[id] = {right_coordinates[data].x, right_coordinates[data].y - 2.5};
		}
		
		obstacle_location_grid[id] = data;

	}

	bool environment::  move_obstacle(int id){

		cout<<"@ "<<sc_time_stamp()<<"------Start move_obstacle--------"<<endl;

		bool is_grid_crossing = false;
			switch(obstacle_dir[id]) {
				case 1 : // North
					obstacle_location_point[id].y += grid_point_location_obstacle[point_map_pos];
					if(obstacle_location_point[id].y >= right_coordinates[obstacle_location_grid[id]].y) {
						update_obstacle(id , obstacle_path[id][obstacle_path_map_pos%(obstacle_path[id].size())]);
						is_grid_crossing = true;
					}
					break;
				case 2 : // South
					obstacle_location_point[id].y -= grid_point_location_obstacle[point_map_pos];
					if(obstacle_location_point[id].y <= left_coordinates[obstacle_location_grid[id]].y) {
						update_obstacle(id , obstacle_path[id][(obstacle_path_map_pos)%(obstacle_path[id].size())]);
						is_grid_crossing = true;
					}
					break;
				case 3 : // East
					obstacle_location_point[id].x += grid_point_location_obstacle[point_map_pos];
					if(obstacle_location_point[id].x >= right_coordinates[obstacle_location_grid[id]].x) {
						update_obstacle(id , obstacle_path[id][(obstacle_path_map_pos)%(obstacle_path[id].size())]);
						is_grid_crossing = true;
					}
					break;
				case 4 : // West
					obstacle_location_point[id].x -= grid_point_location_obstacle[point_map_pos];
					if(obstacle_location_point[id].x <= left_coordinates[obstacle_location_grid[id]].x) {
						update_obstacle(id , obstacle_path[id][(obstacle_path_map_pos)%(obstacle_path[id].size())]);
						is_grid_crossing = true;
					}
					break;
				default : 
					break;
			}
			return is_grid_crossing;

	}

	bool environment:: check_border (int id) {

			cout<<"@ "<<sc_time_stamp()<<"------Start check_border--------"<<endl;

			return robot_location_point[id].y >= right_coordinates[robot_location_grid[id]].y || robot_location_point[id].y <= left_coordinates[robot_location_grid[id]].y
				|| robot_location_point[id].x >= right_coordinates[robot_location_grid[id]].x || robot_location_point[id].x <= left_coordinates[robot_location_grid[id]].x;
	}

	bool environment:: check_obstacle_proximity(int id) {

			cout<<"@ "<<sc_time_stamp()<<"------Start check_obstacle_proximity--------"<<endl;

			for(int i = 1 ; i <= 4 ; i++) {

				if(robot_dir[id] == 1 && obstacle_dir[i] == 2) {

					return robot_location_point[id].y < obstacle_location_point[i].y && obstacle_location_point[i].y - robot_location_point[id].y <= 3.0;
				} 

				else if(robot_dir[id] == 2 && obstacle_dir[i] == 1) {
					
					return robot_location_point[id].y > obstacle_location_point[i].y && robot_location_point[id].y - obstacle_location_point[i].y <= 3.0;
				}  

				else if(robot_dir[id] == 3 && obstacle_dir[i] == 4) {
					
					return robot_location_point[id].x < obstacle_location_point[i].x && obstacle_location_point[i].x - robot_location_point[id].x <= 3.0;
				} 

				else if(robot_dir[id] == 4 && obstacle_dir[i] == 3) {
				
					return robot_location_point[id].x > obstacle_location_point[i].x && robot_location_point[id].x - obstacle_location_point[i].x <= 3.0;
				} 
			}

			return false;
	}

	bool environment:: move_robot (int id) {

			cout<<"@ "<<sc_time_stamp()<<"------Start move_robot--------"<<endl;

			int is_grid_crossing = false;
			if(robot_location_grid[id] == 0 || (robot_status[id] == 0 && check_border(id)) || check_obstacle_proximity(id)) {
				
				return false;
			}

			switch(robot_dir[id]) {
				case 1 : // North
					robot_location_point[id].y += grid_point_location_obstacle[point_map_pos];
					
					if(robot_location_point[id].y >= right_coordinates[robot_location_grid[id]].y) {
						
						is_grid_crossing = true;
					}
					break;

				case 2 : // South
					robot_location_point[id].y -= grid_point_location_obstacle[point_map_pos];
					
					if(robot_location_point[id].y <= left_coordinates[robot_location_grid[id]].y) {
					
						is_grid_crossing = true;
					}
					break;
				
				case 3 : // East
					robot_location_point[id].x += grid_point_location_obstacle[point_map_pos];
					
					if(robot_location_point[id].x >= right_coordinates[robot_location_grid[id]].x) {
					
						is_grid_crossing = true;
					}
					break;
				
				case 4 : // West
					robot_location_point[id].x -= grid_point_location_obstacle[point_map_pos];
				
					if(robot_location_point[id].x <= left_coordinates[robot_location_grid[id]].x) {
				
						is_grid_crossing = true;
					}
					break;
				default : 
					break;
			}
			return is_grid_crossing;
	}

	void environment:: enable_robot (int id) {

			cout<<"@ "<<sc_time_stamp()<<"------Start enable_robot--------"<<endl;

			enable_env_to_robot1.write(false);
			enable_env_to_robot2.write(false);
			enable_env_to_robot3.write(false);
			enable_env_to_robot4.write(false);
			wait(10 , SC_NS);
			switch(id) {
				case 1 : 
					enable_env_to_robot1.write(true);
					break;
				case 2 : 
					enable_env_to_robot2.write(true);
					break;
				case 3 : 
					enable_env_to_robot3.write(true);
					
					break;
				case 4 : 
					enable_env_to_robot4.write(true);
					break;
			}
			wait(10 , SC_NS);
			enable_env_to_robot1.write(false);
			enable_env_to_robot2.write(false);
			enable_env_to_robot3.write(false);
			enable_env_to_robot4.write(false);
		}

	void environment:: send_crossing_to_server (int id, sc_fifo_out<int> fifo_out) {
			cout<<"@ "<<sc_time_stamp()<<"------Start send_crossing_to_server--------"<<endl;

			fifo_out.write(id);
			fifo_out.write(1); // count
			fifo_out.write(0); // status signal
			fifo_out.write(2); // START
			enable_robot(id);
	}

	void environment:: read_robot_fifo (int id , sc_fifo_in<int> fifo_in) {

			cout<<"@ "<<sc_time_stamp()<<"------Start read_robot_fifo--------"<<endl;
			int count;
			fifo_in.read(count);
			while(count--) {
				int type , data;
				fifo_in.read(type);
				fifo_in.read(data);
				update_robot(id , type , data);
			}
	}

	
	void environment:: env_process () {
			while(true) {
				wait();

				cout<<"@ "<<sc_time_stamp()<<"------Start env_process--------"<<endl;

				int robot_id;
				if(robot1_to_env.nb_read(robot_id)) {
					read_robot_fifo(robot_id , robot1_to_env);
				}
				if(robot2_to_env.nb_read(robot_id)) {
					read_robot_fifo(robot_id , robot2_to_env);
				}
				if(robot3_to_env.nb_read(robot_id)) {
					read_robot_fifo(robot_id , robot3_to_env);
				}
				if(robot4_to_env.nb_read(robot_id)) {
					read_robot_fifo(robot_id , robot4_to_env);
				}
				bool is_grid_crossing;
				for(int i = 1 ; i <= 4 ; i++) {
					is_grid_crossing = move_obstacle(i);
				}
				if(is_grid_crossing) {
					obstacle_path_map_pos++;
				}
				for(int i = 1 ; i <= 4 ; i++) {
					is_grid_crossing = move_robot(i);
					if(is_grid_crossing) {
						if(i == 1) {
							send_crossing_to_server(i , env_to_robot1);
						} else if(i == 2) {
							send_crossing_to_server(i , env_to_robot2);
						} else if(i == 3) {
							send_crossing_to_server(i , env_to_robot3);	
						} else if(i == 4) {
							send_crossing_to_server(i , env_to_robot4);
						}
					}
				}
				point_map_pos++;

				cout<<"/**===================================ENVIRONMENT LOG===================================**/"<<endl;
				log_grid_robot();
				cout<<"/**===================================ENVIRONMENT LOG===================================**/"<<endl<<endl<<endl;
			}
		}

#endif
