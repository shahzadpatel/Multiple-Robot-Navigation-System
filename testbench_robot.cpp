#include<systemc.h>
#include<Library.h>
#include<Robot.h>
#include<Server.h> 

#include<Environment.h> 

SC_MODULE(test_bench) {

//FIFO
	sc_fifo<int> server_to_robot1;
    sc_fifo<int> server_to_robot2;
    sc_fifo<int> server_to_robot3;
    sc_fifo<int> server_to_robot4;


    sc_fifo<int> robot_to_server1;
    sc_fifo<int> robot_to_server2;
    sc_fifo<int> robot_to_server3;
    sc_fifo<int> robot_to_server4;


    sc_fifo<int> robot1_to_env;
    sc_fifo<int> robot2_to_env;
    sc_fifo<int> robot3_to_env;
    sc_fifo<int> robot4_to_env; 

    sc_fifo<int> env_to_robot1;
    sc_fifo<int> env_to_robot2;
    sc_fifo<int> env_to_robot3;
    sc_fifo<int> env_to_robot4;

 //SERVER

    sc_signal<bool> enable_server_to_robot1;
    sc_signal<bool> enable_server_to_robot2;
    sc_signal<bool> enable_server_to_robot3;
    sc_signal<bool> enable_server_to_robot4;

 //ROBOT

    sc_signal<bool> robot_enable_from_server;
	sc_signal<bool> robot_enable_from_env;

//ENVIRONMENT

	sc_signal<bool> clock;
	sc_signal<bool> enable_env_to_robot1;
	sc_signal<bool> enable_env_to_robot2;
	sc_signal<bool> enable_env_to_robot3;
	sc_signal<bool> enable_env_to_robot4; 



//MODULE 
	
	
	environment*env;
	server*ser;

	robot*rob1;
	robot*rob2;
	robot*rob3;
	robot*rob4;

	void clock_signal();

	SC_CTOR(test_bench){

		env = new environment("Enivronment Module");
		
		ser = new server("Server Module");

		rob1 = new robot("Robot 1", 1 );
		rob2 = new robot("Robot 1", 2 );
		rob3 = new robot("Robot 1", 3 );
		rob4 = new robot("Robot 1", 4 );


//signals from server to robot
		ser->server_to_robot1(server_to_robot1);
		rob1->server_to_robot(server_to_robot1);
		ser->server_to_robot2(server_to_robot2);
		rob2->server_to_robot(server_to_robot2);
		ser->server_to_robot3(server_to_robot3);
		rob3->server_to_robot(server_to_robot3);
		ser->server_to_robot4(server_to_robot4);
		rob4->server_to_robot(server_to_robot4);

		ser->enable_server_to_robot1(enable_server_to_robot1);
		rob1->robot_enable_from_server(enable_server_to_robot1);
		ser->enable_server_to_robot2(enable_server_to_robot2);
		rob2->robot_enable_from_server(enable_server_to_robot2);
		ser->enable_server_to_robot3(enable_server_to_robot3);
		rob3->robot_enable_from_server(enable_server_to_robot3);
		ser->enable_server_to_robot4(enable_server_to_robot4);
		rob4->robot_enable_from_server(enable_server_to_robot4);


//signals from robot to server
		 rob1->robot_to_server(robot_to_server1);
		 ser->robot_to_server1(robot_to_server1);
		  rob2->robot_to_server(robot_to_server2);
		 ser->robot_to_server2(robot_to_server2);
		  rob3->robot_to_server(robot_to_server3);
		 ser->robot_to_server3(robot_to_server3);
		  rob4->robot_to_server(robot_to_server4);
		 ser->robot_to_server4(robot_to_server4);


// signals from environment to robot

		 env->env_to_robot1(env_to_robot1);
		 rob1->env_to_robot(env_to_robot1);
		 env->env_to_robot2(env_to_robot2);
		 rob2->env_to_robot(env_to_robot2);
		 env->env_to_robot3(env_to_robot3);
		 rob3->env_to_robot(env_to_robot3);
		 env->env_to_robot4(env_to_robot4);
		 rob4->env_to_robot(env_to_robot4);

		 env->enable_env_to_robot1(enable_env_to_robot1);
		 rob1->robot_enable_from_env(enable_env_to_robot1);
		 env->enable_env_to_robot2(enable_env_to_robot2);
		 rob2->robot_enable_from_env(enable_env_to_robot2);
		 env->enable_env_to_robot3(enable_env_to_robot3);
		 rob3->robot_enable_from_env(enable_env_to_robot3);
		 env->enable_env_to_robot4(enable_env_to_robot4);
		 rob4->robot_enable_from_env(enable_env_to_robot4);


// signals from robot to environment

		 rob1-> robot_to_env(robot1_to_env);
		 env->robot1_to_env(robot1_to_env);
		 rob2-> robot_to_env(robot2_to_env);
		 env->robot2_to_env(robot2_to_env);
		 rob3-> robot_to_env(robot3_to_env);
		 env->robot3_to_env(robot3_to_env);
		 rob4-> robot_to_env(robot4_to_env);
		 env->robot4_to_env(robot4_to_env);


// Clock in Environment and Server
		 env->clock(clock);
		 ser->clock(clock);

SC_THREAD(clock_signal);

sc_fifo<int> server_to_robot1 (50) , env_to_robot1 (50) , robot_to_server1 (50) , robot1_to_env (50);
			sc_fifo<int> server_to_robot2 (50) , env_to_robot2 (50) , robot_to_server2 (50) , robot2_to_env (50);
			sc_fifo<int> server_to_robot3 (50) , env_to_robot3 (50) , robot_to_server3 (50) , robot3_to_env (50);
			sc_fifo<int> server_to_robot4 (50) , env_to_robot4 (50) , robot_to_server4 (50) , robot4_to_env (50);

		 
		}

	};


void test_bench::clock_signal() {
			while (true){
		        wait(0.5 , SC_MS);
		    	clock = false;
		        wait(0.5 , SC_MS);
		    	clock = true;
			}
		}


int sc_main(int argc , char* argv[]) {

	cout<<"@ "<<sc_time_stamp()<<"----------Start---------"<<endl<<endl<<endl;
	test_bench test_bench("Robot Navigation");

	cout<<"@ "<<sc_time_stamp()<<"----------Start Simulation---------"<<endl<<endl<<endl;
	sc_start(50000 , SC_MS);
	cout<<"@ "<<sc_time_stamp()<<"----------End Simulation---------"<<endl<<endl<<endl;
	return 0;
}
