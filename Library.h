
#ifndef Libray_H
#define Library_H

#include<systemc.h>
#include <map>

struct coordinates {
    double x;
	double y;
};


std::map<int , coordinates> map_left_coordinates();
std::map<int , coordinates> map_right_coordinates();
std::map<int , int> map_north();
std::map<int , int> map_south();
std::map<int , int> map_east();
std::map<int , int>  map_west();
std::map<int , std::vector<int> > map_robot_path();
std::map<int , int> map_robot_status();
std::map<int , std::vector<int> > map_obstacle_path();
std::map<int , int> robot_direction();
std::map<int , int> robot_loc_grid();
std::map<int , coordinates> robot_loc_point();
std::map<int , int> obstacle_direction();
std::map<int , int> obstacle_loc_grid();
std::map<int , coordinates> obstacle_loc_point();
std::vector<double> grid_point_loc_robot();
std::vector<double> grid_point_loc_obstacle();
void value_print (int grid);
void log_grid_robot ();

std::map<int , coordinates> left_coordinates = map_left_coordinates();
std::map<int , coordinates> right_coordinates = map_right_coordinates();
std::map<int , int> north = map_north();
std::map<int , int> south = map_south();
std::map<int , int> east = map_east();
std::map<int , int> west = map_west();
std::map<int , std::vector<int> > robot_path = map_robot_path();
std::map<int , int> robot_status = map_robot_status();
std::map<int , std::vector<int> > obstacle_path = map_obstacle_path();
std::map<int , int> robot_dir = robot_direction();
std::map<int , int> robot_location_grid = robot_loc_grid();
std::map<int , coordinates> robot_location_point = robot_loc_point();
std::map<int , int> obstacle_dir = obstacle_direction();
std::map<int , int> obstacle_location_grid = obstacle_loc_grid();
std::map<int , coordinates> obstacle_location_point = obstacle_loc_point();
std::vector<double> grid_point_location_robot = grid_point_loc_robot();
std::vector<double> grid_point_location_obstacle = grid_point_loc_obstacle();



