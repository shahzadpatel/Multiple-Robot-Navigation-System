#ifndef Server.H
#define Server.H



#include <systemc.h>

 

//template <class data_size>

SC_MODULE(server) {

 // Inputs
    sc_in<bool> clock;
    sc_fifo_in<int> robot_to_server1;
    sc_fifo_in<int> robot_to_server2;
    sc_fifo_in<int> robot_to_server3;
    sc_fifo_in<int> robot_to_server4;

    // Outputs
    sc_out<bool> enable_server_to_robot1;
    sc_out<bool> enable_server_to_robot2;
    sc_out<bool> enable_server_to_robot3;
    sc_out<bool> enable_server_to_robot4;

    sc_fifo_out<int> server_to_robot1;
    sc_fifo_out<int> server_to_robot2;
    sc_fifo_out<int> server_to_robot3;
    sc_fifo_out<int> server_to_robot4;


    sc_time t1;
    sc_time t2;
    sc_time t3;
    sc_time t4;
    sc_event init_robot_event;

             bool set_priority(int id1 , int id2);
             bool check_crossing(int id);
             void enable_robot(int id);
             void send_stop_to(int id, sc_fifo_out<int> fifo_out);
             void send_next_grid_to(int id, sc_fifo_out<int> fifo_out);
             void save_status(int id , int status);
             void init_robot_process();
             void read_robot_fifo(int id , sc_fifo_in<int> fifo_in , sc_fifo_out<int> fifo_out);
             void server_process ();

           
 	
            
  SC_CTOR(server){

  
  SC_THREAD(server_process);
      sensitive<<clock.pos();

      SC_THREAD(init_robot_process);

      sc_time t1(1 , SC_SEC);
      sc_time t2(5 , SC_SEC);
      sc_time t3(7 , SC_SEC);
      sc_time t4(2 , SC_SEC);
  
  }
  
};


bool server:: set_priority (int id1 , int id2) {
      if(id1 > id2) {
        if(id2 == 1) {
          send_stop_to(id2 , server_to_robot1); // id2 will stop at the crossing
        } else if(id2 == 2) {
          send_stop_to(id2 , server_to_robot2); // id2 will stop at the crossing
        } else if(id2 == 3) {
          send_stop_to(id2 , server_to_robot3); // id2 will stop at the crossing
        } else if(id2 == 4) {
          send_stop_to(id2 , server_to_robot4); // id2 will stop at the crossing
        }
        return false;
      }
      cout<<"/**===================================SERVER LOG===================================**/"<<endl;
      // cout<<"       Start Signal To Robot : "<<toStart<<endl;
      // cout<<"       Current Grid : "<<_robots[0].range(5 , 0)<<endl;
      // cout<<"       Next Grid : "<<_robots[0].range(11 , 6)<<endl;
      // cout<<"       State : "<<_robots[0].range(12 , 12)<<endl;
      cout<<"/**===================================SERVER LOG===================================**/"<<endl<<endl<<endl;
      return true;
    }
