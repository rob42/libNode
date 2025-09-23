#ifndef ZENOHNODE_H
#define ZENOHNODE_H

#include <Arduino.h>
#include <stdint.h>
#include <stddef.h>
#include <zenoh-pico.h>
#include <PicoSyslog.h>

// Peer mode values (comment/uncomment as needed)
#define ZENOH_MODE "peer"
#define ZENOH_LOCATOR "udp/224.0.0.123:7447#iface=eth0" //in peer mode it MUST have #iface=eth0
//scout doesnt work in peer, flips to tcp and crashes.

// Client mode values (comment/uncomment as needed)
//#define ZENOH_MODE "client"
//#define ZENOH_LOCATOR "tcp/192.168.1.125:7447" 
//#define ZENOH_LOCATOR "" // If empty, it will scout

// zenoh key that is published.
#define KEYEXPR "test/test"

extern PicoSyslog::Logger syslog;
typedef void (*ZenohMessageCallback)(const char* topic, const char* payload, size_t len);


class ZenohNode {
public:

  ZenohNode();
  ~ZenohNode();

 // void setSyslogIP(const char* ip);
  // Initialize the Zenoh node. Optionally provide a locator/url. mode, and keyExpr
  // Returns true on success.
  bool begin(const char* locator = nullptr,const char* mode = "client",const char* keyExpr = "test/test");

  // Stop the node and free resources.
  void end();

  // Publish a raw payload to a topic.
  // Returns true on success.
  bool publish(const char* topic, const char* payload, size_t len);

  // Convenience overload for null-terminated payloads (strings).
  bool publish(const char* topic, const char* payload);

  // Subscribe to a topic; callback will be invoked for received messages.
  // Returns true on success.
  bool subscribe(const char* topic, ZenohMessageCallback cb); 

  static void data_handler(z_loaned_sample_t *sample, void *arg);

  bool declarePublisher(const char* keyExpr);
  
  // Check whether the node is currently running.
  bool isRunning() const;

private:
  bool running;

  // Internal helpers (stubs / placeholders)
  
};

#endif // ZENOHNODE_H