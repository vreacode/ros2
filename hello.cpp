/*
需求：编写第一个小程序，控制机器狗打招呼
流程：
  1.创建发布对象
  2.创建定时器
  3.定时器中，调用发布对象发布指令。

*/

//包含头文件
#include "rclcpp/rclcpp.hpp"
#include "unitree_api/msg/request.hpp"

using namespace std::chrono_literals;
//自定义节点类：
class HelloWorld : public rclcpp::Node{
public:
    HelloWorld(): Node("helloworld"){
        RCLCPP_INFO(this->get_logger(), "HelloWorld创建！");

        // 1.创建发布对象
        pub_ = this->create_publisher<unitree_api::msg::Request>("/api/sport/request",10);
        // 2.创建定时器
        timer_ = this->create_wall_timer(1s,std::bind(&HelloWorld::on_timer,this));
        // 3.定时器中，调用发布对象发布指令
      }
  private:
      rclcpp::Publisher<unitree_api::msg::Request>::SharedPtr pub_;
      rclcpp::TimerBase::SharedPtr timer_;
      void on_timer(){
        unitree_api::msg::Request request;
        request.header.identity.api_id = 1016;//打招呼的协议码

        pub_->publish(request);//发布

      }
    
  };
  

int main(int argc,char * argv[]){
  //初始化ros客户端；
  rclcpp::init(argc,argv);
  //调用spin函数，并传入节点对象指针。

  rclcpp::spin(std::make_shared<HelloWorld>());
  //释放资源
  rclcpp::shutdown();

  return 0;
}