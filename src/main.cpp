#include <uWS/uWS.h>
#include <iostream>
#include "json.hpp"
#include "PID.h"
#include <math.h>
#include <vector>
#include <algorithm>

// for convenience
using json = nlohmann::json;

using namespace std;


// For converting back and forth between radians and degrees.
constexpr double pi() { return M_PI; }
double deg2rad(double x) { return x * pi() / 180; }
double rad2deg(double x) { return x * 180 / pi(); }

// Checks if the SocketIO event has JSON data.
// If there is data the JSON object in string format will be returned,
// else the empty string "" will be returned.
std::string hasData(std::string s) {
  auto found_null = s.find("null");
  auto b1 = s.find_first_of("[");
  auto b2 = s.find_last_of("]");
  if (found_null != std::string::npos) {
    return "";
  }
  else if (b1 != std::string::npos && b2 != std::string::npos) {
    return s.substr(b1, b2 - b1 + 1);
  }
  return "";
}

int main()
{
  uWS::Hub h;
  PID pid_steer;
  PID pid_speed;
  // tested with manual values from P~=1 to 0.004, I ~= 0.001 to 0.00005, D ~=1 to 6
  // Initialize PID with P = 0.1, I = 0.0001, D = 4.0
  pid_steer.Init(0.1,0.0001,4);
  pid_speed.Init(0.6,0,0);
  //Desired Speed
  double desired_speed=45;
  
  // TODO: Initialize the pid variable.
  h.onMessage([&pid_steer,&pid_speed,&desired_speed](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length, uWS::OpCode opCode) {
    // "42" at the start of the message means there's a websocket message event.
    // The 4 signifies a websocket message
    // The 2 signifies a websocket event
    if (length && length > 2 && data[0] == '4' && data[1] == '2')
    {
      auto s = hasData(std::string(data).substr(0, length));
      if (s != "") {
        auto j = json::parse(s);
        std::string event = j[0].get<std::string>();
        if (event == "telemetry") {
          // j[1] is the data JSON object
          double steer_cte = std::stod(j[1]["cte"].get<std::string>());
          double speed = std::stod(j[1]["speed"].get<std::string>());
          double angle = std::stod(j[1]["steering_angle"].get<std::string>());
          
          /* PID Controller for steering */
          double steer_value;
          // Update PID values
          pid_steer.UpdateErrorPID(steer_cte);
          // PID equation
          steer_value = -pid_steer.Kp*pid_steer.p_error - pid_steer.Kd*pid_steer.d_error -
           pid_steer.Ki*pid_steer.i_error;
          // Normalizing steering value to -1 to 1
          steer_value = std::max(std::min(1.0, steer_value), -1.0);
          // DEBUG
          std::cout << "CTE (STEERING): " << steer_cte <<  endl;

          json msgJson;
          msgJson["steering_angle"] = steer_value;

          /* P Controller for speed */
          double speed_cte = desired_speed - speed;
          // Update P value
          pid_speed.UpdateErrorP(speed_cte);
          // Calculate Throttle using P Controller and adjust
          // it based on steering angle, more angle less throttle
          double throttle =
          (pid_speed.Kp*pid_speed.p_error)/(1+abs(angle*6));

         // cout<<"Throttle:\t"<<throttle<<endl;
         //Normalize throttle
          throttle = max(-1.0, min(1.0, throttle));

          msgJson["throttle"] =throttle;

          // Sending data to socket
          auto msg = "42[\"steer\"," + msgJson.dump() + "]";
          //std::cout << msg << std::endl;
          ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
          
        }
      } else {
        // Manual driving
        std::string msg = "42[\"manual\",{}]";
        ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
      }
    }
  });

  // We don't need this since we're not using HTTP but if it's removed the program
  // doesn't compile :-(
  h.onHttpRequest([](uWS::HttpResponse *res, uWS::HttpRequest req, char *data, size_t, size_t) {
    const std::string s = "<h1>Hello world!</h1>";
    if (req.getUrl().valueLength == 1)
    {
      res->end(s.data(), s.length());
    }
    else
    {
      // i guess this should be done more gracefully?
      res->end(nullptr, 0);
    }
  });

  h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
    std::cout << "Connected!!!" << std::endl;
  });

  h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code, char *message, size_t length) {
    ws.close();
    std::cout << "Disconnected" << std::endl;
  });

  int port = 4567;
  if (h.listen(port))
  {
    std::cout << "Listening to port " << port << std::endl;
  }
  else
  {
    std::cerr << "Failed to listen to port" << std::endl;
    return -1;
  }
  h.run();
}
