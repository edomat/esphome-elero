#pragma once

#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "esphome/components/cover/cover.h"
#include "esphome/components/elero/elero.h"

namespace esphome {
namespace elero {

class EleroCover : public cover::Cover, public Component {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;
  float get_setup_priority() const override;
  
  cover::CoverTraits get_traits() override;
  
  void set_elero_parent(Elero *parent) { this->parent_ = parent; }
  void set_blind_address(uint32_t address) { this->command_.blind_addr = address; }
  void set_channel(uint8_t channel) { this->command_.channel = channel; }
  void set_remote_address(uint32_t remote) { this->command_.remote_addr = remote; }
  void set_payload_1(uint8_t payload) { this->command_.payload[0] = payload; }
  void set_payload_2(uint8_t payload) { this->command_.payload[1] = payload; }
  void set_hop(uint8_t hop) { this->command_.hop = hop; }
  void set_pckinf_1(uint8_t pckinf) { this->command_.pck_inf[0] = pckinf; }
  void set_pckinf_2(uint8_t pckinf) { this->command_.pck_inf[1] = pckinf; }
  void set_command_up(uint8_t cmd) { this->command_up_ = cmd; }
  void set_command_down(uint8_t cmd) { this->command_down_ = cmd; }
  void set_command_stop(uint8_t cmd) { this->command_stop_ = cmd; }
  void set_command_check(uint8_t cmd) { this->command_check_ = cmd; }
  void set_poll_offset(uint32_t offset) { this->poll_offset_ = offset; }
  uint32_t get_blind_address() { return this->command_.blind_addr; }
  void set_rx_state(uint8_t state);
  
 protected:
  void control(const cover::CoverCall &call) override;
  void increase_counter();
  void send_command(uint8_t command);

  t_elero_command command_ = {
    .counter = 1,
  };
  Elero *parent_;
  uint32_t last_poll_{0};
  uint32_t poll_offset_{0};
  uint32_t movement_start_{0};
  uint8_t command_up_{0x20};
  uint8_t command_down_{0x40};
  uint8_t command_check_{0x00};
  uint8_t command_stop_{0x10};
};

} // namespace elero
} // namespace esphome

