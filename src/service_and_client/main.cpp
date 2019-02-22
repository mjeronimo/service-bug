// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <chrono>
#include <cinttypes>
#include <memory>
#include "example_interfaces/srv/add_two_ints.hpp"
#include "rclcpp/rclcpp.hpp"

#include <inttypes.h>
#include <memory>
#include "example_interfaces/srv/add_two_ints.hpp"
#include "rclcpp/rclcpp.hpp"

#include "std_msgs/msg/empty.hpp"
#include "std_srvs/srv/empty.hpp"

using AddTwoInts = example_interfaces::srv::AddTwoInts;

//int main(int argc, char * argv[])
void service_func()
{
  //rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("minimal_client");
  auto client = node->create_client<AddTwoInts>("add_two_ints");
  while (!client->wait_for_service(std::chrono::seconds(1))) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(node->get_logger(), "client interrupted while waiting for service to appear.");
      return; //  1;
    }
    RCLCPP_INFO(node->get_logger(), "waiting for service to appear...");
  }
  auto request = std::make_shared<AddTwoInts::Request>();
  request->a = 41;
  request->b = 1;
  auto result_future = client->async_send_request(request);

#if 0
  if (rclcpp::spin_until_future_complete(node, result_future) !=
    rclcpp::executor::FutureReturnCode::SUCCESS)
  {
    RCLCPP_ERROR(node->get_logger(), "service call failed :(");
    return 1;
  }
#else
    rclcpp::executor::FutureReturnCode status = rclcpp::executor::FutureReturnCode::TIMEOUT;
    do {
      status = rclcpp::spin_until_future_complete(node, result_future, std::chrono::milliseconds(500));
    } while (rclcpp::ok() && status != rclcpp::executor::FutureReturnCode::SUCCESS);
#endif

  auto result = result_future.get();
  RCLCPP_INFO(node->get_logger(), "result of %" PRId64 " + %" PRId64 " = %" PRId64,
    request->a, request->b, result->sum);
  //rclcpp::shutdown();
  //return 0;
}


rclcpp::Node::SharedPtr g_node = nullptr;

void handle_service(
  const std::shared_ptr<rmw_request_id_t> request_header,
  const std::shared_ptr<std_srvs::srv::Empty::Request> request,
  const std::shared_ptr<std_srvs::srv::Empty::Response> response)
{
  (void)request_header;
  (void)request;
  (void)response;
  RCLCPP_INFO(g_node->get_logger(), "service request");
  service_func();
}

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  g_node = rclcpp::Node::make_shared("test_service");
  auto server = g_node->create_service<std_srvs::srv::Empty>("callit", handle_service);
  rclcpp::spin(g_node);
  rclcpp::shutdown();
  g_node = nullptr;
  return 0;
}
