#include "rclcpp/rclcpp.hpp"

class ParamServerNode : public rclcpp::Node{
    public:
        ParamServerNode() : Node("ros2_Param_demo_node"){
            //声明参数并设置默认值（强制声明机制）
            this -> declare_parameter<int>("robot_speed",50);
            this -> declare_parameter<double>("pid_kp",2.5);
            this -> declare_parameter<std::string>("device_name","lidar_sensor");
            this -> declare_parameter<bool>("enable_filter",true);

            //注册参数动态回调（参数修改实时触发）
            //对于回调函数，其实就是在实际参数注入时，作为函数指针传入进行调用，实现“回头调用”的解耦
            param_callback_handle_ = this -> add_on_set_parameters_callback(std::bind(&ParamServerNode::paramCallback,this,std::placeholders::_1));

            RCLCPP_INFO(this -> get_logger(),"ROS2参数服务节点启动成功!");
            printParamValue();
        }

    private: 
        rclcpp::node_interfaces::OnSetParametersCallbackHandle::SharedPtr param_callback_handle_;

        //参数变更回调函数
        rcl_interfaces::msg::SetParametersResult paramCallback(const std::vector<rclcpp::Parameter>& params){
            rcl_interfaces::msg::SetParametersResult result;
            result.successful = true;

            for(const auto& param : params){
                RCLCPP_INFO(this -> get_logger(),"参数更新:%s = %s",param.get_name().c_str(),param.value_to_string().c_str());
            }

            return result;
        }

        //读取并打印所有参数
        void printParamValue(){
            //这里其实就是获取参数然后存储在变量中进行后续使用
            int speed = this -> get_parameter("robot_speed").as_int();
            double kp = this -> get_parameter("pid_kp").as_double();
            std::string device = this -> get_parameter("device_name").as_string();
            bool filter = this -> get_parameter("enable_filter").as_bool();

            RCLCPP_INFO(this -> get_logger(),"机器人速度:%d",speed);
            RCLCPP_INFO(this -> get_logger(),"PID kp:%.2f",kp);
            RCLCPP_INFO(this -> get_logger(),"设备名称:%s",device.c_str());
            RCLCPP_INFO(this -> get_logger(),"滤波使用:%d",filter);
        }
};

int main(int argc,char** argv){
    rclcpp::init(argc,argv);

    auto node = std::make_shared<ParamServerNode>();

    rclcpp::spin(node);

    rclcpp::shutdown();

    return 0;
}