#include <iostream>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node{
    public:
    //构造函数，先构造父类有参构造函数，再初始化列表
        MinimalPublisher(std::string name):Node(name),count_(0){
            publisher_ = this -> create_publisher<std_msgs::msg::String>("topic",10);
            timer_ = this -> create_wall_timer(500ms , std::bind(&MinimalPublisher::timer_callback,this));
        }

    private:
        rclcpp::TimerBase::SharedPtr timer_;
        //共享指针对象，std::shared_ptr<rclcpp::TimerBase>
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
        //using rclcpp::Publisher<std_msgs::msg::String>::SharedPtr = std::shared_ptr<rclcpp::Publisher<std_msgs::msg::String>> 
        //模板类rclcpp::Publisher<std_msgs::msg::String>的一个智能指针对像
        size_t count_;

        void timer_callback(){
            auto message = std_msgs::msg::String();
            message.data = "Hello world!"+std::to_string(count_++);
            RCLCPP_INFO(this->get_logger(),"Publishing:'%s'",message.data.c_str());
            publisher_->publish(message);
        }
};

int main(int argc,char* argv[]){
    rclcpp::init(argc,argv);

    // MinimalPublisher* node = new MinimalPublisher("minimal_publisher"); 
    // auto node = std::make_shared<MinimalPublisher>("minimal_publisher");
    auto node = std::shared_ptr<MinimalPublisher>(new MinimalPublisher("minimal_publisher"));
    //std::shared_ptr<MinimalPublisher> node = std::make_shared<MinimalPublisher>()
    //等价于MinimalPublisher* node = new MinimalPublisher()
    //这里构造函数是无参构造函数，因此模板类的成员函数(shared_ptr())里面没有参数传入

    rclcpp::spin(node);

    rclcpp::shutdown();

    return 0;
}
