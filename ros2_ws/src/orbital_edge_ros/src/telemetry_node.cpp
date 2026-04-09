#include "rclcpp/rclcpp.hpp"
#include "orbital_edge/ephemeris_engine.hpp"
#include "orbital_edge_ros/msg/astronomical_telemetry.hpp"

using namespace std::chrono_literals;

namespace orbital_edge_ros {

class TelemetryNode : public rclcpp::Node {
public:
    TelemetryNode() : Node("astronomical_telemetry_node") {
        // Parametreleri yükle
        this->declare_parameter("veri_yolu", "/opt/orbital_edge/data");
        this->declare_parameter("enlem", 40.99);
        this->declare_parameter("boylam", 39.71);

        std::string veri_yolu = this->get_parameter("veri_yolu").as_string();
        m_enlem = this->get_parameter("enlem").as_double();
        m_boylam = this->get_parameter("boylam").as_double();

        // Motoru başlat
        m_engine = std::make_unique<orbital_edge::EphemerisEngine>(veri_yolu);

        // Yayıncıyı oluştur
        m_publisher = this->create_publisher<orbital_edge_ros::msg::AstronomicalTelemetry>("/astro/telemetry", 10);

        // Zamanlayıcıyı başlat (10Hz)
        m_timer = this->create_wall_timer(100ms, std::bind(&TelemetryNode::publish_telemetry, this));

        RCLCPP_INFO(this->get_logger(), "[OrbitalEdge] Telemetri dugumu baslatildi. Konum: %f, %f", m_enlem, m_boylam);
    }

private:
    void publish_telemetry() {
        auto msg = orbital_edge_ros::msg::AstronomicalTelemetry();
        msg.header.stamp = this->now();
        msg.header.frame_id = "celestial_frame";

        // Güneş verilerini al (Örnek)
        auto sun_data = m_engine->get_planet_pos(orbital_edge::Planets::SUN, m_enlem, m_boylam);

        msg.gezegen_adi = "Gunes";
        msg.boylam_derece = sun_data.zodiac_degree;
        msg.yukseklik_dagilim = sun_data.altitude;
        msg.azimut = sun_data.azimuth;
        msg.burc_adi = sun_data.sign;
        msg.gecerli = true;

        m_publisher->publish(msg);
    }

    std::unique_ptr<orbital_edge::EphemerisEngine> m_engine;
    rclcpp::Publisher<orbital_edge_ros::msg::AstronomicalTelemetry>::SharedPtr m_publisher;
    rclcpp::TimerBase::SharedPtr m_timer;
    double m_enlem, m_boylam;
};

} // namespace orbital_edge_ros

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<orbital_edge_ros::TelemetryNode>());
    rclcpp::shutdown();
    return 0;
}
