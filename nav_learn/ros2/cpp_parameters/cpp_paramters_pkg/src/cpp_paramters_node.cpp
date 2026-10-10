#include <chrono>
#include <functional>
#include <string>

#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

class MinimalParam : public rclcpp::Node{
    public:
        MinimalParam():Node("minimal_param_node"){
            this -> declare_parameter("my_parameter","world");

            timer_ = this -> create_wall_timer(100ms,std::bind(&MinimalParam::timer_callback,this));
        }
    

    private:
        rclcpp::TimerBase::SharedPtr timer_;

        void timer_callback(){
            std::string my_param = this -> get_parameter("my_parameter").as_string();

            RCLCPP_INFO(this -> get_logger(),"Hello %s!",my_param.c_str());

            std::vector<rclcpp::Parameter> all_new_paramters{rclcpp::Parameter("my_parameter","world")};

            this -> set_parameters(all_new_paramters);
        }
};

int main(int argc , char** argv){
    rclcpp::init(argc,argv);

    auto node = std::make_shared<MinimalParam>();

    rclcpp::spin(node);

    rclcpp::shutdown();

    return 0;
}