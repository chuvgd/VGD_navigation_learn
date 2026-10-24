#include <memory>

#include "geometry_msgs/msg/transform_stamped.hpp"
#include "rclcpp/rclcpp.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/static_transform_broadcaster.h"

class StaticFramePublisher : public rclcpp::Node{
    public:
        explicit StaticFramePublisher(char* transformation[]):Node("static_broadcaster_publisher"){
            tf_static_broadcaster_ = std::make_shared<tf2_ros::StaticTransformBroadcaster>(this);

            //在构造函数直接进行相关静态转换的发布
            this -> make_transforms(transformation);
        }

    private:
        std::shared_ptr<tf2_ros::StaticTransformBroadcaster> tf_static_broadcaster_;
        void make_transforms(char* transfromation[]){
            geometry_msgs::msg::TransformStamped t;

            t.header.stamp = this->get_clock()->now();
            t.header.frame_id = "world";
            t.child_frame_id = transfromation[1];

            //atof()函数将字符串转换为双精度浮点数
            t.transform.translation.x = atof(transfromation[2]);
            t.transform.translation.y = atof(transfromation[3]);
            t.transform.translation.z = atof(transfromation[4]);
            tf2::Quaternion q;
            q.setRPY(
                atof(transfromation[5]),
                atof(transfromation[6]),
                atof(transfromation[7])
            );
            t.transform.rotation.x = q.x();
            t.transform.rotation.y = q.y();
            t.transform.rotation.z = q.z();
            t.transform.rotation.w = q.w();

            tf_static_broadcaster_ -> sendTransform(t);
        }
};

int main(int argc,char** argv){
    auto logger = rclcpp::get_logger("logger");

    if(argc != 8){
        RCLCPP_INFO(
            logger,"Invalid number of parameters\nusage:"
            "$ ros2 run learning_tf2_cpp static_broadcaster_publisher "
            "child_frame_name x y z roll pitch yaw");

            return 1;
    }

    //As the parent frame of the transform is 'world',it is necessary to check that the frame name passed is different
    if(strcmp(argv[1],"world") == 0){
        RCLCPP_INFO(logger,"Your static turtle name cannot be 'world'");
        return 1;
    }

    //Pass parameters and initialize node
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<StaticFramePublisher>(argv));
    rclcpp::shutdown();
    return 0;
}