bool server:: check_crossing (int id) {
      if(robot_path[id].size() <= 1) {
        robot_path[id].erase(robot_path[id].begin());
        cout<<"ROBOT REACHED DESTINATION";
        return false;
      }
      int currentGrid = robot_path[id].front();
      int nextGrid = robot_path[id][1];
      for(int i = 1 ; i <= 4 ; i++) {
        if(i != id && robot_path[i][0] == nextGrid && set_priority(id , i)) {
          return false;
        }
      }
      for(int i = 1 ; i <= 4 ; i++) {
        if(i != id && robot_status[i] == 0 && robot_path[i][1] == currentGrid) {
          robot_path[i].erase(robot_path[i].begin());
         if(i == 1) {
            send_next_grid_to(i , server_to_robot1);
          } else if(i == 2) {
            send_next_grid_to(i , server_to_robot2);
          } else if(i == 3) {
            send_next_grid_to(i , server_to_robot3); 
          } else if(i == 4) {
            send_next_grid_to(i , server_to_robot4);
          }
          break;
        }
      }
      cout<<"/**===================================SERVER LOG===================================**/"<<endl;
      // cout<<"       Start Signal To Robot : "<<toStart<<endl;
      // cout<<"       Current Grid : "<<_robots[0].range(5 , 0)<<endl;
      // cout<<"       Next Grid : "<<_robots[0].range(11 , 6)<<endl;
      // cout<<"       State : "<<_robots[0].range(12 , 12)<<endl;
      cout<<"/**===================================SERVER LOG===================================**/"<<endl<<endl<<endl;
      return true;
    }
    void server:: enable_robot (int id) {
      enable_server_to_robot1.write(false);
      enable_server_to_robot2.write(false);
      enable_server_to_robot3.write(false);
      enable_server_to_robot4.write(false);
      wait(10 , SC_NS);
      switch(id) {
        case 1 : 
          enable_server_to_robot1.write(true);
          break;
        case 2 : 
          enable_server_to_robot2.write(true);
          break;
        case 3 : 
          enable_server_to_robot3.write(true);
          
          break;
        case 4 : 
          enable_server_to_robot4.write(true);
          break;
      }
      wait(10 , SC_NS);
      enable_server_to_robot1.write(false);
      enable_server_to_robot2.write(false);
      enable_server_to_robot3.write(false);
      enable_server_to_robot4.write(false);
    }
    void server:: send_stop_to(int id, sc_fifo_out<int> fifo_out) {
      cout<<"@ "<<sc_time_stamp()<<"------Start _sendStopTo--------"<<endl;

      fifo_out.write(id);
      fifo_out.write(1); // count
      fifo_out.write(0); // status signal
      fifo_out.write(0); // START
      enable_robot(id);
      save_status(id , 0);

      cout<<"/**===================================SERVER LOG===================================**/"<<endl;
      // cout<<"       Start Signal To Robot : "<<toStart<<endl;
      // cout<<"       Current Grid : "<<_robots[0].range(5 , 0)<<endl;
      // cout<<"       Next Grid : "<<_robots[0].range(11 , 6)<<endl;
      // cout<<"       State : "<<_robots[0].range(12 , 12)<<endl;
      cout<<"/**===================================SERVER LOG===================================**/"<<endl<<endl<<endl;
    }
    void server::send_next_grid_to (int id, sc_fifo_out<int> fifo_out) {
      cout<<"@ "<<sc_time_stamp()<<"------Start _sendNextGridTo--------"<<endl;
      robot_path[id].erase(robot_path[id].begin());
      fifo_out.write(id);
      fifo_out.write(2); // count
      fifo_out.write(0); // status signal
      fifo_out.write(1); // START
      fifo_out.write(1); // path signal
      fifo_out.write(robot_path[id].front());
      enable_robot(id);
      save_status(id , 1);

      cout<<"/**===================================SERVER LOG===================================**/"<<endl;
      // cout<<"       Start Signal To Robot : "<<toStart<<endl;
      // cout<<"       Current Grid : "<<_robots[0].range(5 , 0)<<endl;
      // cout<<"       Next Grid : "<<_robots[0].range(11 , 6)<<endl;
      // cout<<"       State : "<<_robots[0].range(12 , 12)<<endl;
      cout<<"/**===================================SERVER LOG===================================**/"<<endl<<endl<<endl;
    }
    void server::save_status (int id , int status) {
      robot_status[id] = status;
    }
    void server::init_robot_process () {
     while(true) {
        wait(init_robot_event);
        cout<<"@ "<<sc_time_stamp()<<"------Start _robotInitProcess--------"<<endl;

        send_next_grid_to(1 , server_to_robot1); // R1 start at 1sec
        save_status(1 , 1);

        cout<<"/**===================================SERVER LOG===================================**/"<<endl;
        // cout<<"       Start Signal To Robot : "<<toStart<<endl;
        // cout<<"       Current Grid : "<<_robots[0].range(5 , 0)<<endl;
        // cout<<"       Next Grid : "<<_robots[0].range(11 , 6)<<endl;
        // cout<<"       State : "<<_robots[0].range(12 , 12)<<endl;
        cout<<"/**===================================SERVER LOG===================================**/"<<endl<<endl<<endl;

        wait(init_robot_event);
        cout<<"@ "<<sc_time_stamp()<<"------Start _robotInitProcess--------"<<endl;

        send_next_grid_to(4 , server_to_robot4); // R4 starts at 2sec
        save_status(4 , 1);

        cout<<"/**===================================SERVER LOG===================================**/"<<endl;
        // cout<<"       Start Signal To Robot : "<<toStart<<endl;
        // cout<<"       Current Grid : "<<_robots[0].range(5 , 0)<<endl;
        // cout<<"       Next Grid : "<<_robots[0].range(11 , 6)<<endl;
        // cout<<"       State : "<<_robots[0].range(12 , 12)<<endl;
        cout<<"/**===================================SERVER LOG===================================**/"<<endl<<endl<<endl;

        wait(init_robot_event);
        cout<<"@ "<<sc_time_stamp()<<"------Start _robotInitProcess--------"<<endl;

        send_next_grid_to(3 , server_to_robot3); // R3 starts at 5sec
        save_status(3 , 1);

        cout<<"/**===================================SERVER LOG===================================**/"<<endl;
        // cout<<"       Start Signal To Robot : "<<toStart<<endl;
        // cout<<"       Current Grid : "<<_robots[0].range(5 , 0)<<endl;
        // cout<<"       Next Grid : "<<_robots[0].range(11 , 6)<<endl;
        // cout<<"       State : "<<_robots[0].range(12 , 12)<<endl;
        cout<<"/**===================================SERVER LOG===================================**/"<<endl<<endl<<endl;

        wait(init_robot_event);
        cout<<"@ "<<sc_time_stamp()<<"------Start _robotInitProcess--------"<<endl;

        send_next_grid_to(2 , server_to_robot2); // R2 starts at 7sec
        save_status(2 , 1);

        cout<<"/**===================================SERVER LOG===================================**/"<<endl;
        // cout<<"       Start Signal To Robot : "<<toStart<<endl;
        // cout<<"       Current Grid : "<<_robots[0].range(5 , 0)<<endl;
        // cout<<"       Next Grid : "<<_robots[0].ran  ge(11 , 6)<<endl;
        // cout<<"       State : "<<_robots[0].range(12 , 12)<<endl;
        cout<<"/**===================================SERVER LOG===================================**/"<<endl<<endl<<endl;
        wait(init_robot_event);
      }
    }



    void server::read_robot_fifo (int id , sc_fifo_in<int> fifo_in , sc_fifo_out<int> fifo_out) {
      cout<<"@ "<<sc_time_stamp()<<"------Start _readRobotFifo--------"<<endl;

      int count , type , data;
      fifo_in.read(count);
      while(count--) {
        int type , data;
        fifo_in.read(type);
        fifo_in.read(data);
        switch(data) {
          case 0 : // STOP
            save_status(id , 0);
            break;
          case 1 : // START
            save_status(id , 1);
            break;
          case 2 : // CROSSING
            if(check_crossing(id)) {
              send_stop_to(id , fifo_out);
            } else {
              send_next_grid_to(id , fifo_out);
            }
            break;
          default:
            cout<<"WRONG DATA INPUT ON SERVER";
            break;
        }
      } 
    }

    void server::server_process () {
      while(true) {
        cout<<"@ "<<sc_time_stamp()<<"------Start _serverProcess--------"<<endl;

        if(sc_time_stamp() == t1 || sc_time_stamp() == t2 || sc_time_stamp() == t3 || sc_time_stamp() == t4) {
          init_robot_event.notify();
        }
        int robot_id;
        if(robot_to_server1.nb_read(robot_id)) {
          read_robot_fifo(robot_id , robot_to_server1 , server_to_robot1);
        }
        if(robot_to_server2.nb_read(robot_id)) {
          read_robot_fifo(robot_id , robot_to_server2 , server_to_robot2);
        }
        if(robot_to_server3.nb_read(robot_id)) {
          read_robot_fifo(robot_id , robot_to_server3 , server_to_robot3);
        }
        if(robot_to_server4.nb_read(robot_id)) {
          read_robot_fifo(robot_id , robot_to_server4 , server_to_robot4);
        }

        cout<<"/**===================================SERVER LOG===================================**/"<<endl;

        cout<<"/**===================================SERVER LOG===================================**/"<<endl<<endl<<endl;

        wait();
      }
    }
#endif