#ifndef POLYGON_BASE_REGULAR_POLYGON_HPP
#define POLYGON_BASE_REGULAR_POLYGON_HPP

namespace polygon_base
{
    class RegularPolygon
    {
        public:
            virtual void initialize(double side_length) = 0;
            virtual double area() = 0;
            //这里如果不给default关键字让其为默认析构函数会出现未定义行为
            //这个问题比较语法糖，没必要深入思考
            virtual ~RegularPolygon() = default;
        protected:
            RegularPolygon(){};
    };
}

#endif