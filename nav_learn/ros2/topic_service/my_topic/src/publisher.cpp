#include <iostream>
#include <memory>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/msg/num.hpp"

using namespace std::chrono_literals;

class Publisher : public rclcpp::Node{
    public:
        Publisher(std::string name):Node(name),count_(0){
            publisher_ = this -> create_publisher<tutorial_interfaces::msg::Num>("my_topic",10);
            timer_ = this -> create_wall_timer(500ms,std::bind(&Publisher::call_back,this));
        }

    private:
        size_t count_;
        rclcpp::TimerBase::SharedPtr timer_;
        rclcpp::Publisher<tutorial_interfaces::msg::Num>::SharedPtr publisher_;
        void call_back(){
            auto message = tutorial_interfaces::msg::Num();
            message.num = this -> count_++;
            RCLCPP_INFO(this->get_logger(),"Publishing: %ld",message.num);
            publisher_ -> publish(message);
        };
};

int main(int argc,char** argv){
    rclcpp::init(argc,argv);

    auto node = std::make_shared<Publisher>("VGD");

    rclcpp::spin(node);

    rclcpp::shutdown();

    return 0;
}

