#ifndef Robot_H
#define Robot_H

# include<systemc.h>

SC_MODULE(robot){
	
	sc_in<bool> robot_enable_from_server;
	sc_in<bool> robot_enable_from_env;
	sc_fifo_in<int> server_to_robot;
	sc_fifo_in<int> env_to_robot;


	sc_fifo_out<int> robot_to_server;
	sc_fifo_out<int> robot_to_env;
	
	int id;
	
	

	void relay_to_server(int type, int data);
	void relay_to_env(int type, int data);
	void robot_process();


	SC_HAS_PROCESS(robot);
		robot(sc_module_name name , int robot_id) : sc_module(name) {

	
	SC_THREAD(robot_process);

	sensitive<< robot_enable_from_server;
	sensitive<< robot_enable_from_env;
	
	id = robot_id;
	
	}
	
};

void robot::relay_to_server(int type, int data){
	cout<<"@ "<<sc_time_stamp()<<"------Start Relay to Server--------"<<endl;

			wait(10 , SC_NS);
			robot_to_server.write(type);
			robot_to_server.write(data);
			wait(10 , SC_NS);

			cout<<"/**===================================ROBOT LOG===================================**/"<<endl;
			// cout<<"       Obstacle Signal To Server : "<<_isObstacleToServer<<endl;
			// cout<<"       Boundary Signal To Server : "<<_isBoundaryToServer<<endl;
			// cout<<"       Delta Crossing Signal To Server : "<<_isDeltaCrossingToServer<<endl;
			cout<<"/**===================================ROBOT LOG===================================**/"<<endl;

			cout<<"@ "<<sc_time_stamp()<<"------End Relay to Server--------"<<endl<<endl<<endl;
}

void robot::relay_to_env(int type, int data){
	cout<<"@ "<<sc_time_stamp()<<"------Start _relayToEnv--------"<<endl;

			wait(10 , SC_NS);
			robot_to_env.write(type);
			robot_to_env.write(data);
			wait(10 , SC_NS);

			cout<<"/**===================================ROBOT LOG===================================**/"<<endl;
			// cout<<"       Start Signal To Environment : "<<_startFromServer.read()<<endl;
			// cout<<"       Stop Signal To Environment : "<<_stopFromServer.read()<<endl;
			cout<<"/**===================================ROBOT LOG===================================**/"<<endl;

			cout<<"@ "<<sc_time_stamp()<<"------End _relayToEnv--------"<<endl<<endl<<endl;
}

void robot::robot_process () {
			while(true) {
				wait();
				int robot_id;
				if(server_to_robot.nb_read(robot_id)) {
					if(robot_id != id) {
						// not this robot
					}
					int count;
					server_to_robot.read(count);
					if(robot_enable_from_server) {
						robot_to_env.write(id);
						robot_to_env.write(count);
						
					} else {
						robot_to_server.write(id);
						robot_to_server.write(count);
					}
					while(count--) {
						int type , data;
						server_to_robot.read(type);
						server_to_robot.read(data);
						if(robot_enable_from_server) {
							relay_to_env(type , data);
							
						} else {
							relay_to_server(type , data);
						}
					}
				}
			}
		}

		#endif