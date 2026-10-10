#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "more_interfaces/msg/address_book.hpp"

using namespace std::chrono_literals;

class AddressBookPublisher : public rclcpp::Node{
    public:
        AddressBookPublisher():Node("address_book_publisher"){
            address_book_publisher_ = this -> create_publisher<more_interfaces::msg::AddressBook>("new_topic",10);

            //这里使用lambda函数去代替函数包装器，也是一种函数指针形式
            //这里lambda函数捕获了this指针——捕获类对象，用来调用类成员变量进行消息发布
            auto publish_msg = [this]() -> void{
                auto message = more_interfaces::msg::AddressBook();

                message.first_name = "John";
                message.last_name = "Doe";
                message.phone_number = "18729525092";
                message.phone_type = message.PHONE_TYPE_MOBILE;

                std::cout<<"Publishing Contact"<<std::endl;
                std::cout<<"First : "<<message.first_name<<" Last:"<<message.last_name<<std::endl;

                this -> address_book_publisher_ -> publish(message);
            };

            //创建定时器，定时器参数就是定时器时间间隔和要执行的函数指针(回调函数)
            timer_ = this -> create_wall_timer(1s,publish_msg);
        }
    
    private:
        rclcpp::Publisher<more_interfaces::msg::AddressBook>::SharedPtr address_book_publisher_;
        rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc , char* argv[]){
    rclcpp::init(argc,argv);

    auto node = std::make_shared<AddressBookPublisher>();

    rclcpp::spin(node);

    rclcpp::shutdown();

    return 0;
}