// 字符串和自定义类型的转换
// xml本质是字符串类型，当端口不是std::string需要将字符串解析为自定义类型
// 特化BT::convertFromString
#include "rclcpp/rclcpp.hpp"
#include "behaviortree_cpp/behavior_tree.h"

struct Position2D{
    double x;
    double y;
};

//实现一个将字符串转化为Position2D

namespace BT{
    template<>
    // 内联函数（相当于静态库）
    inline Position2D convertFromString(StringView str){
        // 我们期望由分号分隔实数
        auto parts = splitString(str,';');
        if(parts.size()!=2){
            throw RuntimeError("无效输入");
        }
        else{
            Position2D output;
            output.x = convertFromString<double>(parts[0]);
            output.y = convertFromString<double>(parts[1]);
            return output;
        }
    }
}

// 当后面xml出现"-1;3"这样的字符串并赋值给Position2D端口时，库会自动调用这个特化函数完成转换