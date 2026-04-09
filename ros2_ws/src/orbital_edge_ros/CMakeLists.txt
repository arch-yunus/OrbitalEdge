cmake_minimum_required(VERSION 3.8)
project(orbital_edge_ros)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Bulunması gereken paketler
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# Özel mesajları dahil et
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/AstronomicalTelemetry.msg"
  DEPENDENCIES std_msgs
)

# OrbitalEdge kütüphanesini bul (Daha önce kurduğumuz varsayılıyor veya manuel yol ekleniyor)
# find_package(orbital_edge REQUIRED)
# Manuel include (Eğer kurulu değilse geçici olarak proje kökünden alıyoruz)
include_directories(../../core/include)

# Yürütülebilir dosyayı oluştur
add_executable(telemetry_node src/telemetry_node.cpp)
ament_target_dependencies(telemetry_node rclcpp std_msgs)
# rosidl_target_interfaces(telemetry_node ${PROJECT_NAME} "rosidl_typesupport_cpp")

install(TARGETS
  telemetry_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