std::map<int , coordinates> map_left_coordinates () {
  	std::map<int , coordinates> map;
    int j=0;
    for(int i = 1 ; i <= 10 ; i++) {
        map[i] = {j++*5 , 8*5};
    }
    map[11] = {0*5 , 7*5};
    map[12] = {9*5 , 7*5};
    j=0;
    for(int i = 13 ; i <= 22 ; i++) {
        map[i] = {j++*5 , 6*5};
    }
    map[23] = {0*5 , 5*5};
    map[24] = {5*5 , 5*5};
    map[25] = {9*5 , 5*5};
    j=0;
    for(int i = 26 ; i <= 35 ; i++) {
        map[i] = {j++*5 , 4*5};
    }
    map[36] = {0*5 , 3*5};
    map[37] = {6*5 , 3*5};
    map[38] = {9*5 , 3*5};
    j=0;
    for(int i = 39 ; i <= 48 ; i++) {
        map[i] = {j++*5 , 2*5};
    }
    map[49] = {0*5 , 1*5};
    map[50] = {9*5 , 1*5};
    j=0;
    for(int i = 51 ; i <= 60 ; i++) {
        map[i] = {j++*5 , 0*5};
    }
  	return map;
}
std::map<int , coordinates> map_right_coordinates () {
  	std::map<int , coordinates> map;
  	int j=0;
    for(int i = 1 ; i <= 10 ; i++) {
        map[i] = {++j*5 , 9*5};
    }
    map[11] = {0*5 , 8*5};
    map[12] = {9*5 , 8*5};
    j=0;
    for(int i = 13 ; i <= 22 ; i++) {
        map[i] = {++j*5 , 7*5};
    }
    map[23] = {1*5 , 6*5};
    map[24] = {6*5 , 6*5};
    map[25] = {10*5 , 6*5};
    j=0;
    for(int i = 26 ; i <= 35 ; i++) {
        map[i] = {++j*5 , 5*5};
    }
    map[36] = {1*5 , 4*5};
    map[37] = {7*5 , 4*5};
    map[38] = {10*5 , 4*5};
    j=0;
    for(int i = 39 ; i <= 48 ; i++) {
        map[i] = {++j*5 , 3*5};
    }
    map[49] = {1*5 , 2*5};
    map[50] = {10*5 , 2*5};
    j=0;
    for(int i = 51 ; i <= 60 ; i++) {
        map[i] = {++j*5 , 1*5};
    }
  	return map;
}
std::map<int , int> map_north () {
  	std::map<int , int> map;
    for(int i = 1 ; i <= 10 ; i++) {
      	map[i] = -1;
    }
    map[11] = 1;
    map[12] = 10;
    map[13] = 11;
    for(int i = 14 ; i <= 21 ; i++) {
        map[i] = -1;
    }
    map[22] = 12;
    map[23] = 13;
    map[24] = 18;
    map[25] = 22;
    map[26] = 23;
    for(int i = 27 ; i <= 30 ; i++) {
        map[i] = -1;
    }
    map[31] = 24;
    for(int i = 32 ; i <= 34 ; i++) {
        map[i] = -1;
    }
    map[35] = 25;
    map[36] = 26;
    map[37] = 32;
    map[38] = 35;
    map[39] = 36;
    for(int i = 40 ; i <= 44 ; i++) {
        map[i] = -1;
    }
    map[45] = 37;
    for(int i = 46 ; i <= 47 ; i++) {
        map[i] = -1;
    }
    map[48] = 38;
    map[49] = 39;
    map[50] = 48;
    map[51] = 49;
    for(int i = 52 ; i <= 59 ; i++) {
        map[i] = -1;
    }
    map[60] = 50;
  	return map;
}
std::map<int , int> map_south () {
  	std::map<int , int> map;
    map[1] = 11;
  	for(int i = 2 ; i <= 9 ; i++) {
        map[i] = -1;
    }
    map[10] = 12;
    map[11] = 1;
    map[12] = 10;
    map[13] = 11;
    for(int i = 14 ; i <= 17 ; i++) {
        map[i] = -1;
    }
    map[18] = 24;
    for(int i = 19 ; i <= 21 ; i++) {
        map[i] = -1;
    }
    map[22] = 25;
    map[23] = 26;
    map[24] = 31;
    map[25] = 35;
    map[26] = 36;
    for(int i = 27 ; i <= 31 ; i++) {
        map[i] = -1;
    }
    map[32] = 37;
    for(int i = 33 ; i <= 34 ; i++) {
        map[i] = -1;
    }
    map[35] = 38;
    map[36] = 39;
    map[37] = 45;
    map[38] = 48;
    map[39] = 49;
    for(int i = 40 ; i <= 47 ; i++) {
        map[i] = -1;
    }
    map[48] = 50;
    map[49] = 51;
    map[50] = 60;
    for(int i = 51 ; i <= 60 ; i++) {
        map[i] = -1;
    }
  	return map;
}
std::map<int , int> map_east () {
  	std::map<int , int> map;
    map[1] = -1;
  	for(int i = 2 ; i <= 10 ; i++) {
        map[i] = i - 1;
    }
    map[11] = -1;
    map[12] = -1;
    map[13] = -1;
    for(int i = 14 ; i <= 22 ; i++) {
        map[i] = i - 1;
    }
    map[23] = -1;
    map[24] = -1;
    map[25] = -1;
    map[26] = -1;
    for(int i = 27 ; i <= 35 ; i++) {
        map[i] = i - 1;
    }
    map[36] = -1;
    map[37] = -1;
    map[38] = -1;
    map[39] = -1;
    for(int i = 40 ; i <= 48 ; i++) {
        map[i] = i - 1;
    }
    map[49] = -1;
    map[50] = -1;
    map[51] = -1;
    for(int i = 52 ; i <= 60 ; i++) {
        map[i] = i - 1;
    }
  	return map;
}
std::map<int , int> map_west () {
  	std::map<int , int> map;
    for(int i = 1 ; i <= 9 ; i++) {
        map[i] = i + 1;
    }
    map[10] = -1;
    map[11] = -1;
    map[12] = -1;
    for(int i = 13 ; i <= 21 ; i++) {
        map[i] = i + 1;
    }
    map[22] = -1;
    map[23] = -1;
    map[24] = -1;
    map[25] = -1;
    for(int i = 26 ; i <= 34 ; i++) {
        map[i] = i + 1;
    }
    map[35] = -1;
    map[36] = -1;
    map[37] = -1;
    map[38] = -1;
    for(int i = 39 ; i <= 47 ; i++) {
        map[i] = i + 1;
    }
    map[48] = -1;
    map[49] = -1;
    map[50] = -1;
    for(int i = 51 ; i <= 59 ; i++) {
        map[i] = i + 1;
    }
    map[60] = -1;
  	return map;
}
std::map<int , std::vector<int> > map_robot_path () {
    std::map<int , std::vector<int> > map;
    // Robot 1
    map[1].push_back(0);
    map[1].push_back(1);
    map[1].push_back(11);
    map[1].push_back(13);
    map[1].push_back(14);
    map[1].push_back(15);
    map[1].push_back(16);
    map[1].push_back(17);
    map[1].push_back(18);
    map[1].push_back(24);
    map[1].push_back(31);
    map[1].push_back(30);
    map[1].push_back(29);
    map[1].push_back(28);
    map[1].push_back(27);
    map[1].push_back(26);
    map[1].push_back(36);
    map[1].push_back(39);

    // Robot 2
    map[2].push_back(0);
    map[2].push_back(10);
    map[2].push_back(12);
    map[2].push_back(22);
    map[2].push_back(21);
    map[2].push_back(20);
    map[2].push_back(19);
    map[2].push_back(18);
    map[2].push_back(24);
    map[2].push_back(31);
    map[2].push_back(32);
    map[2].push_back(33);
    map[2].push_back(34);
    map[2].push_back(35);
    map[2].push_back(25);

    // Robot 3
    map[3].push_back(0);
    map[3].push_back(49);
    map[3].push_back(39);
    map[3].push_back(36);
    map[3].push_back(26);
    map[3].push_back(27);
    map[3].push_back(28);
    map[3].push_back(29);
    map[3].push_back(30);
    map[3].push_back(31);
    map[3].push_back(32);
    map[3].push_back(37);
    map[3].push_back(45);
    map[3].push_back(46);
    map[3].push_back(47);
    map[3].push_back(48);
    map[3].push_back(38);

    // Robot 4
    map[4].push_back(0);
    map[4].push_back(60);
    map[4].push_back(50);
    map[4].push_back(48);
    map[4].push_back(47);
    map[4].push_back(46);
    map[4].push_back(45);
    map[4].push_back(44);
    map[4].push_back(43);
    map[4].push_back(42);
    map[4].push_back(41);
    map[4].push_back(40);
    map[4].push_back(39);
    map[4].push_back(49);
    map[4].push_back(51);
    map[4].push_back(52);
    map[4].push_back(53);
    map[4].push_back(54);
    map[4].push_back(55);
    return map;
}
std::map<int , int> map_robot_status () {
    std::map<int , int> map;
    // Robot 1
    map[1] = 1;

    // Robot 2
    map[2] = 1;

    // Robot 3
    map[3] = 1;

    // Robot 4
    map[4] = 1;
    return map;
}
std::map<int , std::vector<int> > map_obstacle_path () {
    std::map<int , std::vector<int> > map;
    // Obstacle 1
    for(int i = 1 ; i <= 10 ; i++) {
        map[1].push_back(i);
    }
    map[1].push_back(12);
    for(int i = 22 ; i >= 13 ; i--) {
        map[1].push_back(i);
    }
    map[1].push_back(11);

    // Obstacle 2
    for(int i = 13 ; i <= 18 ; i++) {
        map[2].push_back(i);
    }
    map[2].push_back(24);
    for(int i = 31 ; i <= 35 ; i++) {
        map[2].push_back(i);
    }
    map[2].push_back(25);
    for(int i = 22 ; i >= 18 ; i--) {
        map[2].push_back(i);
    }
    map[2].push_back(24);
    for(int i = 31 ; i >= 26 ; i--) {
        map[2].push_back(i);
    }
    map[2].push_back(23);

    // Obstacle 3
    for(int i = 26 ; i <= 32 ; i++) {
        map[3].push_back(i);
    }
    map[3].push_back(37);
    for(int i = 45 ; i <= 48 ; i++) {
        map[3].push_back(i);
    }
    map[3].push_back(38);
    for(int i = 35 ; i >= 32 ; i--) {
        map[3].push_back(i);
    }
    map[3].push_back(37);
    for(int i = 45 ; i >= 39 ; i--) {
        map[3].push_back(i);
    }
    map[3].push_back(36);

    // Obstacle 4
    for(int i = 39 ; i <= 48 ; i++) {
        map[4].push_back(i);
    }
    map[4].push_back(50);
    for(int i = 60 ; i >= 51 ; i--) {
        map[4].push_back(i);
    }
    map[4].push_back(49);
    return map;
}
std::map<int , int> robot_direction () {
    std::map<int , int> map;
    for(int i = 1 ; i <= 4 ; i++) {
        map[i] = 0;
    }
    return map;
}
std::map<int , int> robot_loc_grid () {
    std::map<int , int> map;
    for(int i = 1 ; i <= 4 ; i++) {
        map[i] = 0;
    }
    return map;
}
std::map<int , coordinates> robot_loc_point () {
    std::map<int , coordinates> map;
    for(int i = 1 ; i <= 4 ; i++) {
        map[i] = {0 , 0};
    }
    return map;
}
std::map<int , int> obstacle_direction () {
    std::map<int , int> map;
    for(int i = 1 ; i <= 4 ; i++) {
        map[i] = 0;
    }
    return map;
}
std::map<int , int> obstacle_loc_grid () {
    std::map<int , int> map;
    for(int i = 1 ; i <= 4 ; i++) {
        map[i] = 0;
    }
    return map;
}
std::map<int , coordinates> obstacle_loc_point () {
    std::map<int , coordinates> map;
    for(int i = 1 ; i <= 4 ; i++) {
        map[i] = {0 , 0};
    }
    return map;
}
std::vector<double> grid_point_loc_robot () {
    std::vector<double> _v;
    for(int i = 1 ; i <= 1000*5 ; i++) {
        _v.push_back(0.002*i);
    }
    return _v;
}
std::vector<double> grid_point_loc_obstacle () {
    std::vector<double> _v;
    for(int i = 1 ; i <= 1000*5 ; i++) {
        _v.push_back(0.005*i);
    }
    return _v;
}
void value_print (int grid) {
    for(int j = 1 ; j <= 4 ; j++) {
        if(robot_location_grid[j] == grid) {
            cout<<"R"<<j<<" ";
            return;
        } else if(obstacle_location_grid[j] == grid) {
            cout<<"O"<<j<<" ";
            return;
        }
    }
    cout<<" - ";
}
void log_grid_robot () {
    for(int i = 1 ; i <= 10 ; i++) {
        value_print(i);
    }
    cout<<endl;
    value_print(11);
    for(int i = 1 ; i <= 8 ; i++) {
        cout<<" X ";
    }
    value_print(12);
    cout<<endl;
    for(int i = 13 ; i <= 22 ; i++) {
        value_print(i);
    }
    cout<<endl;
    value_print(23);
    for(int i = 1 ; i <= 4 ; i++) {
        cout<<" X ";
    }
    value_print(24);
    for(int i = 1 ; i <= 3 ; i++) {
        cout<<" X ";
    }
    value_print(25);
    cout<<endl;
    for(int i = 26 ; i <= 35 ; i++) {
        value_print(i);
    }
    cout<<endl;
    value_print(36);
    for(int i = 1 ; i <= 5 ; i++) {
        cout<<" X ";
    }
    value_print(37);
    for(int i = 1 ; i <= 2 ; i++) {
        cout<<" X ";
    }
    value_print(38);
    cout<<endl;
    for(int i = 39 ; i <= 48 ; i++) {
        value_print(i);
    }
    cout<<endl;
    value_print(49);
    for(int i = 1 ; i <= 8 ; i++) {
        cout<<" X ";
    }
    value_print(50);
    cout<<endl;
    for(int i = 51 ; i <= 60 ; i++) {
        value_print(i);
    }
    cout<<endl;
}

#endif
